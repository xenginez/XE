#include "Prefab.h"

#include "IAssetsService.h"

USING_XE

XE::Prefab::Prefab( IAssetsServicePtr val, const String& link )
	:_Service(std::move( val )), _Link( link )
{

}

XE::ObjectPtr XE::Prefab::GetClone() const
{
	return GetStatus() == AssetStatus::Ready ? _Service->GetAsset( _Link )->Clone() : nullptr;
}

XE::ObjectCPtr XE::Prefab::GetReference() const
{
	return GetStatus() == AssetStatus::Ready ? _Service->GetAsset( _Link ) : nullptr;
}

const XE::String& XE::Prefab::GetLink() const
{
	return _Link;
}

XE::AssetStatus XE::Prefab::GetStatus() const
{
	return _Service->GetAssetStatus( _Link );
}
