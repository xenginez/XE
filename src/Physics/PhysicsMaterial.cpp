#include "PhysicsMaterial.h"

#include <PhysX/PxPhysicsAPI.h>

#define _p reinterpret_cast< physx::PxMaterial * >( GetHandle().GetValue() )

BEG_META( XE::PhysicsMaterial )
END_META()

XE::PhysicsMaterial::PhysicsMaterial()
{

}

XE::PhysicsMaterial::~PhysicsMaterial()
{

}

XE::PhysicsMaterialHandle XE::PhysicsMaterial::GetHandle() const
{
	return _Handle;
}

void XE::PhysicsMaterial::SetHandle( XE::PhysicsMaterialHandle val )
{
	_Handle = val;
}

XE::float32 XE::PhysicsMaterial::GetRestitution() const
{
	return _p->getRestitution();
}

void XE::PhysicsMaterial::SetRestitution( XE::float32 val )
{
	_p->setRestitution( val );
}

XE::float32 XE::PhysicsMaterial::GetStaticFriction() const
{
	return _p->getStaticFriction();
}

void XE::PhysicsMaterial::SetStaticFriction( XE::float32 val )
{
	_p->setStaticFriction( val );
}

XE::float32 XE::PhysicsMaterial::GetDynamicFriction() const
{
	return _p->getDynamicFriction();
}

void XE::PhysicsMaterial::SetDynamicFriction( XE::float32 val )
{
	_p->setDynamicFriction( val );
}

XE::CombineMode XE::PhysicsMaterial::GetFrictionCombineMode() const
{
	return static_cast< XE::CombineMode >( _p->getFrictionCombineMode() );
}

void XE::PhysicsMaterial::SetFrictionCombineMode( XE::CombineMode val )
{
	_p->setFrictionCombineMode( static_cast< physx::PxCombineMode::Enum >( val ) );
}

XE::CombineMode XE::PhysicsMaterial::GetRestitutionCombineMode() const
{
	return static_cast< XE::CombineMode >( _p->getRestitutionCombineMode() );
}

void XE::PhysicsMaterial::SetRestitutionCombineMode( XE::CombineMode val )
{
	_p->setRestitutionCombineMode( static_cast< physx::PxCombineMode::Enum >( val ) );
}

XE::PhysicsMaterialFlags XE::PhysicsMaterial::GetPhysicsMaterialFlags() const
{
	return XE::uint16( _p->getFlags() );
}

void XE::PhysicsMaterial::SetPhysicsMaterialFlags( XE::PhysicsMaterialFlags val )
{
	_p->setFlags( physx::PxMaterialFlags( val.GetValue() ) );
}
