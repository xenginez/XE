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

XE::Prefab XE::IAssetsService::CreatePrefab( const String &val )
{
	return { XE_THIS(IAssetsService), val };
}
