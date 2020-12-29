/*!
 * \file	SkeletonAnimation.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/19
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef SKELETONANIMATION_H__9E0377FC_ACF8_42A6_8311_5FEA82308F78
#define SKELETONANIMATION_H__9E0377FC_ACF8_42A6_8311_5FEA82308F78

#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API SkeletonAnimation : public XE::Object
{
	OBJECT( SkeletonAnimation, Object )

public:
	SkeletonAnimation();

	~SkeletonAnimation() override;

public:
	XE::SkeletonAnimationHandle GetHandle() const;

public:
	XE::float32 GetDuration() const;

private:
	XE::SkeletonAnimationHandle _Handle;
};

END_XE_NAMESPACE

#endif // SKELETONANIMATION_H__9E0377FC_ACF8_42A6_8311_5FEA82308F78
