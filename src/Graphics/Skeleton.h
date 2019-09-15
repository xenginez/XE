/*!
 * \file	Skeleton.h
 *
 * \author	ZhengYuanQing
 * \date	2019/07/28
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef SKELETON_H__035FBC00_8817_4635_8785_EF71ED728BE3
#define SKELETON_H__035FBC00_8817_4635_8785_EF71ED728BE3

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API BoneJoint : public XE::Object
{
	OBJECT( BoneJoint, Object )

public:
	XE::String Name;
	XE::uint64 Parent;
	XE::Mat4 Transform;
	XE::Array<XE::uint64> Children;
};
DECL_META_CLASS( GRAPHICS_API, BoneJoint );

class GRAPHICS_API Skeleton : public XE::Object
{
	OBJECT( Skeleton, Object )

public:
	static constexpr XE::uint64 npos = std::numeric_limits<XE::uint64>::max();

public:
	Skeleton();

	~Skeleton() override;

public:
	XE::uint64 GetBoneJointCount() const;

	XE::uint64 FindBoneJointIndex( const XE::String & val ) const;

	const XE::String & GetBoneJointName( XE::uint64 val ) const;

	XE::uint64 GetBoneJointParent( XE::uint64 val ) const;

	const XE::Mat4 & GetBoneJointTransform( XE::uint64 val ) const;

	const XE::Array<XE::uint64> & GetBoneJointChildren( XE::uint64 val ) const;

public:
	const XE::Array<XE::BoneJoint> & GetBoneJoints() const;

public:
	void SetBoneJointTransform( XE::uint64 val, const XE::Mat4 & mat );

private:
	XE::Array<XE::BoneJoint> _BoneJoints;
};

END_XE_NAMESPACE

#endif // SKELETON_H__035FBC00_8817_4635_8785_EF71ED728BE3
