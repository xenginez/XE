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

	XE::uint32 flag = 0;
	Serialize( &flag, sizeof( XE::uint32 ) );

	_IsConvert = ( flag != 0x12345678 );

	XE::uint64 version;
	_Stream.read( (char *)&version, sizeof( XE::uint64 ) );
	if ( _IsConvert )
	{
		XE::uint8 * buf = (XE::uint8*)&version;
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

void XE::ArchiveLoad::Serialize( XE::int8 * ptr )
{
	_Stream.read( (char *)ptr, sizeof( XE::int8 ) );
}

void XE::ArchiveLoad::Serialize( XE::int16 * ptr )
{
	_Stream.read( (char *)ptr, sizeof( XE::int8 ) );

	if ( _IsConvert )
	{
		XE::uint8 * buf = (XE::uint8*)ptr;

		std::swap( buf[0], buf[1] );
	}
}

void XE::ArchiveLoad::Serialize( XE::int32 * ptr )
{
	_Stream.read( (char *)ptr, sizeof( XE::int32 ) );

	if ( _IsConvert )
	{
		XE::uint8 * buf = (XE::uint8*)ptr;

		std::swap( buf[0], buf[3] );
		std::swap( buf[1], buf[2] );
	}
}

void XE::ArchiveLoad::Serialize( XE::int64 * ptr )
{
	_Stream.read( (char *)ptr, sizeof( XE::int64 ) );

	if ( _IsConvert )
	{
		XE::uint8 * buf = (XE::uint8*)ptr;

		std::swap( buf[0], buf[7] );
		std::swap( buf[1], buf[6] );
		std::swap( buf[2], buf[5] );
		std::swap( buf[3], buf[4] );
	}
}

void XE::ArchiveLoad::Serialize( XE::uint8 * ptr )
{
	_Stream.read( (char *)ptr, sizeof( XE::uint8 ) );
}

void XE::ArchiveLoad::Serialize( XE::uint16 * ptr )
{
	_Stream.read( (char *)ptr, sizeof( XE::uint16 ) );

	if ( _IsConvert )
	{
		XE::uint8 * buf = (XE::uint8*)ptr;

		std::swap( buf[0], buf[1] );
	}
}

void XE::ArchiveLoad::Serialize( XE::uint32 * ptr )
{
	_Stream.read( (char *)ptr, sizeof( XE::uint32 ) );

	if ( _IsConvert )
	{
		XE::uint8 * buf = (XE::uint8*)ptr;

		std::swap( buf[0], buf[3] );
		std::swap( buf[1], buf[2] );
	}
}

void XE::ArchiveLoad::Serialize( XE::uint64 * ptr )
{
	_Stream.read( (char *)ptr, sizeof( XE::uint64 ) );

	if ( _IsConvert )
	{
		XE::uint8 * buf = (XE::uint8*)ptr;

		std::swap( buf[0], buf[7] );
		std::swap( buf[1], buf[6] );
		std::swap( buf[2], buf[5] );
		std::swap( buf[3], buf[4] );
	}
}

void XE::ArchiveLoad::Serialize( XE::float32 * ptr )
{
	_Stream.read( (char *)ptr, sizeof( XE::float32 ) );

	if ( _IsConvert )
	{
		XE::uint8 * buf = (XE::uint8*)ptr;

		std::swap( buf[0], buf[3] );
		std::swap( buf[1], buf[2] );
	}
}

void XE::ArchiveLoad::Serialize( XE::float64 * ptr )
{
	_Stream.read( (char *)ptr, sizeof( XE::float64 ) );

	if ( _IsConvert )
	{
		XE::uint8 * buf = (XE::uint8*)ptr;

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
		XE::uint32 flag = 0x12345678;
		Serialize( &flag, sizeof( XE::uint32 ) );
		XE::uint64 version = Version;
		Serialize( &version, sizeof( XE::uint64 ) );
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

void XE::ArchiveSave::Serialize( XE::int8 * ptr )
{
	_Stream.write( (const char *)ptr, sizeof( XE::int8 ) );
}

void XE::ArchiveSave::Serialize( XE::int16 * ptr )
{
	_Stream.write( (const char *)ptr, sizeof( XE::int16 ) );
}

void XE::ArchiveSave::Serialize( XE::int32 * ptr )
{
	_Stream.write( (const char *)ptr, sizeof( XE::int32 ) );
}

void XE::ArchiveSave::Serialize( XE::int64 * ptr )
{
	_Stream.write( (const char *)ptr, sizeof( XE::int64 ) );
}

void XE::ArchiveSave::Serialize( XE::uint8 * ptr )
{
	_Stream.write( (const char *)ptr, sizeof( XE::uint8 ) );
}

void XE::ArchiveSave::Serialize( XE::uint16 * ptr )
{
	_Stream.write( (const char *)ptr, sizeof( XE::uint16 ) );
}

void XE::ArchiveSave::Serialize( XE::uint32 * ptr )
{
	_Stream.write( (const char *)ptr, sizeof( XE::uint32 ) );
}

void XE::ArchiveSave::Serialize( XE::uint64 * ptr )
{
	_Stream.write( (const char *)ptr, sizeof( XE::uint64 ) );
}

void XE::ArchiveSave::Serialize( XE::float32 * ptr )
{
	_Stream.write( (const char *)ptr, sizeof( XE::float32 ) );
}

void XE::ArchiveSave::Serialize( XE::float64 * ptr )
{
	_Stream.write( (const char *)ptr, sizeof( XE::float64 ) );
}

void XE::ArchiveSave::Serialize( void * ptr, XE::uint64 size )
{
	_Stream.write( (const char *)ptr, size );
}
