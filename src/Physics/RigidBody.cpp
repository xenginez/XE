#include "RigidBody.h"

#include <PhysX/PxPhysicsAPI.h>

#define CAST() reinterpret_cast< physx::PxRigidActor * >( GetHandle().GetValue() )

BEG_META( XE::RigidBody )
END_META()

XE::RigidBody::RigidBody()
{
}

XE::RigidBody::~RigidBody()
{

}
