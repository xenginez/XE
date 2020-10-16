#include "Joint.h"

#include <PhysX/PxPhysicsAPI.h>

#define CAST() reinterpret_cast< physx::PxJoint * >( GetHandle().GetValue() )

BEG_META( XE::Joint )
END_META()

XE::Joint::Joint()
{

}

XE::Joint::~Joint()
{

}
