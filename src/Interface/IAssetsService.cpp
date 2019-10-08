#include "IAssetsService.h"

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
	auto prefab = XE::make_shared<Prefab>();

	prefab->SetLink( val );

	return prefab;
}
