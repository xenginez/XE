#include "PhysicsMaterial.h"

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
	return _Restitution;
}

void XE::PhysicsMaterial::SetRestitution( XE::float32 val )
{
	_Restitution = val;
}

XE::float32 XE::PhysicsMaterial::GetStaticFriction() const
{
	return _StaticFriction;
}

void XE::PhysicsMaterial::SetStaticFriction( XE::float32 val )
{
	_StaticFriction = val;
}

XE::float32 XE::PhysicsMaterial::GetDynamicFriction() const
{
	return _DynamicFriction;
}

void XE::PhysicsMaterial::SetDynamicFriction( XE::float32 val )
{
	_DynamicFriction = val;
}

XE::CombineMode XE::PhysicsMaterial::GetFrictionCombineMode() const
{
	return _FrictionCombineMode;
}

void XE::PhysicsMaterial::SetFrictionCombineMode( XE::CombineMode val )
{
	_FrictionCombineMode = val;
}

XE::CombineMode XE::PhysicsMaterial::GetRestitutionCombineMode() const
{
	return _RestitutionCombineMode;
}

void XE::PhysicsMaterial::SetRestitutionCombineMode( XE::CombineMode val )
{
	_RestitutionCombineMode = val;
}

XE::PhysicsMaterialFlags XE::PhysicsMaterial::GetPhysicsMaterialFlags() const
{
	return _PhysicsMaterialFlags;
}

void XE::PhysicsMaterial::SetPhysicsMaterialFlags( XE::PhysicsMaterialFlags val )
{
	_PhysicsMaterialFlags = val;
}
