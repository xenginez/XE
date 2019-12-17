#include "AssetsService.h"

#include <sqlite3/sqlite3.h>
#include <tbb/concurrent_hash_map.h>

USING_XE

BEG_META( AssetsService )
END_META()

using AssetTuple = std::tuple < AssetStatus, ObjectPtr, XE::float32 >;
using AssetMap = tbb::concurrent_hash_map < MD5, AssetTuple, MD5HashCompare >;

struct AssetsService::Private
{
	sqlite3 * _DB = nullptr;
	AssetMap _Assets;
	XE::float32 _Timer = 0;
	Deque < XE::MD5 > _Erase;
	XE::Map<XE::String, XE::MD5> _MD5Cache;
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
	auto path = GetFramework()->GetAssetsPath() / "assets.db";
	if( sqlite3_open_v2( path.string().c_str(), &_p->_DB, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL ) != SQLITE_OK )
	{
		XE_LOG( LoggerLevel::Error, "open assets sqlite fial" );
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
	if( _p->_DB != nullptr )
	{
		sqlite3_close_v2( _p->_DB );
		_p->_DB = nullptr;
	}

	_p->_Erase.clear();
	_p->_Assets.clear();
}

XE::ObjectPtr XE::AssetsService::Load( const String & val )
{
	auto obj = GetAsset( val );

	if( obj == nullptr )
	{
		_p->_Assets.insert( std::make_pair( PathToMD5( val ), std::make_tuple( AssetStatus::Loading, nullptr, GetFramework()->GetTimerService()->GetTime() ) ) );
		LoadAsset( PathToMD5( val ) );
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
			LoadAsset( PathToMD5( val ) );
			_p->_Assets.insert( std::make_pair( PathToMD5( val ), std::make_tuple( AssetStatus::Ready, nullptr, GetFramework()->GetTimerService()->GetTime() ) ) );
		}
		else
		{
			GetFramework()->GetThreadService()->PostTask( [&]()
														  {
															  LoadAsset( PathToMD5( val ) );
															  return false;
														  }, ThreadType::IO );
			_p->_Assets.insert( std::make_pair( PathToMD5( val ), std::make_tuple( AssetStatus::Loading, nullptr, GetFramework()->GetTimerService()->GetTime() ) ) );
		}
	}
}

void XE::AssetsService::Unload( const String & val )
{
	if( GetFramework()->GetThreadService()->GetCurrentThreadType() == ThreadType::IO )
	{
		UnloadAsset( PathToMD5( val ) );
	}
	else
	{
		GetFramework()->GetThreadService()->PostTask( [&]()
													  {
														  UnloadAsset( PathToMD5( val ) );
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

void XE::AssetsService::LoadAsset( const XE::MD5 & val )
{
	ObjectPtr asset = DeserializeObject( val );

	asset->AssetLoad();

	{
		AssetMap::accessor it;
		if( _p->_Assets.find( it, val ) )
		{
			std::get < 0 >( it->second ) = AssetStatus::Ready;
			std::get < 1 >( it->second ) = asset;
			std::get < 2 >( it->second ) = GetFramework()->GetTimerService()->GetTime();
		}
	}
}

void XE::AssetsService::UnloadAsset( const XE::MD5 & val )
{
	AssetMap::accessor it;
	if( _p->_Assets.find( it, val ) )
	{
		std::get < 1 >( it->second )->AssetUnload();

		_p->_Assets.erase( it );
	}
}

XE::MD5 AssetsService::PathToMD5( const XE::String & val ) const
{
	XE::MD5 md5;

	auto it = _p->_MD5Cache.find( val );
	if( it != _p->_MD5Cache.end() )
	{
		md5 = it->second;
	}
	else
	{
		auto str = XE::StringUtils::Format( "SELECT md5 FROM index WHERE path='%1';", val );
		sqlite3_stmt * stmt = NULL;
		if( sqlite3_prepare_v2( _p->_DB, str.c_str(), -1, &stmt, NULL ) == SQLITE_OK )
		{
			if( sqlite3_step( stmt ) == SQLITE_ROW )
			{
				md5 = MD5::From32String( (const char * )sqlite3_column_text( stmt, 0 ) );

				_p->_MD5Cache.insert( { val, md5 } );
			}

			sqlite3_finalize( stmt );
		}
	}

	return md5;
}

ObjectPtr AssetsService::DeserializeObject( const XE::MD5 & val ) const
{
	auto str = XE::StringUtils::Format( "SELECT data, size FROM data WHERE md5='%1';", val.To32String() );
	sqlite3_stmt * stmt = NULL;

	if( sqlite3_prepare_v2( _p->_DB, str.c_str(), -1, &stmt, NULL ) == SQLITE_OK )
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

	return nullptr;
}
