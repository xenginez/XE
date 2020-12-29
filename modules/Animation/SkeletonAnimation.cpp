#include "SkeletonAnimation.h"

#include <ozz/animation/runtime/animation.h>

#define _p reinterpret_cast<ozz::animation::Animation*>(_Handle.GetValue())

BEG_META( XE::SkeletonAnimation )
END_META()

XE::SkeletonAnimation::SkeletonAnimation()
{

}

XE::SkeletonAnimation::~SkeletonAnimation()
{

}

XE::SkeletonAnimationHandle XE::SkeletonAnimation::GetHandle() const
{
	return _Handle;
}

XE::float32 XE::SkeletonAnimation::GetDuration() const
{
	return _p->duration();
}
