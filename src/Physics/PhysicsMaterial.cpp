#include "PhysicsMaterial.h"

#include <PhysX/PxPhysicsAPI.h>

#define CAST() reinterpret_cast< physx::PxMaterial * >( GetHandle().GetValue() )

BEG_META( XE::PhysicsMaterial )
END_META()

XE::PhysicsMaterial::PhysicsMaterial()
{

}

XE::PhysicsMaterial::~PhysicsMaterial()
{

}
