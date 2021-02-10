/*!
 * \file   Transform.h
 *
 * \author ZhengYuanQing
 * \date   2021/02/09
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef TRANSFORM_H__595570D6_1829_4393_B7E9_1D7CC38EAB1B
#define TRANSFORM_H__595570D6_1829_4393_B7E9_1D7CC38EAB1B

#include "Type.h"

#include "Math/Mat.h"
#include "Math/Vec3.h"
#include "Math/Quat.h"

BEG_XE_NAMESPACE

class XE_API Transform
{
public:
    static const Transform Identity;

public:
    Transform( Transform * parent = nullptr );

    Transform( const XE::Mat4x4f & val, Transform * parent = nullptr );

    Transform( const XE::Vec3f & position, const XE::Quat & rotation, const XE::Vec3f & scale, Transform * parent = nullptr );

    Transform( const Transform & val, Transform * parent = nullptr );

    ~Transform();

public:
    XE::Transform * GetParent() const;

    void SetParent( XE::Transform * parent );

public:
	XE::Vec3f GetUp() const;

	XE::Vec3f GetDown() const;

	XE::Vec3f GetLeft() const;

	XE::Vec3f GetRight() const;

	XE::Vec3f GetForward() const;

	XE::Vec3f GetBackward() const;

public:
    void Translate( const XE::Vec3f & val );

    void Rotate( const XE::Quat & val );

    void Scale( const XE::Vec3f & val );

public:
	XE::Vec3d GetWorldPosition() const;

	void SetWorldPosition( const XE::Vec3d & val );

	XE::Quat GetWorldRotation() const;

	void SetWorldRotation( const XE::Quat & val );

	XE::Vec3d GetWorldScale() const;

	void SetWorldScale( const XE::Vec3d & val );

	XE::Mat4x4d GetWorldTransform() const;

	void SetWorldTransform( const XE::Mat4x4d & val );

public:
    const XE::Vec3f & GetRelativePosition() const;

    void SetRelativePosition( const XE::Vec3f & val );

    const XE::Quat & GetRelativeRotation() const;

    void SetRelativeRotation( const XE::Quat & val );

    const XE::Vec3f & GetRelativeScale() const;

    void SetRelativeScale( const XE::Vec3f & val );

    const XE::Mat4x4f & GetRelativeTransform() const;

    void SetRelativeTransform( const XE::Mat4x4f & val );

private:
    XE::Transform * _Parent = nullptr;

    XE::Vec3f _Position;
    XE::Quat _Rotation;
    XE::Vec3f _Scale;
    XE::Mat4x4f _Transform;
};
DECL_META_CLASS( XE_API, Transform );

XE::Transform operator *( const XE::Transform & left, const XE::Transform & right );

END_XE_NAMESPACE

#endif // TRANSFORM_H__595570D6_1829_4393_B7E9_1D7CC38EAB1B
