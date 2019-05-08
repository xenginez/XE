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

class GRAPHICS_API Bone : public XE::Object
{
	OBJECT( Bone, Object )

public:
	Bone();
	
	~Bone() override;
};

class GRAPHICS_API Joint : public XE::Object
{
	OBJECT( Joint, Object )

public:
	Joint();
	
	~Joint() override;
};

class GRAPHICS_API Skeleton : public XE::Object
{
	OBJECT( Skeleton, Object )
	
public:
	Skeleton();
	
	~Skeleton() override;

public:
	Array < BonePtr > _Bones;
	Array < JointPtr > _Joints;
};

END_XE_NAMESAPCE

#endif //__SKELETON_H__9AEB194C_02DF_4C42_BAAF_AE192AC93E1F
