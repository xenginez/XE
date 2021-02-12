#include "Asset.h"

#include "Interface/IFramework.h"
#include "Interface/IAssetsService.h"

BEG_META( XE::Asset )
	type->Property( "AssetPath", &XE::Asset::GetAssetPath, &XE::Asset::SetAssetPath );
END_META()

XE::Asset::Asset()
{

}

XE::Asset::Asset( const Asset & val )
	:_AssetPath( val._AssetPath ), _Ptr( val._Ptr )
{

}

XE::Asset::~Asset()
{

}

XE::Asset::operator bool() const
{
	return _Ptr != nullptr;
}

XE::Asset & XE::Asset::operator=( std::nullptr_t )
{
	_Ptr = nullptr;
	return *this;
}

XE::Asset & XE::Asset::operator=( const Asset & val )
{
	_Ptr = val._Ptr;
	_AssetPath = val._AssetPath;
	return *this;
}

void XE::Asset::Load()
{
	if( _Ptr == nullptr )
	{
		auto obj = XE::IFramework::GetCurrentFramework()->GetServiceT< XE::IAssetsService >()->LoadObject( _AssetPath );
		LoadFinish( obj );
	}
}

void XE::Asset::AsyncLoad()
{
	if( _Ptr == nullptr )
	{
		XE::IFramework::GetCurrentFramework()->GetServiceT< XE::IAssetsService >()->AsyncLoadObject( _AssetPath, [this]( XE::ObjectPtr obj )
																									 {
																										 LoadFinish( obj );
																									 } );
	}
}

void XE::Asset::LoadFinish( const XE::ObjectPtr & val )
{
	_Ptr = val;
}

const XE::String & XE::Asset::GetAssetPath() const
{
	return _AssetPath;
}

void XE::Asset::SetAssetPath( const XE::String & val )
{
	_AssetPath = val;
}
