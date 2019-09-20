#include "Skeleton.h"

USING_XE

BEG_META( BoneJoint )
type->Property( "Name", &BoneJoint::Name );
type->Property( "Parent", &BoneJoint::Parent );
type->Property( "Children", &BoneJoint::Children );
type->Property( "Transform", &BoneJoint::Transform );
END_META()


BEG_META( Skeleton )
type->Property( "BoneJoints", &Skeleton::_BoneJoints );
END_META()

XE::Skeleton::Skeleton()
{

}

XE::Skeleton::~Skeleton()
{

}

XE::uint32 XE::Skeleton::GetBoneJointCount() const
{
	return static_cast< XE::uint32 >( _BoneJoints.size() );
}

XE::uint32 XE::Skeleton::FindBoneJointIndex( const XE::String & val ) const
{
	for( XE::uint32 i = 0; i < _BoneJoints.size(); ++i )
	{
		if( _BoneJoints[i].Name == val )
		{
			return i;
		}
	}

	return npos;
}

const XE::String & XE::Skeleton::GetBoneJointName( XE::uint32 val ) const
{
	return _BoneJoints[val].Name;
}

XE::uint32 XE::Skeleton::GetBoneJointParent( XE::uint32 val ) const
{
	return _BoneJoints[val].Parent;
}

const XE::Mat4 & XE::Skeleton::GetBoneJointTransform( XE::uint32 val ) const
{
	return _BoneJoints[val].Transform;
}

const XE::Array<XE::uint32> & XE::Skeleton::GetBoneJointChildren( XE::uint32 val ) const
{
	return _BoneJoints[val].Children;
}

const XE::Array<XE::BoneJoint> & XE::Skeleton::GetBoneJoints() const
{
	return _BoneJoints;
}

void XE::Skeleton::SetBoneJointTransform( XE::uint32 val, const XE::Mat4 & mat )
{
	_BoneJoints[val].Transform = mat;
}
