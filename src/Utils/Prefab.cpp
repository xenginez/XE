#include "Prefab.h"

#include "Interface/IFramework.h"
#include "Interface/IAssetsService.h"

USING_XE

BEG_META(Prefab)
		type->Property("Link", &Prefab::GetLink, &Prefab::SetLink);
END_META()

XE::Prefab::Prefab()
{

}

XE::Prefab::~Prefab()
{

}

const XE::String &XE::Prefab::GetLink() const
{
	return _Link;
}

void Prefab::SetLink( const XE::String &val )
{
	_Link = val;
}

XE::AssetStatus XE::Prefab::GetStatus() const
{
	return IFramework::GetCurrentFramework()->GetAssetsService()->GetAssetStatus(_Link);
}

XE::ReflectObjectPtr Prefab::GetReference() const
{
	return GetStatus() == AssetStatus::Ready ? IFramework::GetCurrentFramework()->GetAssetsService()->GetAsset(_Link)
											 : nullptr;
}
