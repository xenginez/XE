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

#include "Math/Mathf.h"
#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API SkeletonAnimationKey
{
public:
	friend class SkeletonAnimation;

public:
	SkeletonAnimationKey();

	~SkeletonAnimationKey();

public:
	XE::float32 GetTime() const;

	void SetTime( XE::float32 val );

	const XE::Vec3 & GetPosition() const;

	void SetPosition( const XE::Vec3 & val );

	const XE::Quat & GetRotation() const;

	void SetRotation( const XE::Quat & val );

	const XE::Vec3 & GetScale() const;

	void SetScale( const XE::Vec3 & val );

private:
	XE::float32 _Time;
	XE::Vec3 _Position;
	XE::Quat _Rotation;
	XE::Vec3 _Scale;
};
DECL_META_CLASS( XE_API, SkeletonAnimationKey );

class XE_API SkeletonAnimationTrack
{
public:
	friend class SkeletonAnimation;

public:
	SkeletonAnimationTrack();

	~SkeletonAnimationTrack();

public:
	XE::float32 GetMaxTime() const;

	void SetMaxTime( XE::float32 val );

	const Array< SkeletonAnimationKey > & GetSkeletonAnimationKeys() const;

	void SetSkeletonAnimationKeys( const Array< SkeletonAnimationKey > & val );

public:
	XE::float32 _MaxTime;
	Array< SkeletonAnimationKey > _Keys;
};
DECL_META_CLASS( XE_API, SkeletonAnimationTrack );

class XE_API SkeletonAnimation : public XE::Object
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

	const Array< SkeletonAnimationTrack > & GetSkeletonAnimationTracks() const;

	void SetSkeletonAnimationTracks( const Array< SkeletonAnimationTrack > & val );

public:
	bool Sample( XE::uint32 bone, XE::float32 time, XE::Vec3 & position, XE::Quat & rotation, XE::Vec3 & scale ) const;

private:
	String _Name;
	String _Skeleton;
	XE::float32 _MaxTime;
	Array< SkeletonAnimationTrack > _Tracks;
};

END_XE_NAMESPACE

#endif // SKELETONANIMATION_H__6E601FF8_DDB5_470B_9FDE_EA161BD40C6B
