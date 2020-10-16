#include "RigidDynamic.h"

#include <PhysX/PxPhysicsAPI.h>

#define CAST() reinterpret_cast< physx::PxRigidDynamic * >( GetHandle().GetValue() )

BEG_META( XE::RigidDynamic )
END_META()

XE::RigidDynamic::RigidDynamic()
{

}

XE::RigidDynamic::~RigidDynamic()
{

}
