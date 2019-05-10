#include "Skeleton.h"

USING_XE

BEGIN_META(Bone)
		type->Property("Name", &Bone::_Name);
		type->Property("Parent", &Bone::_Parent);
		type->Property("Children", &Bone::_Children);
		type->Property("Scale", &Bone::_Scale);
		type->Property("Position", &Bone::_Position);
		type->Property("Rotation", &Bone::_Rotation);
END_META()

XE::Bone::Bone()
		:_Parent(static_cast<uint64>(-1)), _Scale(Vec3::One), _Position(Vec3::Zero), _Rotation(Quat::Identity)
{

}

XE::Bone::~Bone()
{

}

BEGIN_META(VertexWeight)
		type->Property("Weight0", &VertexWeight::Weight0);
		type->Property("Weight1", &VertexWeight::Weight1);
		type->Property("Weight2", &VertexWeight::Weight2);
		type->Property("Weight3", &VertexWeight::Weight3);
		type->Property("Bone0", &VertexWeight::Bone0);
		type->Property("Bone1", &VertexWeight::Bone1);
		type->Property("Bone2", &VertexWeight::Bone2);
		type->Property("Bone3", &VertexWeight::Bone3);
END_META()

XE::VertexWeight::VertexWeight()
		:Weight0(0),
		Weight1(0),
		Weight2(0),
		Weight3(0),
		Bone0(static_cast<uint64>(-1)),
		Bone1(static_cast<uint64>(-1)),
		Bone2(static_cast<uint64>(-1)),
		Bone3(static_cast<uint64>(-1))
{

}

XE::VertexWeight::~VertexWeight()
{

}


BEGIN_META(Skeleton)
		type->Property("Bones", &Skeleton::_Bones);
		type->Property("Weight", &Skeleton::_Weight);
		type->Property("RootBone", &Skeleton::_RootBone);
END_META()

XE::Skeleton::Skeleton()
		:_RootBone(static_cast<uint64>(-1))
{

}

XE::Skeleton::~Skeleton()
{

}

XE::uint64 XE::Skeleton::GetRootBone() const
{
	return _RootBone;
}

XE::uint64 XE::Skeleton::GetBoneCount() const
{
	return _Bones.size();
}

const XE::Array < XE::Bone > &XE::Skeleton::GetBones() const
{
	return _Bones;
}

const XE::String &XE::Skeleton::GetBoneName( XE::uint64 val ) const
{
	XE_ASSERT(val < _Bones.size());
	
	return _Bones[val]._Name;
}

XE::uint64 XE::Skeleton::GetBoneIndex( const XE::String &val ) const
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

const XE::Vec3 &XE::Skeleton::GetBoneLocalScale( XE::uint64 bone ) const
{
	XE_ASSERT(bone < _Bones.size());
	
	return _Bones[bone]._Scale;
}

void XE::Skeleton::SetBoneLocalScale( XE::uint64 bone, const XE::Vec3 &val )
{
	XE_ASSERT(bone < _Bones.size());
	
	_Bones[bone]._Scale = val;
}

const XE::Vec3 &XE::Skeleton::GetBoneLocalPosition( XE::uint64 bone ) const
{
	XE_ASSERT(bone < _Bones.size());
	
	return _Bones[bone]._Position;
}

void XE::Skeleton::SetBoneLocalPosition( XE::uint64 bone, const XE::Vec3 &val )
{
	XE_ASSERT(bone < _Bones.size());
	
	_Bones[bone]._Position = val;
}

const XE::Quat &XE::Skeleton::GetBoneLocalRotation( XE::uint64 bone ) const
{
	XE_ASSERT(bone < _Bones.size());
	
	return _Bones[bone]._Rotation;
}

void XE::Skeleton::SetBoneLocalRotation( XE::uint64 bone, const XE::Quat &val )
{
	XE_ASSERT(bone < _Bones.size());
	
	_Bones[bone]._Rotation = val;
}

const XE::Mat4 &XE::Skeleton::GetBoneWorldTransform( XE::uint64 val ) const
{
	XE_ASSERT(val < _Bones.size());
	
	return _Bones[val]._WorldTransform;
}

void XE::Skeleton::SetBoneWorldTransform( XE::uint64 bone, const XE::Mat4 &val )
{
	XE_ASSERT(bone < _Bones.size());
	
	_Bones[bone]._WorldTransform = val;
}

const Array < XE::uint64 > &XE::Skeleton::GetBoneChildren( XE::uint64 val ) const
{
	XE_ASSERT(val < _Bones.size());
	
	return _Bones[val]._Children;
}

XE::uint64 XE::Skeleton::GetVertexWeightCount() const
{
	return _Weight.size();
}

const XE::Array < VertexWeight > &XE::Skeleton::GetVertexWeights() const
{
	return _Weight;
}

float XE::Skeleton::GetVertexWeight0( XE::uint64 val ) const
{
	XE_ASSERT(val < _Weight.size());
	
	return _Weight[val].Weight0;
}

void XE::Skeleton::SetVertexWeight0( XE::uint64 vertex, float val )
{
	XE_ASSERT(vertex < _Weight.size());
	
	_Weight[vertex].Weight0 = val;
}

float XE::Skeleton::GetVertexWeight1( XE::uint64 val ) const
{
	XE_ASSERT(val < _Weight.size());
	
	return _Weight[val].Weight1;
}

void XE::Skeleton::SetVertexWeight1( XE::uint64 vertex, float val )
{
	XE_ASSERT(vertex < _Weight.size());
	
	_Weight[vertex].Weight1 = val;
}

float XE::Skeleton::GetVertexWeight2( XE::uint64 val ) const
{
	XE_ASSERT(val < _Weight.size());
	
	return _Weight[val].Weight2;
}

void XE::Skeleton::SetVertexWeight2( XE::uint64 vertex, float val )
{
	XE_ASSERT(vertex < _Weight.size());
	
	_Weight[vertex].Weight2 = val;
}

float XE::Skeleton::GetVertexWeight3( XE::uint64 val ) const
{
	XE_ASSERT(val < _Weight.size());
	
	return _Weight[val].Weight3;
}

void XE::Skeleton::SetVertexWeight3( XE::uint64 vertex, float val )
{
	XE_ASSERT(vertex < _Weight.size());
	
	_Weight[vertex].Weight3 = val;
}

XE::uint64 XE::Skeleton::GetVertexWeightBone0( XE::uint64 val ) const
{
	XE_ASSERT(val < _Weight.size());
	
	return _Weight[val].Bone0;
}

void XE::Skeleton::SetVertexWeightBone0( XE::uint64 vertex, XE::uint64 val )
{
	XE_ASSERT(vertex < _Weight.size());
	
	_Weight[vertex].Bone0 = val;
}

XE::uint64 XE::Skeleton::GetVertexWeightBone1( XE::uint64 val ) const
{
	XE_ASSERT(val < _Weight.size());
	
	return _Weight[val].Bone1;
}

void XE::Skeleton::SetVertexWeightBone1( XE::uint64 vertex, XE::uint64 val )
{
	XE_ASSERT(vertex < _Weight.size());
	
	_Weight[vertex].Bone1 = val;
}

XE::uint64 XE::Skeleton::GetVertexWeightBone2( XE::uint64 val ) const
{
	XE_ASSERT(val < _Weight.size());
	
	return _Weight[val].Bone2;
}

void XE::Skeleton::SetVertexWeightBone2( XE::uint64 vertex, XE::uint64 val )
{
	XE_ASSERT(vertex < _Weight.size());
	
	_Weight[vertex].Bone2 = val;
}

XE::uint64 XE::Skeleton::GetVertexWeightBone3( XE::uint64 val ) const
{
	XE_ASSERT(val < _Weight.size());
	
	return _Weight[val].Bone3;
}

void XE::Skeleton::SetVertexWeightBone3( XE::uint64 vertex, XE::uint64 val )
{
	XE_ASSERT(vertex < _Weight.size());
	
	_Weight[vertex].Bone3 = val;
}
