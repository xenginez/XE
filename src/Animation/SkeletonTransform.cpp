#include "SkeletonTransform.h"

#include <ozz/base/maths/vec_float.h>
#include <ozz/base/containers/vector.h>
#include <ozz/base/maths/soa_transform.h>

BEG_META( XE::SkeletonTransform )
END_META()

struct XE::SkeletonTransform::Private
{
	XE::Array< XE::Mat4 > _Transform;
	ozz::vector<ozz::math::Float4x4> _Models;
}

XE::SkeletonTransform::SkeletonTransform()
	:_p( new Private )
{

}

XE::SkeletonTransform::~SkeletonTransform()
{
	delete _p;
}

XE::SkeletonTransformHandle XE::SkeletonTransform::GetHandle() const
{
	return reinterpret_cast< XE::uint64 >( &_p->_Models );
}

const XE::Array< XE::Mat4 > & XE::SkeletonTransform::GetTransform() const
{
	return _p->_Transform;
}

void XE::SkeletonTransform::SetTransform( const XE::Array< XE::Mat4 > & val )
{
	_p->_Transform = val;
}
