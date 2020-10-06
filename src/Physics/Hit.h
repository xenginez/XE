/*!
 * \file	Hit.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/26
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef HIT_H__C401DD79_F933_4621_AB28_9A13DF8483CF
#define HIT_H__C401DD79_F933_4621_AB28_9A13DF8483CF

#include "Math/Vec3.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API Hit
{
public:
	XE::Vec3 Normal;
	XE::Vec3 Position;
	XE::float32 Distance;
};
DECL_META_CLASS( XE_API, Hit );

class XE_API SweepHit : public Hit
{

};
DECL_META_CLASS( XE_API, SweepHit );

class XE_API OverlapHit : public Hit
{

};
DECL_META_CLASS( XE_API, OverlapHit );

class XE_API RaycastHit : public Hit
{
public:
	ShapePtr Shape;
	RigidBodyPtr RigidBody;
};
DECL_META_CLASS( XE_API, RaycastHit );

END_XE_NAMESPACE

#endif // HIT_H__C401DD79_F933_4621_AB28_9A13DF8483CF
