#include "Constraint.h"

#include <PhysX/PxPhysicsAPI.h>

#define _p reinterpret_cast< physx::PxConstraint * >( GetHandle().GetValue() )

BEG_META( XE::Constraint )
END_META()

XE::Constraint::Constraint()
{

}

XE::Constraint::~Constraint()
{

}

XE::ConstraintHandle XE::Constraint::GetHandle() const
{
	return _Handle;
}

void XE::Constraint::SetHandle( XE::ConstraintHandle val )
{
	_Handle = val;
}

XE::PhysicsSceneHandle XE::Constraint::GetSceneHandle() const
{
	return _SceneHandle;
}

void XE::Constraint::GetSceneHandle( XE::PhysicsSceneHandle val )
{
	_SceneHandle = val;
}

XE::ConstraintFlags XE::Constraint::GetConstraintFlags() const
{
	return XE::ConstraintFlags( XE::uint16( _p->getFlags() ) );
}

void XE::Constraint::SetConstraintFlags( XE::ConstraintFlags val )
{
	_p->setFlags( physx::PxConstraintFlags( val.GetValue() ) );
}

XE::Pair<XE::RigidActorHandle, XE::RigidActorHandle> XE::Constraint::GetRigidActorHandle() const
{
	physx::PxRigidActor * actor0, * actor1;
	
	_p->getActors( actor0, actor1 );

	return { reinterpret_cast< XE::uint64 >( actor0 ), reinterpret_cast< XE::uint64 >( actor1 ) };
}

void XE::Constraint::SetRigidActorHandle( const XE::Pair<XE::RigidActorHandle, XE::RigidActorHandle> & val )
{
	_p->setActors( reinterpret_cast< physx::PxRigidActor * >( val.first.GetValue() ), reinterpret_cast< physx::PxRigidActor * >( val.second.GetValue() ) );
}

bool XE::Constraint::IsValid() const
{
	return _p->isValid();
}

XE::Vec3 XE::Constraint::GetForce() const
{
	physx::PxVec3 linear, angular;

	_p->getForce( linear, angular );

	return { linear.x, linear.y, linear.z };
}

XE::Vec3 XE::Constraint::GetTorque() const
{
	physx::PxVec3 linear, angular;

	_p->getForce( linear, angular );

	return { angular.x, angular.y, angular.z };
}

XE::float32 XE::Constraint::GetBreakForce() const
{
	XE::float32 linear, angular;
	
	_p->getBreakForce( linear, angular );

	return linear;
}

void XE::Constraint::SetBreakForce( XE::float32 val )
{
	_p->setBreakForce( val, GetBreakTorque() );
}

XE::float32 XE::Constraint::GetBreakTorque() const
{
	XE::float32 linear, angular;

	_p->getBreakForce( linear, angular );

	return angular;
}

void XE::Constraint::SetBreakTorque( XE::float32 val )
{
	_p->setBreakForce( GetBreakForce(), val );
}

XE::float32 XE::Constraint::GetMinResponseThreshold() const
{
	return _p->getMinResponseThreshold();
}

void XE::Constraint::SetMinResponseThreshold( XE::float32 val )
{
	_p->setMinResponseThreshold( val );
}
