#include "Prefab.h"

#include "IAssetsService.h"

USING_XE

XE::Prefab::Prefab( IAssetsServicePtr val, const String& link )
	:_Service(std::move( val )), _Link( link )
{

}

const XE::String& XE::Prefab::GetLink() const
{
	return _Link;
}

XE::AssetStatus XE::Prefab::GetStatus() const
{
	return _Service->GetAssetStatus( _Link );
}
