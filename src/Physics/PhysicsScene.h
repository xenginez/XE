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

#include "Utils/Object.h"
#include "Utils/Flags.hpp"

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
	XE::Flags<XE::PhysicsSceneFlag> GetFlag() const;

	void SetFlag( XE::Flags<XE::PhysicsSceneFlag> flags );

	XE::Vec3 GetGravity() const;

	void SetGravity( const XE::Vec3 & val );

	XE::float32 GetThresholdVelocity() const;

	void SetThresholdVelocity( XE::float32 val );

	XE::uint32 GetCCDMaxPasses() const;

	void SetCCDMaxPasses( XE::uint32 val );

	XE::FrictionType GetFrictionType() const;

	void SetFrictionType( XE::FrictionType val );

private:
	XE::PhysicsSceneHandle _Handle;
};

END_XE_NAMESPACE

#endif // PHYSICSSCENE_H__FB446DFF_5426_40D5_B375_25BB7F184281
