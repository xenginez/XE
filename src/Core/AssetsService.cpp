#include "AssetsService.h"

#include <zipper/unzipper.h>
#include <tbb/concurrent_hash_map.h>

USING_XE

BEG_META( AssetsService )
END_META()

using AssetTuple = std::tuple < AssetStatus, ObjectPtr, XE::float32 >;
using AssetMap = tbb::concurrent_hash_map < MD5, AssetTuple, MD5HashCompare >;

struct AssetsService::Private
{
	AssetMap _Assets;
	XE::float32 _Timer;
	XE::Map<XE::String, XE::MD5> _MD5Cache;
	XE::Map<XE::MD5, XE::uint32> _MD5Index;
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
	ResetMD5Cache();
}

bool XE::AssetsService::Startup()
{
	_p->_Timer = 0;

	return true;
}

void XE::AssetsService::Update()
{
	_p->_Timer += GetFramework()->GetTimerService()->GetUnscaleDeltaTime();
	if( _p->_Timer > AssetCacheTime )
	{
		_p->_Timer = 0;

		auto time = GetFramework()->GetTimerService()->GetTime();
		for( auto it = _p->_Assets.begin(); it != _p->_Assets.end(); ++it )
		{
			if( ObjectPtr asset = std::get < 1 >( it->second ) )
			{
				if( asset.use_count() <= 2 && ( ( time - std::get < 2 >( it->second ) ) > AssetCacheTime ) )
				{
					AssetMap::accessor it;
					if( _p->_Assets.find( it, it->first ) )
					{
						_p->_Assets.erase( it );
					}
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
	_p->_Timer = 0;
	_p->_Assets.clear();
	_p->_MD5Cache.clear();
	_p->_MD5Index.clear();
}

XE::ObjectPtr XE::AssetsService::Load( const String & val )
{
	auto obj = GetAsset( val );

	if( obj == nullptr )
	{
		SetAssetStatus( PathToMD5( val ), nullptr, AssetStatus::LOADING );
		obj = LoadAsset( val );
		if( obj )
		{
			SetAssetStatus( PathToMD5( val ), obj, AssetStatus::READY );
		}
		else
		{
			SetAssetStatus( PathToMD5( val ), obj, AssetStatus::FAILED );
		}
	}

	return obj;
}

void XE::AssetsService::AsyncLoad( const String & val )
{
	auto obj = GetAsset( val );

	if( obj == nullptr )
	{
		if( GetFramework()->GetThreadService()->GetCurrentThreadType() == ThreadType::IO )
		{
			SetAssetStatus( PathToMD5( val ), nullptr, AssetStatus::LOADING );
			auto asset = LoadAsset( val );
			if( asset )
			{
				SetAssetStatus( PathToMD5( val ), asset, AssetStatus::READY );
			}
			else
			{
				SetAssetStatus( PathToMD5( val ), asset, AssetStatus::FAILED );
			}
		}
		else
		{
			SetAssetStatus( PathToMD5( val ), nullptr, AssetStatus::LOADING );
			GetFramework()->GetThreadService()->PostTask( [this, val]()
														  {
															  AsyncLoad( val );
															  return false;
														  }, ThreadType::IO );
		}
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

	return AssetStatus::UNDEFINED;
}

XE::ObjectPtr XE::AssetsService::LoadAsset( const XE::String & val )
{
	if( auto asset = SearchAssetData( val ) )
	{
		asset->AssetLoad();
		return asset;
	}

	return nullptr;
}

XE::ObjectPtr XE::AssetsService::SearchAssetData( const XE::String & val ) const
{
	auto md5 = PathToMD5( val );

	XE::Buffer buf;

	auto it = _p->_MD5Index.find( md5 );
	if( it != _p->_MD5Index.end() )
	{
		auto path = XE::StringUtils::Format( "%1/assets_%2.data", GetFramework()->GetAssetsPath().string(), it->second );

		zipper::Unzipper unzip( path );

		std::vector<unsigned char> data;
		unzip.extractEntryToMemory( md5.To32String(), data );
		buf.Wirte( (const char * )data.data(), data.size() );

		XE::ObjectPtr obj;

		auto view = buf.GetView();
		XE::BinaryLoadArchive load( view );
		load & obj;

		return obj;
	}

	return nullptr;
}

void XE::AssetsService::ResetMD5Cache()
{
	_p->_MD5Cache.clear();
	_p->_MD5Index.clear();

	auto path = GetFramework()->GetUserDataPath() / "assets.data";
	std::ifstream ifs( path );
	if( ifs.is_open() )
	{
		char buf[512] = { 0 };

		while( !ifs.eof() )
		{
			ifs.getline( buf, 512 );
			auto list = XE::StringUtils::Split( buf, ":" );
			if( list.size() == 3 )
			{
				_p->_MD5Cache.insert( { list[0], list[1] } );
				_p->_MD5Index.insert( { list[1], std::stoi( list[2] ) } );
			}
		}
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

	return md5;
}

void XE::AssetsService::SetAssetStatus( const XE::MD5 & md5, const XE::ObjectPtr & asset, AssetStatus status )
{
	AssetMap::accessor it;
	if( _p->_Assets.find( it, md5 ) )
	{
		std::get < 0 >( it->second ) = status;
		std::get < 1 >( it->second ) = asset;
		std::get < 2 >( it->second ) = GetFramework()->GetTimerService()->GetTime();
	}
	else
	{
		_p->_Assets.insert( std::make_pair( md5, std::make_tuple( status, asset, GetFramework()->GetTimerService()->GetTime() ) ) );
	}
}
