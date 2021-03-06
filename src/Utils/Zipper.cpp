#include "Zipper.h"

#include <lz4/lz4.h>
#include <lz4/lz4frame.h>

#define BLOCK_SIZE ( 256 )

struct EntryInfo
{
	XE::uint64 Start = 0;
	XE::uint64 CompressSize = 0;
	XE::uint64 DecompressSize = 0;
};

struct XE::Zipper::Private
{
	XE::Array< char > _DstBuf;
	std::ostream * _Stream = nullptr;
	std::array< char, BLOCK_SIZE > _SrcBuf;
	LZ4F_compressionContext_t  _LZ4 = nullptr;
	XE::Map< XE::String, EntryInfo > _Entries;
};

XE::Zipper::Zipper()
	:_p( new Private )
{

}

XE::Zipper::Zipper( std::ostream & stream )
	: _p( new Private )
{
	Open( stream );
}

XE::Zipper::~Zipper()
{
	Close();

	delete _p;
}

bool XE::Zipper::AddEntiy( const XE::String & name, std::istream & source )
{
	if( IsOpen() )
	{
		auto it = _p->_Entries.find( name );
		if( it == _p->_Entries.end() )
		{
			EntryInfo info;
			info.Start = _p->_Stream->tellp();
			auto pos = source.tellg();
			source.seekg( 0, std::ios::end );
			info.DecompressSize = source.tellg() - pos;
			source.seekg( pos );

			while( !source.eof() )
			{
				source.read( _p->_SrcBuf.data(), BLOCK_SIZE );
				XE::int32 in_size = ( XE::uint32 )source.gcount();

				size_t out_size = LZ4F_compressUpdate( _p->_LZ4, _p->_DstBuf.data(), _p->_DstBuf.capacity(), _p->_SrcBuf.data(), in_size, nullptr );

				if( LZ4F_isError( out_size ) != 0 )
				{
					_p->_Stream->seekp( info.Start );
					source.seekg( pos );
					return false;
				}

				info.CompressSize += out_size;
				_p->_Stream->write( _p->_DstBuf.data(), out_size );
			}

			_p->_Entries.insert( { name, std::move( info ) } );

			return true;
		}
	}

	return false;
}

bool XE::Zipper::Open( std::ostream & stream )
{
	Close();

	if( LZ4F_isError( LZ4F_createCompressionContext( &_p->_LZ4, LZ4F_VERSION ) ) != 0 )
	{
		return false;
	}

	_p->_Stream = &stream;
	_p->_Stream->seekp( 0, std::ios::beg );
	_p->_DstBuf.resize( LZ4F_compressBound( BLOCK_SIZE, nullptr ), 0 );

	size_t ret = LZ4F_compressBegin( _p->_LZ4, &_p->_DstBuf.front(), _p->_DstBuf.capacity(), nullptr );
	if( LZ4F_isError( ret ) != 0 )
	{
		_p->_Stream = nullptr;
		Close();
		return false;
	}

	_p->_Stream->write( _p->_DstBuf.data(), ret );

	return true;
}

bool XE::Zipper::IsOpen() const
{
	return _p->_Stream != nullptr;
}

void XE::Zipper::Close()
{
	if( _p->_LZ4 )
	{
		size_t ret = LZ4F_compressEnd( _p->_LZ4, _p->_DstBuf.data(), _p->_DstBuf.capacity(), nullptr );

		_p->_Stream->write( _p->_DstBuf.data(), ret );

		LZ4F_freeCompressionContext( _p->_LZ4 );
		_p->_LZ4 = nullptr;
	}

	if( _p->_Stream )
	{
		auto start = _p->_Stream->tellp();
		for( const auto & i : _p->_Entries )
		{
			XE::uint64 sz = i.first.size();
			( *_p->_Stream ) << sz;
			_p->_Stream->write( i.first.c_str(), sz );
			( *_p->_Stream ) << i.second.Start;
			( *_p->_Stream ) << i.second.CompressSize;
			( *_p->_Stream ) << i.second.DecompressSize;
		}

		( *_p->_Stream ) << XE::uint64( _p->_Stream->tellp() - start );

		_p->_Stream->flush();
	}

	_p->_Stream = nullptr;
	_p->_Entries.clear();
}

struct XE::Unzipper::Private
{
	std::istream * _Stream = nullptr;
	std::array< char, BLOCK_SIZE > _SrcBuf;
	std::array< char, BLOCK_SIZE > _DstBuf;
	XE::Map< XE::String, EntryInfo > _Entries;
	LZ4F_decompressionContext_t  _LZ4 = nullptr;
};

XE::Unzipper::Unzipper()
	:_p( new Private )
{

}

XE::Unzipper::Unzipper( std::istream & stream )
	: _p( new Private )
{
	Open( stream );
}

XE::Unzipper::~Unzipper()
{
	Close();

	delete _p;
}

void XE::Unzipper::GetEntries( XE::Array< XE::String > & entries ) const
{
	for( const auto & i : _p->_Entries )
	{
		entries.push_back( i.first );
	}
}

bool XE::Unzipper::ExtractEntiy( const XE::String & name )
{
	auto it = _p->_Entries.find( name );

	return it != _p->_Entries.end();
}

bool XE::Unzipper::GetEntryData( const XE::String & name, std::ostream & stream )
{
	if( IsOpen() )
	{
		auto entry = _p->_Entries.find( name );
		if( entry != _p->_Entries.end() )
		{
			auto pos = stream.tellp();
			_p->_Stream->seekg( entry->second.Start );
			XE::uint64 total_size = entry->second.CompressSize;
			XE::uint64 offset = 0;

			while( total_size > 0 )
			{
				_p->_Stream->read( _p->_SrcBuf.data() + offset, std::min< XE::uint64 >( BLOCK_SIZE - offset, total_size ) );

				XE::int32 src_size = _p->_Stream->gcount();

				size_t in_size = src_size;
				size_t out_size = BLOCK_SIZE;
				
				if( LZ4F_isError( LZ4F_decompress( _p->_LZ4, _p->_DstBuf.data(), &out_size, _p->_SrcBuf.data(), &in_size, nullptr ) ) != 0 )
				{
					_p->_Stream->seekg( entry->second.Start );
					stream.seekp( pos );
					return false;
				}
				
				total_size -= in_size;
				offset = src_size - in_size;
				stream.write( _p->_DstBuf.data(), out_size );
				std::memcpy( _p->_SrcBuf.data(), _p->_SrcBuf.data() + in_size, offset );
			}

			return true;
		}
	}

	return false;
}

bool XE::Unzipper::Open( std::istream & stream )
{
	Close();

	if( LZ4F_isError( LZ4F_createDecompressionContext( &_p->_LZ4, LZ4F_VERSION ) ) != 0 )
	{
		return false;
	}

	_p->_Stream = &stream;
	_p->_Stream->seekg( -int(sizeof( XE::uint64 )), std::ios::end );
	XE::uint64 pos = 0;
	( *_p->_Stream ) >> pos;
	_p->_Stream->seekg( pos );

	while( !_p->_Stream->eof() )
	{
		XE::String name;
		EntryInfo info;

		XE::uint64 sz = 0;
		( *_p->_Stream ) >> sz;
		name.resize( sz + 1 );
		_p->_Stream->read( name.data(), sz );
		( *_p->_Stream ) >> info.Start;
		( *_p->_Stream ) >> info.CompressSize;
		( *_p->_Stream ) >> info.DecompressSize;

		_p->_Entries.insert( { std::move( name ), std::move( info ) } );
	}

	_p->_Stream->seekg( 0, std::ios::beg );

	return true;
}

bool XE::Unzipper::IsOpen() const
{
	return _p->_Stream != nullptr;
}

void XE::Unzipper::Close()
{
	if( _p->_LZ4 )
	{
		LZ4F_freeDecompressionContext( _p->_LZ4 );
		_p->_LZ4 = nullptr;
	}

	_p->_Stream = nullptr;
	_p->_Entries.clear();
}
