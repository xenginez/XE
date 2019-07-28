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

class GRAPHICS_API Bone
{
public:
	String Name;
	Mat4 Transform;
	XE::uint64 Parent;
};
DECL_META_CLASS( GRAPHICS_API, Bone );

class GRAPHICS_API Skeleton : public XE::Object
{
	OBJECT( Skeleton, Object )

public:
	static constexpr XE::uint64 npos = std::numeric_limits<XE::uint64>::max();

public:
	Skeleton();

	~Skeleton() override;

public:
	XE::uint64 GetBoneCount() const;

	XE::uint64 FindBoneIndex( const String & val ) const;

	const String & GetBoneName( XE::uint64 val ) const;

	XE::uint64 GetBoneParent( XE::uint64 val ) const;

	const Array<Bone> & GetBones() const;

public:
	const Mat4 & GetBoneTransform( XE::uint64 val ) const;

	void SetBoneTransform( XE::uint64 val, const Mat4 & mat );

private:
	Array<Bone> _Bones;
};

END_XE_NAMESPACE

#endif // SKELETON_H__035FBC00_8817_4635_8785_EF71ED728BE3
