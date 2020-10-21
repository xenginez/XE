#include "Skeleton.h"

BEG_META( XE::Skeleton )
END_META()

XE::Skeleton::Skeleton()
{

}

XE::Skeleton::~Skeleton()
{

}

XE::SkeletonHandle XE::Skeleton::GetHandle() const
{
	return _Handle;
}
