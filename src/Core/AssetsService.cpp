#include "AssetsService.h"

#include <sqlite3/sqlite3.h>
#include <tbb/concurrent_hash_map.h>

USING_XE

BEG_META( AssetsService )
END_META()

using AssetTuple = std::tuple < AssetStatus, ObjectPtr, XE::float32 >;
using AssetMap = tbb::concurrent_hash_map < String, AssetTuple, StringHashCompare >;

struct AssetsService::Private
{
	XE::float32 _Timer = 0;
	AssetMap _Assets;
	Deque < String > _Erase;
	sqlite3 * _DBMD5;
	XE::Array< sqlite3 * > _DBs;
	XE::UnorderedMap<XE::String, XE::uint32> _MD5s;
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
	auto path = GetFramework()->GetAssetsPath() / "md5.db";
	if( sqlite3_open_v2( path.string().c_str(), &_p->_DBMD5, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL ) == SQLITE_OK )
	{
		sqlite3_stmt * stmt = NULL;
		if( sqlite3_prepare_v2( _p->_DBMD5, "SELECT md5, index from md5", -1, &stmt, NULL ) == SQLITE_OK )
		{
			while( sqlite3_step( stmt ) == SQLITE_ROW )
			{
				const char * md5 = ( const char * )sqlite3_column_text( stmt, 0 );
				int index = sqlite3_column_int( stmt, 1 );

				_p->_MD5s.insert( { md5, index } );
			}

			sqlite3_finalize( stmt );
		}
	}

	for( int i = 0; ; ++i )
	{
		auto path = GetFramework()->GetAssetsPath() / ( XE::StringUtils::Format( "asset_%1.db", i ) );
		if( std::filesystem::exists( path ) )
		{
			sqlite3 * db;
			if( sqlite3_open_v2( path.string().c_str(), &db, SQLITE_OPEN_READONLY | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL ) == SQLITE_OK )
			{
				_p->_DBs.push_back( db );
			}
			else
			{
				break;
			}
		}
		else
		{
			break;
		}
	}
}

bool XE::AssetsService::Startup()
{

	return true;
}

void XE::AssetsService::Update()
{
	if( auto threadService = GetFramework()->GetThreadService() )
	{
		for( auto it : _p->_Erase )
		{
			threadService->PostTask( [&]()
									 {
										 UnloadAsset( it );
										 return false;
									 }, ThreadType::IO );
		}
	}
	_p->_Erase.clear();

	_p->_Timer += GetFramework()->GetTimerService()->GetUnscaleDeltaTime();
	if( _p->_Timer > AssetCacheTime )
	{
		_p->_Timer = 0;

		auto time = GetFramework()->GetTimerService()->GetTime();
		for( auto it = _p->_Assets.begin(); it != _p->_Assets.end(); ++it )
		{
			if( ObjectPtr asset = std::get < 1 >( it->second ) )
			{
				if( asset.use_count() == 1 && ( ( time - std::get < 2 >( it->second ) ) > AssetCacheTime ) )
				{
					_p->_Erase.push_back( it->first );
				}
				else
				{
					std::get < 2 >( it->second ) = time;
				}
			}
		}
	}
}

void XE::AssetsService::Clearup()
{
	if( _p->_DBMD5 != nullptr )
	{
		sqlite3_close_v2( _p->_DBMD5 );
		_p->_DBMD5 = nullptr;
	}

	for( auto db : _p->_DBs )
	{
		sqlite3_close_v2( db );
	}
	_p->_DBs.clear();
	_p->_MD5s.clear();
	_p->_Erase.clear();
	_p->_Assets.clear();
}

XE::ObjectPtr XE::AssetsService::Load( const String & val )
{
	auto obj = GetAsset( val );

	if( obj == nullptr )
	{
		_p->_Assets.insert( std::make_pair( PathToMD5( val ), std::make_tuple( AssetStatus::Loading, nullptr, GetFramework()->GetTimerService()->GetTime() ) ) );
		LoadAsset( val );
	}

	return GetAsset( val );
}

void XE::AssetsService::AsynLoad( const String & val )
{
	auto obj = GetAsset( val );

	if( obj == nullptr )
	{
		if( GetFramework()->GetThreadService()->GetCurrentThreadType() == ThreadType::IO )
		{
			LoadAsset( val );
			_p->_Assets.insert( std::make_pair( PathToMD5( val ), std::make_tuple( AssetStatus::Ready, nullptr, GetFramework()->GetTimerService()->GetTime() ) ) );
		}
		else
		{
			GetFramework()->GetThreadService()->PostTask( [&]()
														  {
															  LoadAsset( val );
															  return false;
														  }, ThreadType::IO );
			_p->_Assets.insert( std::make_pair( val, std::make_tuple( AssetStatus::Loading, nullptr, GetFramework()->GetTimerService()->GetTime() ) ) );
		}
	}
}

void XE::AssetsService::Unload( const String & val )
{
	if( GetFramework()->GetThreadService()->GetCurrentThreadType() == ThreadType::IO )
	{
		UnloadAsset( val );
	}
	else
	{
		GetFramework()->GetThreadService()->PostTask( [&]()
													  {
														  UnloadAsset( val );
														  return false;
													  }, ThreadType::IO );
	}
}

XE::ObjectPtr XE::AssetsService::GetAsset( const String & val ) const
{
	AssetMap::accessor it;
	if( _p->_Assets.find( it, PathToMD5( val ) ) )
	{
		std::get < 2 >( it->second ) = GetFramework()->GetTimerService()->GetTime();
		return std::get < 1 >( it->second );
	}

	return nullptr;
}

XE::AssetStatus XE::AssetsService::GetAssetStatus( const String & val ) const
{
	AssetMap::accessor it;
	if( _p->_Assets.find( it, PathToMD5( val ) ) )
	{
		return std::get < 0 >( it->second );
	}

	return AssetStatus::Undefined;
}

void XE::AssetsService::LoadAsset( const String & val )
{
	auto md5 = PathToMD5( val );

	ObjectPtr asset = DeserializeObject( md5 );

	asset->AssetLoad();

	{
		AssetMap::accessor it;
		if( _p->_Assets.find( it, md5 ) )
		{
			std::get < 0 >( it->second ) = AssetStatus::Ready;
			std::get < 1 >( it->second ) = asset;
			std::get < 2 >( it->second ) = GetFramework()->GetTimerService()->GetTime();
		}
	}
}

void XE::AssetsService::UnloadAsset( const String & val )
{
	AssetMap::accessor it;
	if( _p->_Assets.find( it, PathToMD5( val ) ) )
	{
		std::get < 1 >( it->second )->AssetUnload();

		_p->_Assets.erase( it );
	}
}

XE::String AssetsService::PathToMD5( const XE::String & val ) const
{
	std::regex regex( "^([a-fA-F0-9]{32})$" );
	
	if( std::regex_match( val.ToCString(), regex ) )
	{
		return val;
	}

	auto list = XE::StringUtils::Split( val.ToStdString(), ":" );
	if( list.size() == 2 )
	{
		auto str = XE::StringUtils::Format( "SELECT md5 FROM index WHERE path=%1;", list[1] );
		sqlite3_stmt * stmt = NULL;
		if( sqlite3_prepare_v2( _p->_DBs[std::stoi( list[0] )], str.c_str(), -1, &stmt, NULL ) == SQLITE_OK )
		{
			if( sqlite3_step( stmt ) == SQLITE_ROW )
			{
				return (const char * )sqlite3_column_text( stmt, 0 );
			}

			sqlite3_finalize( stmt );
		}
	}

	return "";
}

ObjectPtr AssetsService::DeserializeObject( const XE::String & val ) const
{
	auto str = XE::StringUtils::Format( "SELECT data, size FROM data WHERE md5=%1;", val.ToStdString() );
	sqlite3_stmt * stmt = NULL;

	auto it = _p->_MD5s.find( val );
	if( it != _p->_MD5s.end() )
	{
		if( sqlite3_prepare_v2( _p->_DBs[it->second], str.c_str(), -1, &stmt, NULL ) == SQLITE_OK )
		{
			if( sqlite3_step( stmt ) == SQLITE_ROW )
			{
				const std::byte * data = ( const std::byte * )sqlite3_column_blob( stmt, 0 );
				int size = sqlite3_column_int( stmt, 1 );

				XE::memory_view view( data, size );
				XE::BinaryLoadArchive archive( view );

				ObjectPtr ret;

				archive & ret;

				return ret;
			}

			sqlite3_finalize( stmt );
		}

	}

	return nullptr;
}
