#include "Skeleton.h"

USING_XE

BEG_META( Joint )
type->Property( "Name", &Joint::Name );
type->Property( "Parent", &Joint::Parent );
type->Property( "Children", &Joint::Children );
type->Property( "Transform", &Joint::Transform );
END_META()


BEG_META( Skeleton )
type->Property( "Joints", &Skeleton::_Joints );
END_META()

XE::Skeleton::Skeleton()
{

}

XE::Skeleton::~Skeleton()
{

}

XE::uint64 XE::Skeleton::GetJointCount() const
{
	return _Joints.size();
}

XE::uint64 XE::Skeleton::FindJointIndex( const XE::String & val ) const
{
	for( XE::uint64 i = 0; i < _Joints.size(); ++i )
	{
		if( _Joints[i].Name == val )
		{
			return i;
		}
	}

	return npos;
}

const XE::String & XE::Skeleton::GetJointName( XE::uint64 val ) const
{
	return _Joints[val].Name;
}

XE::uint64 XE::Skeleton::GetJointParent( XE::uint64 val ) const
{
	return _Joints[val].Parent;
}

const XE::Mat4 & XE::Skeleton::GetJointTransform( XE::uint64 val ) const
{
	return _Joints[val].Transform;
}

const XE::Array<XE::uint64> & XE::Skeleton::GetJointChildren( XE::uint64 val ) const
{
	return _Joints[val].Children;
}

const XE::Array<XE::Joint> & XE::Skeleton::GetJoints() const
{
	return _Joints;
}

void XE::Skeleton::SetJointTransform( XE::uint64 val, const XE::Mat4 & mat )
{
	_Joints[val].Transform = mat;
}
