/*!
 * \file	BlendLayer.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/28
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef BLENDLAYER_H__1D97366D_4AE4_432E_9BCF_F5B0C76A6B40
#define BLENDLAYER_H__1D97366D_4AE4_432E_9BCF_F5B0C76A6B40

#include "Sampler.h"
#include "SkeletonAnimation.h"

BEG_ANIMATION_NAMESPACE

class ANIMATION_API BlendLayer : XE::Object
{
	OBJECT( BlendLayer, Object )

public:
	BlendLayer();

	~BlendLayer();

public:
	void Startup( Animation::SkeletonPtr val );

	void Update( XE::float32 time );

	void Clearup();

	void AssetLoad() override;

public:
	XE::float32 GetWeight() const;

	Animation::SkeletonAnimationPtr GetSkeletonAnimation() const;

	const Animation::Sampler & GetAnimationSampler() const;

private:
	XE::float32 _Weight;
	Sampler _Sampler;
	XE::AssetPtr< Animation::SkeletonAnimation > _SkeletonAnimation;
};

END_ANIMATION_NAMESPACE

#endif // BLENDLAYER_H__1D97366D_4AE4_432E_9BCF_F5B0C76A6B40
