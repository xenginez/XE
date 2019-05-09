#include "Skeleton.h"

USING_XE

BEGIN_META(Bone)
		type->Property("Name", &Bone::_Name);
		type->Property("Parent", &Bone::_Parent);
		type->Property("Children", &Bone::_Children);
		type->Property("Scale", &Bone::_Scale);
		type->Property("Position", &Bone::_Position);
		type->Property("Rotation", &Bone::_Rotation);
		type->Property("WorldTransform", &Bone::_WorldTransform);
END_META()

XE::Bone::Bone()
		:_Parent(0), _Scale(Vec3::One), _Position(Vec3::Zero), _Rotation(Quat::Identity)
{

}

XE::Bone::~Bone()
{

}

BEGIN_META(Skeleton)
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

XE::uint64 XE::Skeleton::GetRootBoneIndex() const
{
	return _RootBone;
}

XE::uint64 XE::Skeleton::GetBoneIndexFromName( const XE::String &val ) const
{
	for( uint64 i = 0; i < _Bones.size(); ++i )
	{
		if( _Bones[i]._Name == val )
		{
			return i;
		}
	}
	
	return static_cast<uint64>(-1);
}

XE::Bone * XE::Skeleton::GetBone( XE::uint64 val )
{
	XE_ASSERT(val < _Bones.size());
	
	return &_Bones[val];
}

XE::Bone * XE::Skeleton::GetBoneFromName( const XE::String &val )
{
	auto i = GetBoneIndexFromName(val);
	
	XE_ASSERT(i != -1);
	
	return &_Bones[i];
}

const XE::Array < XE::Bone > &XE::Skeleton::GetBones() const
{
	return _Bones;
}
