/*!
 * \file	AnimationBlendLayer.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/28
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATIONBLENDLAYER_H__1D97366D_4AE4_432E_9BCF_F5B0C76A6B40
#define ANIMATIONBLENDLAYER_H__1D97366D_4AE4_432E_9BCF_F5B0C76A6B40

#include "Utils/Asset.h"

#include "AnimationSampler.h"
#include "SkeletonAnimation.h"

BEG_XE_NAMESPACE

class XE_API AnimationBlendLayer : XE::Object
{
	OBJECT( AnimationBlendLayer, Object )

public:
	AnimationBlendLayer();

	~AnimationBlendLayer();

public:
	void Startup( XE::SkeletonPtr val );

	void Update( XE::float32 time );

	void Clearup();

	void AssetLoad() override;

public:
	XE::float32 GetWeight() const;

	XE::SkeletonAnimationPtr GetSkeletonAnimation() const;

	const XE::AnimationSampler & GetAnimationSampler() const;

private:
	XE::float32 _Weight;
	AnimationSampler _Sampler;
	XE::AssetPtr< XE::SkeletonAnimation > _SkeletonAnimation;
};

END_XE_NAMESPACE

#endif // ANIMATIONBLENDLAYER_H__1D97366D_4AE4_432E_9BCF_F5B0C76A6B40
