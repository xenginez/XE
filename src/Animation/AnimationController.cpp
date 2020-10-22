#include "AnimationController.h"

BEG_META( XE::AnimationController )
type->Property( "Skeleton", &XE::AnimationController::_Skeleton );
END_META()

XE::AnimationController::AnimationController()
{

}

XE::AnimationController::~AnimationController()
{

}

void XE::AnimationController::Startup()
{
	Super::Startup();
}

void XE::AnimationController::Clearup()
{
	Super::Clearup();

	_Skeleton = nullptr;
}

void XE::AnimationController::AssetLoad()
{
	Super::AssetLoad();

	_Skeleton.AsyncLoad();
}

const XE::AssetPtr<XE::Skeleton> & XE::AnimationController::GetSkeleton() const
{
	return _Skeleton;
}

void XE::AnimationController::SetSkeleton( const XE::AssetPtr<XE::Skeleton> & val )
{
	_Skeleton = val;
}

const XE::Array<XE::Mat4> & XE::AnimationController::GetSkeletonTransform() const
{
	return _SkeletonTransform;
}

void XE::AnimationController::SetSkeletonTransform( const XE::Array<XE::Mat4> & val )
{
	_SkeletonTransform = val;
}
