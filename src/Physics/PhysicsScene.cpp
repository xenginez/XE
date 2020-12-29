#include "PhysicsScene.h"


#define CAST() reinterpret_cast< physx::PxScene * >( GetHandle().GetValue() )

BEG_META( PhysicsScene )
END_META()

XE::PhysicsScene::PhysicsScene()
{

}

XE::PhysicsScene::~PhysicsScene()
{

}

XE::uint32 XE::PhysicsScene::GetCCDMaxPasses() const
{
	return _CCDMaxPasses;
}

void XE::PhysicsScene::SetCCDMaxPasses( XE::uint32 val )
{
	_CCDMaxPasses = val;
}

const XE::Vec3f & XE::PhysicsScene::GetGravity() const
{
	return _Gravity;
}

void XE::PhysicsScene::SetGravity( const XE::Vec3f & val )
{
	_Gravity = val;
}

XE::FrictionType XE::PhysicsScene::GetFrictionType() const
{
	return _FrictionType;
}

void XE::PhysicsScene::SetFrictionType( XE::FrictionType val )
{
	_FrictionType = val;
}

XE::PhysicsSceneHandle XE::PhysicsScene::GetHandle() const
{
	return _Handle;
}

void XE::PhysicsScene::SetHandle( XE::PhysicsSceneHandle val )
{
	_Handle = val;
}

XE::float32 XE::PhysicsScene::GetBounceThresholdVelocity() const
{
	return _BounceThresholdVelocity;
}

void XE::PhysicsScene::SetBounceThresholdVelocity( XE::float32 val )
{
	_BounceThresholdVelocity = val;
}

XE::PhysicsSceneFlags XE::PhysicsScene::GetPhysicsSceneFlags() const
{
	return _PhysicsSceneFlags;
}

void XE::PhysicsScene::SetPhysicsSceneFlags( XE::PhysicsSceneFlags val )
{
	_PhysicsSceneFlags = val;
}
