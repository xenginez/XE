#include "Skeleton.h"

USING_XE

BEG_META( Bone )
type->Property( "Name", &Bone::Name );
type->Property( "Parent", &Bone::Parent );
type->Property( "Transform", &Bone::Transform );
END_META()


BEG_META( Skeleton )
type->Property( "Bones", &Skeleton::_Bones );
END_META()

XE::Skeleton::Skeleton()
{

}

XE::Skeleton::~Skeleton()
{

}

XE::uint64 XE::Skeleton::GetBoneCount() const
{
	return _Bones.size();
}

XE::uint64 XE::Skeleton::FindBoneIndex( const String & val ) const
{
	for( XE::uint64 i = 0; i < _Bones.size(); ++i )
	{
		if( _Bones[i].Name == val )
		{
			return i;
		}
	}

	return npos;
}

const XE::String & XE::Skeleton::GetBoneName( XE::uint64 val ) const
{
	return _Bones[val].Name;
}

XE::uint64 XE::Skeleton::GetBoneParent( XE::uint64 val ) const
{
	return _Bones[val].Parent;
}

const XE::Mat4 & XE::Skeleton::GetBoneTransform( XE::uint64 val ) const
{
	return _Bones[val].Transform;
}

void XE::Skeleton::SetBoneTransform( XE::uint64 val, const Mat4 & mat )
{
	_Bones[val].Transform = mat;
}

const XE::Array<XE::Bone> & XE::Skeleton::GetBones() const
{
	return _Bones;
}
