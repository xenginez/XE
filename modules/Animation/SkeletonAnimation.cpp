#include "SkeletonAnimation.h"

#include <ozz/animation/runtime/animation.h>

#define _p reinterpret_cast<ozz::animation::Animation*>(_Handle.GetValue())

BEG_META( Animation::SkeletonAnimation )
END_META()

Animation::SkeletonAnimation::SkeletonAnimation()
{

}

Animation::SkeletonAnimation::~SkeletonAnimation()
{

}

Animation::SkeletonAnimationHandle Animation::SkeletonAnimation::GetHandle() const
{
	return _Handle;
}

XE::float32 Animation::SkeletonAnimation::GetDuration() const
{
	return _p->duration();
}
