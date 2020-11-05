#include "AssetsService.h"

#include <sqlite3/sqlite3.h>
#include <tbb/concurrent_hash_map.h>
#define TBB_PREVIEW_CONCURRENT_LRU_CACHE 1
#include <tbb/concurrent_lru_cache.h>

#include "Utils/Zipper.h"
#include "Utils/Logger.h"

static constexpr char * SELECT_PACKAGES = "SELECT * FROM packages;";
static constexpr char * SELECT_ASSET = "SELECT package_name FROM assets WHERE path=\"%1\";";

int PrintDBLog( int err )
{
	switch( err ) \
	{ \
	case SQLITE_OK: \
		break; \
	case SQLITE_ERROR: \
		XE_LOG( XE::LoggerLevel::Error, "Generic error" ); break; \
	case SQLITE_INTERNAL: \
		XE_LOG( XE::LoggerLevel::Error, "Internal logic error in SQLite" ); break; \
	case SQLITE_PERM: \
		XE_LOG( XE::LoggerLevel::Error, "Access permission denied" ); break; \
	case SQLITE_ABORT: \
		XE_LOG( XE::LoggerLevel::Error, "Callback routine requested an abort" ); break; \
	case SQLITE_BUSY: \
		XE_LOG( XE::LoggerLevel::Error, "The database file is locked" ); break; \
	case SQLITE_LOCKED: \
		XE_LOG( XE::LoggerLevel::Error, "A table in the database is locked" ); break; \
	case SQLITE_NOMEM: \
		XE_LOG( XE::LoggerLevel::Error, "A malloc() failed" ); break; \
	case SQLITE_READONLY: \
		XE_LOG( XE::LoggerLevel::Error, "Attempt to write a readonly database" ); break; \
	case SQLITE_INTERRUPT: \
		XE_LOG( XE::LoggerLevel::Error, "Operation terminated by sqlite3_interrupt()" ); break; \
	case SQLITE_IOERR: \
		XE_LOG( XE::LoggerLevel::Error, "Some kind of disk I/O error occurred" ); break; \
	case SQLITE_CORRUPT: \
		XE_LOG( XE::LoggerLevel::Error, "The database disk image is malformed" ); break; \
	case SQLITE_NOTFOUND: \
		XE_LOG( XE::LoggerLevel::Error, "Unknown opcode in sqlite3_file_control()" ); break; \
	case SQLITE_FULL: \
		XE_LOG( XE::LoggerLevel::Error, "Insertion failed because database is full" ); break; \
	case SQLITE_CANTOPEN: \
		XE_LOG( XE::LoggerLevel::Error, "Unable to open the database file" ); break; \
	case SQLITE_PROTOCOL: \
		XE_LOG( XE::LoggerLevel::Error, "Database lock protocol error" ); break; \
	case SQLITE_EMPTY: \
		XE_LOG( XE::LoggerLevel::Error, "Internal use only" ); break; \
	case SQLITE_SCHEMA: \
		XE_LOG( XE::LoggerLevel::Error, "The database schema changed" ); break; \
	case SQLITE_TOOBIG: \
		XE_LOG( XE::LoggerLevel::Error, "String or BLOB exceeds size limit" ); break; \
	case SQLITE_CONSTRAINT: \
		XE_LOG( XE::LoggerLevel::Error, "Abort due to constraint violation" ); break; \
	case SQLITE_MISMATCH: \
		XE_LOG( XE::LoggerLevel::Error, "Data type mismatch" ); break; \
	case SQLITE_MISUSE: \
		XE_LOG( XE::LoggerLevel::Error, "Library used incorrectly" ); break; \
	case SQLITE_NOLFS: \
		XE_LOG( XE::LoggerLevel::Error, "Uses OS features not supported on host" ); break; \
	case SQLITE_AUTH: \
		XE_LOG( XE::LoggerLevel::Error, "Authorization denied" ); break; \
	case SQLITE_FORMAT: \
		XE_LOG( XE::LoggerLevel::Error, "Not used" ); break; \
	case SQLITE_RANGE: \
		XE_LOG( XE::LoggerLevel::Error, "2nd parameter to sqlite3_bind out of range" ); break; \
	case SQLITE_NOTADB: \
		XE_LOG( XE::LoggerLevel::Error, "File opened that is not a database file" ); break; \
	case SQLITE_NOTICE: \
		XE_LOG( XE::LoggerLevel::Error, "Notifications from sqlite3_log()" ); break; \
	case SQLITE_WARNING: \
		XE_LOG( XE::LoggerLevel::Error, "Warnings from sqlite3_log()" ); break; \
	case SQLITE_ROW: \
		XE_LOG( XE::LoggerLevel::Error, "sqlite3_step() has another row ready" ); break; \
	case SQLITE_DONE: \
		XE_LOG( XE::LoggerLevel::Error, "sqlite3_step() has finished executing" ); break; \
	default: \
		break; \
	}

	return err;
}

#define CHECK_DB( X ) PrintDBLog( X )

BEG_META( XE::AssetsService )
END_META()

struct XE::AssetsService::Private
{
	sqlite3 * _DB = nullptr;
	XE::Map<XE::String, XE::Unzipper> _Packages;
	tbb::concurrent_hash_map<XE::String, XE::ObjectWPtr, StringHashCompare > _ObjectCache;
	tbb::concurrent_lru_cache<XE::String, XE::MemoryStream> _MemoryCache = { []( XE::String )->XE::MemoryStream {return {};}, 100 };
};

XE::AssetsService::AssetsService()
	:_p( new Private )
{

}

XE::AssetsService::~AssetsService()
{
	delete _p;
}

void XE::AssetsService::Prepare()
{
}

bool XE::AssetsService::Startup()
{
	auto path = GetFramework()->GetAssetsPath() / "index.db";

	CHECK_DB( sqlite3_open( path.u8string().c_str(), &_p->_DB ) );

	int row, col;
	char ** result = nullptr;
	char * errmsg = nullptr;

	int err = CHECK_DB( sqlite3_get_table( _p->_DB, SELECT_PACKAGES, &result, &row, &col, &errmsg ) );
	if( err == SQLITE_OK )
	{
		path = GetFramework()->GetAssetsPath();

		for( int i = 0; i < row; ++i )
		{
			_p->_Packages.insert( { result[col++], XE::Unzipper( ( path / result[col++] ).u8string() ) } );
		}
	}

	return true;
}

void XE::AssetsService::Update()
{

}

void XE::AssetsService::Clearup()
{
	if( _p->_DB )
	{
		CHECK_DB( sqlite3_close( _p->_DB ) );
		_p->_DB = nullptr;
	}
	
	_p->_Packages.clear();
}

XE::MemoryView XE::AssetsService::Load( const XE::FileSystem::Path & path )
{
	auto handle = _p->_MemoryCache[path.u8string()];
	if( handle && handle.value().view() )
	{
		return handle.value().view();
	}

	int row, col;
	char ** result = nullptr;
	char * errmsg = nullptr;
	int err = CHECK_DB( sqlite3_get_table( _p->_DB, XE::StringUtils::Format( SELECT_ASSET, path.u8string() ).c_str(), &result, &row, &col, &errmsg ) );
	if( err == SQLITE_OK && row > 0 )
	{
		auto it = _p->_Packages.find( result[col] );
		if( it != _p->_Packages.end() )
		{
			handle.value().clear();
			it->second.GetEntryData( path.u8string(), handle.value() );
			return handle.value().view();
		}
	}

	return nullptr;
}

void XE::AssetsService::AsyncLoad( const XE::FileSystem::Path & path, const LoadFinishCallback & callback )
{
	CHECK_THREAD( ThreadType::IO ) ? callback( Load( path ) ) : GetFramework()->GetThreadService()->PostTask( ThreadType::IO, [=]()
																											  {
																												  callback( Load( path ) );
																											  } );
}

XE::ObjectPtr XE::AssetsService::LoadObject( const XE::FileSystem::Path & path )
{
	tbb::concurrent_hash_map<XE::String, XE::ObjectWPtr, StringHashCompare >::accessor it;
	if( _p->_ObjectCache.find( it, path.u8string() ) )
	{
		if( !it->second.expired() )
		{
			return it->second.lock();
		}
	}

	if( auto mem = Load( path ) )
	{
		XE::BinaryLoadArchive load( mem );

		XE::ObjectPtr obj;

		load & obj;

		obj->AssetLoad();

		_p->_ObjectCache.insert( { path.u8string(), obj } );

		return obj;
	}

	return nullptr;
}

void XE::AssetsService::AsyncLoadObject( const XE::FileSystem::Path & path, const LoadObjectFinishCallback & callback )
{
	CHECK_THREAD( ThreadType::IO ) ? callback( LoadObject( path ) ) : GetFramework()->GetThreadService()->PostTask( ThreadType::IO, [=]()
																													{
																														callback( LoadObject( path ) );
																													} );
}
