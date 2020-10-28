/*!
 * \file	AnimationSampler.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/28
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATIONSAMPLER_H__5E8A9D05_7231_43C5_B284_F21EE7C2E40C
#define ANIMATIONSAMPLER_H__5E8A9D05_7231_43C5_B284_F21EE7C2E40C

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API AnimationSampler final
{
public:
	AnimationSampler();

	~AnimationSampler();

public:
	void Startup( XE::SkeletonPtr skeleton, XE::SkeletonAnimationPtr animation );

	bool Update( XE::float32 time );

	void Clearup();

public:
	void * GetLocal() const;

private:
	void * _Local;
	void * _Cache;
	XE::SkeletonPtr _Skeleton;
	XE::SkeletonAnimationPtr _Animation;
};

END_XE_NAMESPACE

#endif // ANIMATIONSAMPLER_H__5E8A9D05_7231_43C5_B284_F21EE7C2E40C
