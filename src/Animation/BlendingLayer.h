/*!
 * \file	BlendingLayer.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/24
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef BLENDINGLAYER_H__F2A8E27B_AAD1_4225_AB42_5DFC95B015CC
#define BLENDINGLAYER_H__F2A8E27B_AAD1_4225_AB42_5DFC95B015CC

#include "Utils/Asset.h"

#include "AnimationState.h"
#include "SkeletonAnimation.h"

BEG_XE_NAMESPACE

class XE_API BlendingLayer : public XE::Object
{
	OBJECT( BlendingLayer, Object )

public:
	BlendingLayer();

	~BlendingLayer() override;

public:
	XE::float32 GetWeight() const;

	void SetWeight( XE::float32 val );

	const XE::String & GetName() const;

	void SetName( const XE::String & val );

	const XE::AssetPtr< XE::SkeletonAnimation > & GetSkeletonAnimation() const;

	void SetSkeletonAnimation( const XE::AssetPtr< XE::SkeletonAnimation > & val );

public:
	void AssetLoad() override;

private:
	XE::String _Name;
	XE::float32 _Weight = 1.0f;
	XE::AssetPtr< XE::SkeletonAnimation > _Animation;
};

END_XE_NAMESPACE

#endif // BLENDINGLAYER_H__F2A8E27B_AAD1_4225_AB42_5DFC95B015CC
