#include "IAssetsService.h"

#include "Prefab.h"

USING_XE

BEG_META(IAssetsService)
END_META()

XE::IAssetsService::IAssetsService()
{

}

XE::IAssetsService::~IAssetsService()
{

}

XE::PrefabPtr XE::IAssetsService::CreatePrefab( const String &val )
{
	return XE::make_shared<Prefab>( XE_THIS( IAssetsService ), val );
}
