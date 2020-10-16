#include "Constraint.h"

#include <PhysX/PxPhysicsAPI.h>

#define CAST() reinterpret_cast< physx::PxConstraint * >( GetHandle().GetValue() )

BEG_META( XE::Constraint )
END_META()

XE::Constraint::Constraint()
{

}

XE::Constraint::~Constraint()
{

}
