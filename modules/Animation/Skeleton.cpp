#include "Skeleton.h"

BEG_META( Animation::Skeleton )
END_META()

Animation::Skeleton::Skeleton()
{

}

Animation::Skeleton::~Skeleton()
{

}

Animation::SkeletonHandle Animation::Skeleton::GetHandle() const
{
	return _Handle;
}
