#include "AssetsService.h"

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
		_p->_Assets.insert( std::make_pair( val, std::make_tuple( AssetStatus::Loading, nullptr, GetFramework()->GetTimerService()->GetTime() ) ) );
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
		auto dependent = GetDependent( val );

		for( auto const & it : dependent )
		{
			LoadAsset( it );
		}
	}

	// TODO: Load Current Asset
	ObjectPtr asset = nullptr;

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

void XE::AssetsService::UnloadAsset( const String & val )
{
	AssetMap::accessor it;
	if( _p->_Assets.find( it, val ) )
	{
		std::get < 1 >( it->second )->AssetUnload();

		_p->_Assets.erase( it );
	}
}

XE::FArray<XE::String> XE::AssetsService::GetDependent( const String & val ) const
{
	XE::FArray<XE::String> dependent;

	return dependent;
}
