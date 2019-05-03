#include "Prefab.h"

#include "IAssetsService.h"

USING_XE

XE::Prefab::Prefab()
{

}

XE::Prefab::Prefab( IAssetsServicePtr val, const String& link )
	:_Service( val ), _Link( link )
{

}

XE::Prefab::~Prefab()
{

}

XE::ObjectPtr XE::Prefab::GetClone() const
{
	return GetStatus() == AssetStatus::Ready ? _Service->GetAsset( _Link )->Clone() : nullptr;
}

XE::ObjectPtr XE::Prefab::GetReference() const
{
	return GetStatus() == AssetStatus::Ready ? _Service->GetAsset( _Link ) : nullptr;
}

XE::AssetStatus XE::Prefab::GetStatus() const
{
	return _Service->GetAssetStatus( _Link );
}

const XE::String& XE::Prefab::GetLink() const
{
	return _Link;
}
