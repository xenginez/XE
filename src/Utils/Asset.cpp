#include "Asset.h"

#include <Interface/IFramework.h>
#include <Interface/IAssetsService.h>

USING_XE

XE::ObjectPtr AssetLoad::Load( const XE::String & val )
{
	return XE::IFramework::GetCurrentFramework()->GetServiceT<XE::IAssetsService>()->Load( val );
}

void AssetLoad::AsyncLoad( const XE::String & val )
{
	XE::IFramework::GetCurrentFramework()->GetServiceT<XE::IAssetsService>()->AsyncLoad( val );
}
