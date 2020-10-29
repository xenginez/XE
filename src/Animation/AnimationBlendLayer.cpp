#include "AnimationBlendLayer.h"

#include <ozz/animation/runtime/skeleton.h>
#include <ozz/animation/runtime/animation.h>

BEG_META( XE::AnimationBlendLayer )
type->Property( "Weight", &XE::AnimationBlendLayer::_Weight );
type->Property( "SkeletonAnimation", &XE::AnimationBlendLayer::_SkeletonAnimation );
END_META()

XE::AnimationBlendLayer::AnimationBlendLayer()
{

}

XE::AnimationBlendLayer::~AnimationBlendLayer()
{

}

void XE::AnimationBlendLayer::Startup( XE::SkeletonPtr val )
{
	_Sampler.Startup( val, _SkeletonAnimation.GetShared() );
}

void XE::AnimationBlendLayer::Update( XE::float32 time )
{
	_Sampler.Update( time );
}

void XE::AnimationBlendLayer::Clearup()
{
	_Sampler.Clearup();
}

void XE::AnimationBlendLayer::AssetLoad()
{
	_SkeletonAnimation.AsyncLoad();
}

XE::float32 XE::AnimationBlendLayer::GetWeight() const
{
	return _Weight;
}

XE::SkeletonAnimationPtr XE::AnimationBlendLayer::GetSkeletonAnimation() const
{
	return _SkeletonAnimation.GetShared();
}

const XE::AnimationSampler & XE::AnimationBlendLayer::GetAnimationSampler() const
{
	return _Sampler;
}
