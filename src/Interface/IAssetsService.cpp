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

XE::Prefab XE::IAssetsService::CreatePrefab( const String &val )
{
	XE::Prefab prefab;

	prefab.SetLink( val );

	return prefab;
}
