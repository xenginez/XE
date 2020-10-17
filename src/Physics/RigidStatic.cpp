#include "RigidStatic.h"

#include <PhysX/PxPhysicsAPI.h>

#define _p reinterpret_cast< physx::PxRigidStatic * >( GetHandle().GetValue() )

BEG_META( XE::RigidStatic )
END_META()

XE::RigidStatic::RigidStatic()
{

}

XE::RigidStatic::~RigidStatic()
{

}
