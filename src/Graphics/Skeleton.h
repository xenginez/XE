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

class GRAPHICS_API Weight
{
	OBJECT(Weight)

public:
	Weight();
	
	~Weight();

public:
	float Weight0;
	float Weight1;
	float Weight2;
	float Weight3;
	XE::uint32 Bone0;
	XE::uint32 Bone1;
	XE::uint32 Bone2;
	XE::uint32 Bone3;
};

class GRAPHICS_API Skeleton : public XE::Object
{
	OBJECT(Skeleton, Object)

public:
	Skeleton();
	
	~Skeleton() override;

public:
	XE::uint64 GetBoneCount() const;
	
	XE::uint64 GetRootBoneIndex() const;
	
	XE::uint64 GetBoneIndexFromName( const String &val ) const;

public:
	Bone * GetBone( XE::uint64 val );
	
	Bone * GetBoneFromName( const String &val );
	
	const Array < Bone > &GetBones() const;

public:
	Weight * GetWeight( XE::uint64 val );
	
	const Array < Weight > &GetWeights() const;
	
public:
	XE::uint64 _RootBone;
	Array < Bone > _Bones;
	Array < Weight > _Weight;
};

END_XE_NAMESAPCE

#endif //__SKELETON_H__9AEB194C_02DF_4C42_BAAF_AE192AC93E1F
