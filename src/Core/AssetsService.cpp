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
	XE::float32 _Timer = 0;
	Deque < XE::MD5 > _Erase;
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
	auto path = GetFramework()->GetUserDataPath() / "assets.txt";
	std::ifstream ifs( path );
	if( ifs.is_open() )
	{
		char buf[512] = { 0 };

		while( !ifs.eof() )
		{
			ifs.getline( buf, 512 );
			auto list = XE::StringUtils::Split( buf, ":" );
			_p->_MD5Cache.insert( { list[0], list[1] } );
			_p->_MD5Index.insert( { list[1], std::stoi( list[2] ) } );
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
	auto var = DeserializeObject( val );
	if( var.IsInvalid() == false && var.IsNull() == false )
	{
		ObjectPtr asset = var.Value<ObjectPtr>();

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

	return md5;
}

XE::Variant AssetsService::DeserializeObject( const XE::MD5 & val ) const
{
	ObjectPtr ret;

	auto path = GetFramework()->GetUserDataPath() / "cache" / val.To32String();

	if( std::filesystem::exists( path ) )
	{
		std::ifstream ifs( path, std::ios::binary );

		XE::Buffer buf;
		ifs.seekg( std::ios::end );
		auto size = ifs.tellg();
		ifs.seekg( std::ios::beg );

		buf.resize( size );

		ifs.read( buf.data(), size );

		auto view = buf.GetView();
		XE::BinaryLoadArchive load( view );

		load & ret;
	}
	else
	{
		auto it = _p->_MD5Index.find( val );

		if( it != _p->_MD5Index.end() )
		{
			auto path = XE::StringUtils::Format( "%1/assets_%2.data", GetFramework()->GetAssetsPath().string(), it->second );

			zipper::Unzipper unzip( path );

			XE::omemorystream oms;

			unzip.extractEntryToStream( val.To32String(), oms );

			auto view = oms.view();

			XE::BinaryLoadArchive load( view );

			load & ret;

			std::ofstream ofs( path, std::ios::binary );
			ofs.write( view.data(), view.size() );
			ofs.close();
		}
	}

	return ret;
}
