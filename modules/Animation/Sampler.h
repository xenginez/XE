/*!
 * \file	Sampler.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/28
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef SAMPLER_H__5E8A9D05_7231_43C5_B284_F21EE7C2E40C
#define SAMPLER_H__5E8A9D05_7231_43C5_B284_F21EE7C2E40C

#include "Type.h"

BEG_ANIMATION_NAMESPACE

class ANIMATION_API Sampler final
{
public:
	Sampler();

	~Sampler();

public:
	void Startup( Animation::SkeletonPtr skeleton, Animation::SkeletonAnimationPtr animation );

	bool Update( XE::float32 time );

	void Clearup();

public:
	void * GetLocal() const;

private:
	void * _Local;
	void * _Cache;
	Animation::SkeletonPtr _Skeleton;
	Animation::SkeletonAnimationPtr _Animation;
};

END_ANIMATION_NAMESPACE

#endif // SAMPLER_H__5E8A9D05_7231_43C5_B284_F21EE7C2E40C
