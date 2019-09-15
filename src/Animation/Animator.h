/*!
 * \file	Animator.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/15
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATOR_H__CEBD2CEF_0221_4DB7_816B_3207E8475E73
#define ANIMATOR_H__CEBD2CEF_0221_4DB7_816B_3207E8475E73

#include "Type.h"

BEG_XE_NAMESPACE

class ANIMATION_API AnimatorItem
{
public:
	AnimatorItem();

	~AnimatorItem();

public:
	const XE::Vec3 & GetPosition() const;

	void SetPosition( const XE::Vec3 & val );

	const XE::Quat & GetRotation() const;

	void SetRotation( const XE::Quat & val );

private:
	XE::Vec3 _Position;
	XE::Quat _Rotation;
};
DECL_META_CLASS( ANIMATION_API, AnimatorItem );

class ANIMATION_API AnimatorKey
{
public:
	AnimatorKey();

	~AnimatorKey();

public:
	XE::float32 GetTime() const;

	void SetTime( XE::float32 val );

	const Array< AnimatorItem > & GetSkeletonItems() const;

	void SetSkeletonItems( const Array< AnimatorItem > & val );

public:
	XE::float32 _Time;
	Array< AnimatorItem > _Items;
};
DECL_META_CLASS( ANIMATION_API, AnimatorKey );

class ANIMATION_API Animator : public XE::Object
{
	OBJECT( Animator, Object )

public:
	Animator();

	~Animator() override;

public:
	XE::float32 GetMaxTime() const;

	void SetMaxTime( XE::float32 val );

	const XE::String & GetName() const;

	void SetName( const XE::String & val );

	const XE::String & GetSkeleton() const;

	void SetSkeleton( const XE::String & val );

	const Array< AnimatorKey > & GetSkeletonKeys() const;

	void SetSkeletonKeys( const Array< AnimatorKey > & val );

public:
	XE::Vec3 CalcBoneJointPosition( XE::uint32 bone, XE::float32 time ) const;

	XE::Quat CalcBoneJointRotation( XE::uint32 bone, XE::float32 time ) const;

	XE::Mat4 CalcBoneJointTransform( XE::uint32 bone, XE::float32 time ) const;

private:
	String _Name;
	String _Skeleton;
	XE::float32 _MaxTime;
	Array< AnimatorKey > _Keys;
};

END_XE_NAMESPACE

#endif // ANIMATOR_H__CEBD2CEF_0221_4DB7_816B_3207E8475E73
