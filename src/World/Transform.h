/*!
 * \file   Transform.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TRANSFORM_H__DFB3978B_761A_420E_BAF2_744EFD19CCA3
#define __TRANSFORM_H__DFB3978B_761A_420E_BAF2_744EFD19CCA3

#include "Type.h"

BEG_XE_NAMESPACE

class WORLD_API Transform
{
	OBJECT( Transform )

public:
	Transform();

public:
	Transform * GetParent() const;

	void SetParent( Transform * val );

public:
	Vec3 GetWorldUp();

	Vec3 GetWorldRight();

	Vec3 GetWorldForward();

	Vec3 GetRelativeUp() const;

	Vec3 GetRelativeRight() const;

	Vec3 GetRelativeForward() const;

public:
	const Vec3& GetWorldScale();

	void SetWorldScale( const Vec3& val );

	const Vec3& GetWorldPosition();

	void SetWorldPosition( const Vec3& val );

	const Quat& GetWorldRotation();

	void SetWorldRotation( const Quat& val );

public:
	const Vec3& GetRelativeScale() const;

	void SetRelativeScale( const Vec3& val );

	const Vec3& GetRelativePosition() const;

	void SetRelativePosition( const Vec3& val );

	const Quat& GetRelativeRotation() const;

	void SetRelativeRotation( const Quat& val );

public:
	const Mat4& GetWorldTransform() const;

	void SetWorldTransform( const Mat4& val );

	const Mat4& GetRelativeTransform() const;

	void SetRelativeTransform( const Mat4& val );

private:
	void UpdateTransform();

private:
	bool _Dirty;

	Vec3 _WorldScale;
	Vec3 _WorldPosition;
	Quat _WorldRotation;
	Vec3 _RelativeScale;
	Vec3 _RelativePosition;
	Quat _RelativeRotation;

	Mat4 _WorldTransform;
	Mat4 _RelativeTransform;

	Transform * _Parent;
};

END_XE_NAMESPACE

#endif // __TRANSFORM_H__DFB3978B_761A_420E_BAF2_744EFD19CCA3
