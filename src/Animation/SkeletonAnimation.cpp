#include "SkeletonAnimation.h"

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
