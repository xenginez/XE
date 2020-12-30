#include "BlendLayer.h"

#include <ozz/animation/runtime/skeleton.h>
#include <ozz/animation/runtime/animation.h>

BEG_META( Animation::BlendLayer )
type->Property( "Weight", &Animation::BlendLayer::_Weight );
type->Property( "SkeletonAnimation", &Animation::BlendLayer::_SkeletonAnimation );
END_META()

Animation::BlendLayer::BlendLayer()
{

}

Animation::BlendLayer::~BlendLayer()
{

}

void Animation::BlendLayer::Startup( Animation::SkeletonPtr val )
{
	_Sampler.Startup( val, _SkeletonAnimation.GetShared() );
}

void Animation::BlendLayer::Update( XE::float32 time )
{
	_Sampler.Update( time );
}

void Animation::BlendLayer::Clearup()
{
	_Sampler.Clearup();
}

void Animation::BlendLayer::AssetLoad()
{
	_SkeletonAnimation.AsyncLoad();
}

XE::float32 Animation::BlendLayer::GetWeight() const
{
	return _Weight;
}

Animation::SkeletonAnimationPtr Animation::BlendLayer::GetSkeletonAnimation() const
{
	return _SkeletonAnimation.GetShared();
}

const Animation::Sampler & Animation::BlendLayer::GetAnimationSampler() const
{
	return _Sampler;
}
