#include "PhysicsMaterial.h"

USING_XE

BEG_META( PhysicsMaterial )
type->Property( "Flag", &PhysicsMaterial::_Flag );
type->Property( "Restitution", &PhysicsMaterial::_Restitution );
type->Property( "StaticFriction", &PhysicsMaterial::_StaticFriction );
type->Property( "DynamicFriction", &PhysicsMaterial::_DynamicFriction );
type->Property( "FrictionCombineMode", &PhysicsMaterial::_FrictionCombineMode );
type->Property( "RestitutionCombineMode", &PhysicsMaterial::_RestitutionCombineMode );
END_META()

XE::PhysicsMaterial::PhysicsMaterial()
	:_Restitution( 0.0f ), _StaticFriction( 0.0f ), _DynamicFriction( 0.0f )
{

}

XE::PhysicsMaterial::~PhysicsMaterial()
{

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

XE::PhysicsMaterialFlag XE::PhysicsMaterial::GetFlag() const
{
	return _Flag;
}

void XE::PhysicsMaterial::SetFlag( PhysicsMaterialFlag val )
{
	_Flag = val;
}

XE::CombineMode XE::PhysicsMaterial::GetFrictionCombineMode() const
{
	return _FrictionCombineMode;
}

void XE::PhysicsMaterial::SetFrictionCombineMode( CombineMode val )
{
	_FrictionCombineMode = val;
}

XE::CombineMode XE::PhysicsMaterial::GetRestitutionCombineMode() const
{
	return _RestitutionCombineMode;
}

void XE::PhysicsMaterial::SetRestitutionCombineMode( CombineMode val )
{
	_RestitutionCombineMode = val;
}
