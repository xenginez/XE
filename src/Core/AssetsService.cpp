#include "AssetsService.h"

#include <tbb/concurrent_hash_map.h>

USING_XE

BEG_META( AssetsService )
END_META()

class XEPAsset
{
public:
	String Name;
	XE::uint64 Beg;
	XE::uint64 End;
	Array < String > Dependent;
};

DECL_META_CLASS( CORE_API, XEPAsset );

BEG_META( XEPAsset )
type->Property( "Name", &XEPAsset::Name );
type->Property( "Beg", &XEPAsset::Beg );
type->Property( "End", &XEPAsset::End );
type->Property( "Dependent", &XEPAsset::Dependent );
END_META()


using AssetTuple = std::tuple < AssetStatus, ObjectPtr, XE::float32 >;
using AssetMap = tbb::concurrent_hash_map < String, AssetTuple, StringHashCompare >;
using DirectoryMap = Map < String, XEPAsset >;

struct AssetsService::Private
{
	AssetMap _Assets;
	Deque < String > _Erase;
	DirectoryMap _Directorys;
};


XE::AssetsService::AssetsService()
	:_p( new Private )
{

}

XE::AssetsService::~AssetsService()
{
	delete _p;
}

bool XE::AssetsService::Startup()
{
	std::ifstream ifs( ( GetFramework()->GetAssetsPath() / "directory" ).string(), std::ios::binary );
	if( ifs.is_open() )
	{
		XmlLoadArchive Load( ifs );

		Load & _p->_Directorys;
	}

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

	auto time = GetFramework()->GetTimerService()->GetTime();

	for( auto it = _p->_Assets.begin(); it != _p->_Assets.end(); ++it )
	{
		if( ObjectPtr asset = std::get < 1 >( it->second ) )
		{
			if( asset.use_count() == 1 && ( ( time - std::get < 2 >( it->second ) ) > AssetCacheTime ) )
			{
				_p->_Erase.push_back( it->first );
			}
		}
	}
}

void XE::AssetsService::Clearup()
{
	_p->_Erase.clear();
	_p->_Assets.clear();
	_p->_Directorys.clear();
}

XE::Prefab XE::AssetsService::Load( const String & val )
{
	auto obj = GetAsset( val );
	if( obj == nullptr )
	{
		_p->_Assets.insert( std::make_pair( val, std::make_tuple( AssetStatus::Loading, nullptr, GetFramework()->GetTimerService()->GetTime() ) ) );
		LoadAsset( val );
	}

	return CreatePrefab( val );
}

XE::Prefab XE::AssetsService::AsynLoad( const String & val )
{
	auto obj = GetAsset( val );
	if( obj == nullptr )
	{
		if( GetFramework()->GetThreadService()->GetCurrentThreadType() == ThreadType::IO )
		{
			LoadAsset(val);
			_p->_Assets.insert( std::make_pair( val, std::make_tuple( AssetStatus::Ready, nullptr, GetFramework()->GetTimerService()->GetTime() ) ) );
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

	return CreatePrefab( val );
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
	if( _p->_Assets.find( it, val ) )
	{
		std::get < 2 >( it->second ) = GetFramework()->GetTimerService()->GetTime();
		return std::get < 1 >( it->second );
	}

	return nullptr;
}

XE::AssetStatus XE::AssetsService::GetAssetStatus( const String & val ) const
{
	AssetMap::accessor it;
	if( _p->_Assets.find( it, val ) )
	{
		return std::get < 0 >( it->second );
	}

	return AssetStatus::Undefined;
}

void XE::AssetsService::LoadAsset( const String & val )
{
	{
		auto it = _p->_Directorys.find( val );
		if( it != _p->_Directorys.end() )
		{
			for( const auto & dep : it->second.Dependent )
			{
				LoadAsset( dep );
			}
		}
	}

	// TODO: Load Current Asset

	{
		AssetMap::accessor it;
		if( _p->_Assets.find( it, val ) )
		{
			std::get < 0 >( it->second ) = AssetStatus::Ready;
			std::get < 1 >( it->second ) = nullptr;
			std::get < 2 >( it->second ) = GetFramework()->GetTimerService()->GetTime();
		}
	}
}

void XE::AssetsService::UnloadAsset( const String & val )
{
	AssetMap::accessor it;
	if( _p->_Assets.find( it, val ) )
	{
		_p->_Assets.erase( it );
	}
}

void XE::AssetsService::Prepare()
{

}
