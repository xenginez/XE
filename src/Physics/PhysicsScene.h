/*!
 * \file	PhysicsScene.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/11
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef PHYSICSSCENE_H__FB446DFF_5426_40D5_B375_25BB7F184281
#define PHYSICSSCENE_H__FB446DFF_5426_40D5_B375_25BB7F184281

#include "Math/Math.h"
#include "Utils/Layer.h"
#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API PhysicsScene : public XE::Object
{
	OBJECT( PhysicsScene, Object )

public:
	PhysicsScene();

	~PhysicsScene();

public:
	bool Startup();

	void Clearup();

	XE::PhysicsSceneHandle GetHandle() const;

public:
	XE::Vec3 GetGravity() const;

	void SetGravity( const XE::Vec3 & val );

	XE::uint32 GetCCDMaxPasses() const;

	void SetCCDMaxPasses( XE::uint32 val );

	XE::PhysicsSceneFlags GetFlag() const;

	void SetFlag( XE::PhysicsSceneFlags flags );

	XE::FrictionType GetFrictionType() const;

	void SetFrictionType( XE::FrictionType val );

	XE::float32 GetBounceThresholdVelocity() const;

	void SetBounceThresholdVelocity( XE::float32 val );

public:
	bool Raycast( const XE::Ray & ray, XE::float32 distance, bool multi = false, XE::PhysicsQueryFlags query = XE::PhysicsQueryFlag::DYNAMIC, const XE::Layer & layer = {} );

	bool Sweep( const XE::AABB & box, const XE::Vec3 & dir, XE::float32 distance, bool multi = false, XE::PhysicsQueryFlags query = XE::PhysicsQueryFlag::DYNAMIC, const XE::Layer & layer = {} );

	bool Sweep( const XE::Sphere & sphere, const XE::Vec3 & dir, XE::float32 distance, bool multi = false, XE::PhysicsQueryFlags query = XE::PhysicsQueryFlag::DYNAMIC, const XE::Layer & layer = {} );

	bool Sweep( const XE::Capsule & capsule, const XE::Vec3 & dir, XE::float32 distance, bool multi = false, XE::PhysicsQueryFlags query = XE::PhysicsQueryFlag::DYNAMIC, const XE::Layer & layer = {} );

	bool Overlap( const XE::AABB & box, XE::PhysicsQueryFlags query = XE::PhysicsQueryFlag::DYNAMIC, const XE::Layer & layer = {} );

	bool Overlap( const XE::Sphere & sphere, XE::PhysicsQueryFlags query = XE::PhysicsQueryFlag::DYNAMIC, const XE::Layer & layer = {} );

	bool Overlap( const XE::Capsule & capsule, XE::PhysicsQueryFlags query = XE::PhysicsQueryFlag::DYNAMIC, const XE::Layer & layer = {} );

private:
	XE::PhysicsSceneHandle _Handle;
};

END_XE_NAMESPACE

#endif // PHYSICSSCENE_H__FB446DFF_5426_40D5_B375_25BB7F184281
