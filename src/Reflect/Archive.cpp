#include "Archive.h"

USING_XE

XE::Archive::Archive( ArchiveType val )
	:_Type( val ), _Version( Version )
{

}

XE::Archive::~Archive()
{

}

XE::uint64 XE::Archive::GetVersion() const
{
	return _Version;
}

XE::ArchiveType XE::Archive::GetType() const
{
	return _Type;
}

void XE::Archive::SetVersion( XE::uint64 val )
{
	_Version = val;
}

XE::ArchiveLoad::ArchiveLoad( std::istream& val )
	:Archive( ArchiveType::LOAD ), _Stream( val.rdbuf() )
{
	auto pos = _Stream.tellg();
	_Stream.seekg( 0, std::ostream::beg );

	uint32 flag = 0;
	Serialize( &flag, sizeof( uint32 ) );

	_IsConvert = ( flag != 0x12345678 );

	uint64 version;
	_Stream.read( (char *)&version, sizeof( uint64 ) );
	if ( _IsConvert )
	{
		uint8 * buf = (uint8*)&version;
		std::swap( buf[0], buf[7] );
		std::swap( buf[1], buf[6] );
		std::swap( buf[2], buf[5] );
		std::swap( buf[3], buf[4] );
	}
	SetVersion( version );

	if ( pos > _Stream.tellg() )
	{
		_Stream.seekg( pos );
	}
}

XE::ArchiveLoad::~ArchiveLoad()
{

}

void XE::ArchiveLoad::Serialize( bool * ptr )
{
	_Stream.read( (char *)ptr, sizeof( bool ) );
}

void XE::ArchiveLoad::Serialize( int8 * ptr )
{
	_Stream.read( (char *)ptr, sizeof( int8 ) );
}

void XE::ArchiveLoad::Serialize( int16 * ptr )
{
	_Stream.read( (char *)ptr, sizeof( int8 ) );

	if ( _IsConvert )
	{
		uint8 * buf = (uint8*)ptr;

		std::swap( buf[0], buf[1] );
	}
}

void XE::ArchiveLoad::Serialize( int32 * ptr )
{
	_Stream.read( (char *)ptr, sizeof( int32 ) );

	if ( _IsConvert )
	{
		uint8 * buf = (uint8*)ptr;

		std::swap( buf[0], buf[3] );
		std::swap( buf[1], buf[2] );
	}
}

void XE::ArchiveLoad::Serialize( int64 * ptr )
{
	_Stream.read( (char *)ptr, sizeof( int64 ) );

	if ( _IsConvert )
	{
		uint8 * buf = (uint8*)ptr;

		std::swap( buf[0], buf[7] );
		std::swap( buf[1], buf[6] );
		std::swap( buf[2], buf[5] );
		std::swap( buf[3], buf[4] );
	}
}

void XE::ArchiveLoad::Serialize( uint8 * ptr )
{
	_Stream.read( (char *)ptr, sizeof( uint8 ) );
}

void XE::ArchiveLoad::Serialize( uint16 * ptr )
{
	_Stream.read( (char *)ptr, sizeof( uint16 ) );

	if ( _IsConvert )
	{
		uint8 * buf = (uint8*)ptr;

		std::swap( buf[0], buf[1] );
	}
}

void XE::ArchiveLoad::Serialize( uint32 * ptr )
{
	_Stream.read( (char *)ptr, sizeof( uint32 ) );

	if ( _IsConvert )
	{
		uint8 * buf = (uint8*)ptr;

		std::swap( buf[0], buf[3] );
		std::swap( buf[1], buf[2] );
	}
}

void XE::ArchiveLoad::Serialize( uint64 * ptr )
{
	_Stream.read( (char *)ptr, sizeof( uint64 ) );

	if ( _IsConvert )
	{
		uint8 * buf = (uint8*)ptr;

		std::swap( buf[0], buf[7] );
		std::swap( buf[1], buf[6] );
		std::swap( buf[2], buf[5] );
		std::swap( buf[3], buf[4] );
	}
}

void XE::ArchiveLoad::Serialize( float * ptr )
{
	_Stream.read( (char *)ptr, sizeof( float ) );

	if ( _IsConvert )
	{
		uint8 * buf = (uint8*)ptr;

		std::swap( buf[0], buf[3] );
		std::swap( buf[1], buf[2] );
	}
}

void XE::ArchiveLoad::Serialize( double * ptr )
{
	_Stream.read( (char *)ptr, sizeof( double ) );

	if ( _IsConvert )
	{
		uint8 * buf = (uint8*)ptr;

		std::swap( buf[0], buf[7] );
		std::swap( buf[1], buf[6] );
		std::swap( buf[2], buf[5] );
		std::swap( buf[3], buf[4] );
	}
}

void XE::ArchiveLoad::Serialize( void * ptr, XE::uint64 size )
{
	_Stream.read( (char *)ptr, size );
}

XE::ArchiveSave::ArchiveSave( std::ostream& val )
	:Archive( ArchiveType::SAVE ), _Stream( val.rdbuf() )
{
	if (_Stream.tellp() == 0)
	{
		uint32 flag = 0x12345678;
		Serialize( &flag, sizeof( uint32 ) );
		uint64 version = Version;
		Serialize( &version, sizeof( uint64 ) );
	}
}

XE::ArchiveSave::~ArchiveSave()
{
	_Stream.flush();
}

void XE::ArchiveSave::Serialize( bool * ptr )
{
	_Stream.write( (const char *)ptr, sizeof( bool ) );
}

void XE::ArchiveSave::Serialize( int8 * ptr )
{
	_Stream.write( (const char *)ptr, sizeof( int8 ) );
}

void XE::ArchiveSave::Serialize( int16 * ptr )
{
	_Stream.write( (const char *)ptr, sizeof( int16 ) );
}

void XE::ArchiveSave::Serialize( int32 * ptr )
{
	_Stream.write( (const char *)ptr, sizeof( int32 ) );
}

void XE::ArchiveSave::Serialize( int64 * ptr )
{
	_Stream.write( (const char *)ptr, sizeof( int64 ) );
}

void XE::ArchiveSave::Serialize( uint8 * ptr )
{
	_Stream.write( (const char *)ptr, sizeof( uint8 ) );
}

void XE::ArchiveSave::Serialize( uint16 * ptr )
{
	_Stream.write( (const char *)ptr, sizeof( uint16 ) );
}

void XE::ArchiveSave::Serialize( uint32 * ptr )
{
	_Stream.write( (const char *)ptr, sizeof( uint32 ) );
}

void XE::ArchiveSave::Serialize( uint64 * ptr )
{
	_Stream.write( (const char *)ptr, sizeof( uint64 ) );
}

void XE::ArchiveSave::Serialize( float * ptr )
{
	_Stream.write( (const char *)ptr, sizeof( float ) );
}

void XE::ArchiveSave::Serialize( double * ptr )
{
	_Stream.write( (const char *)ptr, sizeof( double ) );
}

void XE::ArchiveSave::Serialize( void * ptr, XE::uint64 size )
{
	_Stream.write( (const char *)ptr, size );
}
