#include "Asset.h"

#include "Interface/IFramework.h"
#include "Interface/IAssetsService.h"

BEG_META( XE::Asset )
	type->Property( "AssetPath", &XE::Asset::GetAssetPath, &XE::Asset::SetAssetPath );
END_META()

XE::Asset::Asset()
{

}

XE::Asset::Asset( Asset && val )
{
	Swap( std::forward< Asset >( val ) );
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

XE::Asset & XE::Asset::operator=( Asset && val )
{
	Swap( std::forward< Asset >( val ) );
	return *this;
}

XE::Asset & XE::Asset::operator=( const Asset & val )
{
	_Ptr = val._Ptr;
	_AssetPath = val._AssetPath;
	return *this;
}

void XE::Asset::Swap( Asset && val )
{
	std::swap( _Ptr, val._Ptr );
	std::swap( _AssetPath, val._AssetPath );
}

void XE::Asset::Load()
{
	auto obj = XE::IFramework::GetCurrentFramework()->GetServiceT< XE::IAssetsService >()->LoadObject( _AssetPath );
	LoadFinish( obj );
}

void XE::Asset::AsyncLoad()
{
	XE::IFramework::GetCurrentFramework()->GetServiceT< XE::IAssetsService >()->AsyncLoadObject( _AssetPath, std::bind( &XE::Asset::LoadFinish, this, std::placeholders::_1 ) );
}

void XE::Asset::LoadFinish( const XE::ObjectPtr & val )
{
	_Ptr = val;
}

const std::filesystem::path & XE::Asset::GetAssetPath() const
{
	return _AssetPath;
}

void XE::Asset::SetAssetPath( const std::filesystem::path & val )
{
	_AssetPath = val;
}
