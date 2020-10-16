#include "Collection.h"

#include <PhysX/PxPhysicsAPI.h>

#define CAST() reinterpret_cast< physx::PxCollection * >( GetHandle().GetValue() )

BEG_META( XE::Collection )
END_META()

Collection::Collection()
{
	
}

Collection::~Collection()
{

}
