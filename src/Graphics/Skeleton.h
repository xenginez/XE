/*!
 * \file    Skeleton.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-08
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __SKELETON_H__9AEB194C_02DF_4C42_BAAF_AE192AC93E1F
#define __SKELETON_H__9AEB194C_02DF_4C42_BAAF_AE192AC93E1F

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API Bone
{
	OBJECT(Bone)

public:
	Bone();
	
	~Bone();

public:
	String _Name;
	
	XE::uint64 _Parent;
	Array < XE::uint64 > _Children;
	
	Vec3 _Scale;
	Vec3 _Position;
	Quat _Rotation;
	Mat4 _WorldTransform;
};

class GRAPHICS_API VertexWeight
{
	OBJECT(VertexWeight)

public:
	VertexWeight();
	
	~VertexWeight();

public:
	float Weight0;
	float Weight1;
	float Weight2;
	float Weight3;
	XE::uint64 Bone0;
	XE::uint64 Bone1;
	XE::uint64 Bone2;
	XE::uint64 Bone3;
};

class GRAPHICS_API Skeleton : public XE::Object
{
	OBJECT(Skeleton, Object)

public:
	Skeleton();
	
	~Skeleton() override;

public:
	XE::uint64 GetRootBone() const;
	
	XE::uint64 GetBoneCount() const;
	
	const Array < Bone > &GetBones() const;
	
	const String &GetBoneName( XE::uint64 val ) const;
	
	XE::uint64 GetBoneIndex( const String &val ) const;
	
	const XE::Vec3 &GetBoneLocalScale( XE::uint64 bone ) const;
	
	void SetBoneLocalScale( XE::uint64 bone, const XE::Vec3 &val );
	
	const XE::Vec3 &GetBoneLocalPosition( XE::uint64 bone ) const;
	
	void SetBoneLocalPosition( XE::uint64 bone, const XE::Vec3 &val );
	
	const XE::Quat &GetBoneLocalRotation( XE::uint64 bone ) const;
	
	void SetBoneLocalRotation( XE::uint64 bone, const XE::Quat &val );
	
	const XE::Mat4 &GetBoneWorldTransform( XE::uint64 bone ) const;
	
	void SetBoneWorldTransform( XE::uint64 bone, const XE::Mat4 &val );
	
	const Array < XE::uint64 > &GetBoneChildren( XE::uint64 val ) const;

public:
	XE::uint64 GetVertexWeightCount() const;
	
	const Array < VertexWeight > &GetVertexWeights() const;
	
	float GetVertexWeight0( XE::uint64 val ) const;
	
	void SetVertexWeight0( XE::uint64 vertex, float val );
	
	float GetVertexWeight1( XE::uint64 val ) const;
	
	void SetVertexWeight1( XE::uint64 vertex, float val );
	
	float GetVertexWeight2( XE::uint64 val ) const;
	
	void SetVertexWeight2( XE::uint64 vertex, float val );
	
	float GetVertexWeight3( XE::uint64 val ) const;
	
	void SetVertexWeight3( XE::uint64 vertex, float val );
	
	XE::uint64 GetVertexWeightBone0( XE::uint64 val ) const;
	
	void SetVertexWeightBone0( XE::uint64 vertex, XE::uint64 val );
	
	XE::uint64 GetVertexWeightBone1( XE::uint64 val ) const;
	
	void SetVertexWeightBone1( XE::uint64 vertex, XE::uint64 val );
	
	XE::uint64 GetVertexWeightBone2( XE::uint64 val ) const;
	
	void SetVertexWeightBone2( XE::uint64 vertex, XE::uint64 val );
	
	XE::uint64 GetVertexWeightBone3( XE::uint64 val ) const;
	
	void SetVertexWeightBone3( XE::uint64 vertex, XE::uint64 val );

public:
	XE::uint64 _RootBone;
	Array < Bone > _Bones;
	Array < VertexWeight > _Weight;
};

END_XE_NAMESAPCE

#endif //__SKELETON_H__9AEB194C_02DF_4C42_BAAF_AE192AC93E1F
