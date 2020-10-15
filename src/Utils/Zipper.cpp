#include "Zipper.h"

#include <zip/zip.h>

static constexpr XE::uint64 IO_BUFFER_SIZE = 65536;

void Encrypt( XE::uint64 hash, XE::int8 * buf, XE::uint64 size )
{
	while( buf < ( buf + size ) )
	{
		*( ( XE::uint64 * )buf ) ^= hash;
		buf += sizeof( XE::uint64 );
	}
}

void Decrypt( XE::uint64 hash, XE::int8 * buf, XE::uint64 size )
{
	while( buf < ( buf + size ) )
	{
		*( ( XE::uint64 * )buf ) ^= hash;
		buf += sizeof( XE::uint64 );
	}
}

struct XE::Zipper::Private
{
	zip_t * _Zip = nullptr;
};

XE::Zipper::Zipper()
    :_p( new Private )
{

}

XE::Zipper::Zipper( const std::string & zipname )
	: _p( new Private )
{
    Open( zipname );
}

XE::Zipper::~Zipper()
{
    delete _p;
}

bool XE::Zipper::Add( std::istream & source, const std::string & name, const std::string & password /*= "" */ )
{
    if( !_p->_Zip )
    {
        return false;
	}

	if( zip_entry_open( _p->_Zip, name.c_str() ) == 0 )
	{
		auto hash = std::hash<std::string>()( password );

		XE::int8 buf[IO_BUFFER_SIZE];

		while( !source.eof() )
		{
			std::memset( buf, 0, IO_BUFFER_SIZE );

			source.read( buf, IO_BUFFER_SIZE );

			auto size = source.gcount();

			Encrypt( hash, buf, size );

			zip_entry_write( _p->_Zip, buf, size );
		}

		return zip_entry_close( _p->_Zip ) == 0;
	}

	return false;
}

bool XE::Zipper::Open( const std::string & zipname )
{
	Close();

	if( XE::FileSystem::exists( zipname ) )
	{
		zip_open( zipname.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'a' );
	}
	else
	{
		zip_open( zipname.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w' );
	}

    return _p->_Zip != nullptr;
}

bool XE::Zipper::IsOpen() const
{
	return _p->_Zip != nullptr;
}

void XE::Zipper::Close()
{
	if( _p->_Zip != nullptr )
	{
		zip_close( _p->_Zip );
		_p->_Zip = nullptr;
	}
}



struct XE::Unzipper::Private
{
	zip_t * _Zip = nullptr;
};

XE::Unzipper::Unzipper()
    :_p( new Private )
{

}

XE::Unzipper::Unzipper( const std::string & zipname )
	: _p( new Private )
{
    Open( zipname );
}

XE::Unzipper::~Unzipper()
{
    delete _p;
}

bool XE::Unzipper::GetEntries( XE::Array< std::string > & entries ) const
{
	auto count = zip_total_entries( _p->_Zip );

	for( int i = 0; i < count; ++i )
	{
		if( zip_entry_openbyindex( _p->_Zip, i ) == 0 )
		{
			entries.push_back( zip_entry_name( _p->_Zip ) );

			zip_entry_close( _p->_Zip );
		}
	}

    return true;
}

bool XE::Unzipper::ExtractEntiy( const std::string & name )
{
	if( zip_entry_open( _p->_Zip, name.c_str() ) == 0 )
	{
		zip_entry_close( _p->_Zip );

		return true;
	}

	return false;
}

bool XE::Unzipper::GetEntryData( const std::string & name, std::ostream & stream, const std::string & password /*= "" */ )
{
	if( zip_entry_open( _p->_Zip, name.c_str() ) == 0 )
	{
		auto hash = std::hash<std::string>()( password );

		XE::int8 buf[IO_BUFFER_SIZE];
		
		while( 1 )
		{
			std::memset( buf, 0, IO_BUFFER_SIZE );

			XE::int64 size = zip_entry_noallocread( _p->_Zip, buf, IO_BUFFER_SIZE );

			if (size == -1)
			{
				break;
			}

			Decrypt( hash, buf, size );

			stream.write( buf, size );
		}

		zip_entry_close( _p->_Zip );

		return true;
	}
    return false;
}

bool XE::Unzipper::Open( const std::string & zipname )
{
	Close();

	_p->_Zip = zip_open( zipname.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'r' );

	return _p->_Zip != nullptr;
}

bool XE::Unzipper::IsOpen() const
{
    return _p->_Zip != nullptr;
}

void XE::Unzipper::Close()
{
	if( _p->_Zip != nullptr )
	{
		zip_close( _p->_Zip );
		_p->_Zip = nullptr;
	}
}
