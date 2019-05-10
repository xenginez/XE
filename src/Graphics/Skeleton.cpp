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
		:_Parent(static_cast<uint64>(-1)), _Scale(Vec3::One), _Position(Vec3::Zero), _Rotation(Quat::Identity)
{

}

XE::Bone::~Bone()
{

}

BEGIN_META(Weight)
		type->Property("Weight0", &Weight::Weight0);
		type->Property("Weight1", &Weight::Weight1);
		type->Property("Weight2", &Weight::Weight2);
		type->Property("Weight3", &Weight::Weight3);
		type->Property("Bone0", &Weight::Bone0);
		type->Property("Bone1", &Weight::Bone1);
		type->Property("Bone2", &Weight::Bone2);
		type->Property("Bone3", &Weight::Bone3);
END_META()

XE::Weight::Weight()
		:Weight0(0),
		Weight1(0),
		Weight2(0),
		Weight3(0),
		Bone0(static_cast<uint32>(-1)),
		Bone1(static_cast<uint32>(-1)),
		Bone2(static_cast<uint32>(-1)),
		Bone3(static_cast<uint32>(-1))
{

}

XE::Weight::~Weight()
{

}


BEGIN_META(Skeleton)
		type->Property("Bones", &Skeleton::_Bones);
		type->Property("Weight", &Skeleton::_Weight);
		type->Property("RootBone", &Skeleton::_RootBone);
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

XE::Weight * XE::Skeleton::GetWeight( XE::uint64 val )
{
	XE_ASSERT(val < _Weight.size());
	
	return &_Weight[val];
}

const XE::Array < Weight > &XE::Skeleton::GetWeights() const
{
	return _Weight;
}
