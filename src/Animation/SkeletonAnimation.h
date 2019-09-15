/*!
 * \file	SkeletonAnimation.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/15
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef SKELETONANIMATION_H__6E601FF8_DDB5_470B_9FDE_EA161BD40C6B
#define SKELETONANIMATION_H__6E601FF8_DDB5_470B_9FDE_EA161BD40C6B

#include "Type.h"

BEG_XE_NAMESPACE

class ANIMATION_API SkeletonAnimationItem
{
public:
	SkeletonAnimationItem();

	~SkeletonAnimationItem();

public:
	const XE::Vec3 & GetPosition() const;

	void SetPosition( const XE::Vec3 & val );

	const XE::Quat & GetRotation() const;

	void SetRotation( const XE::Quat & val );

	const XE::Vec3 & GetScale() const;

	void SetScale( const XE::Vec3 & val );

private:
	XE::Vec3 _Position;
	XE::Quat _Rotation;
	XE::Vec3 _Scale;
};
DECL_META_CLASS( ANIMATION_API, SkeletonAnimationItem );

class ANIMATION_API SkeletonAnimationKey
{
public:
	SkeletonAnimationKey();

	~SkeletonAnimationKey();

public:
	XE::float32 GetTime() const;

	void SetTime( XE::float32 val );

	const Map< XE::uint32, SkeletonAnimationItem > & GetSkeletonItems() const;

	void SetSkeletonItems( const Map< XE::uint32, SkeletonAnimationItem > & val );

public:
	XE::float32 _Time;
	Map< XE::uint32, SkeletonAnimationItem > _Items;
};
DECL_META_CLASS( ANIMATION_API, SkeletonAnimationKey );

class ANIMATION_API SkeletonAnimation : public XE::Object
{
	OBJECT( SkeletonAnimation, Object )

public:
	SkeletonAnimation();

	~SkeletonAnimation() override;

public:
	XE::float32 GetMaxTime() const;

	void SetMaxTime( XE::float32 val );

	const XE::String & GetName() const;

	void SetName( const XE::String & val );

	const XE::String & GetSkeleton() const;

	void SetSkeleton( const XE::String & val );

	const Array< SkeletonAnimationKey > & GetSkeletonKeys() const;

	void SetSkeletonKeys( const Array< SkeletonAnimationKey > & val );

public:
	bool CalcBoneJointPosition( XE::uint32 bone, XE::float32 time, XE::Vec3 & pos ) const;

	bool CalcBoneJointRotation( XE::uint32 bone, XE::float32 time, XE::Quat & rot ) const;

	bool CalcBoneJointScale( XE::uint32 bone, XE::float32 time, XE::Vec3 & scale ) const;

	bool CalcBoneJointTransform( XE::uint32 bone, XE::float32 time, XE::Vec3 & pos, XE::Quat & rot, XE::Vec3 & scale ) const;

private:
	String _Name;
	String _Skeleton;
	XE::float32 _MaxTime;
	Array< SkeletonAnimationKey > _Keys;
};

END_XE_NAMESPACE

#endif // SKELETONANIMATION_H__6E601FF8_DDB5_470B_9FDE_EA161BD40C6B
