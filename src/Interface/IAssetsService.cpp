#include "IAssetsService.h"

#include "Prefab.h"

USING_XE

BEGIN_META( IAssetsService )
END_META()

XE::IAssetsService::IAssetsService()
{

}

XE::IAssetsService::~IAssetsService()
{

}

XE::PrefabPtr XE::IAssetsService::CreatePrefab(const String& val ) const
{
	return XE::make_shared<XE::Prefab>(XE_THIS(IAssetsServicePtr), val);
}
