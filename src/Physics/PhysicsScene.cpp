#include "PhysicsScene.h"

#include <PhysX/PxPhysicsAPI.h>

#include "Utils/Logger.h"
#include "Interface/IFramework.h"
#include "Interface/IPhysicsService.h"

#define CAST() reinterpret_cast< physx::PxScene * >( GetHandle().GetValue() )

BEG_META( PhysicsScene )
END_META()

XE::PhysicsScene::PhysicsScene()
{

}

XE::PhysicsScene::~PhysicsScene()
{

}

bool XE::PhysicsScene::Startup()
{
	_Handle = XE::IFramework::GetCurrentFramework()->GetPhysicsService()->CreateScene();

	return true;
}

void XE::PhysicsScene::Clearup()
{
	if( _Handle )
	{
		XE::IFramework::GetCurrentFramework()->GetPhysicsService()->ReleaseScene( _Handle );
	}
}

XE::PhysicsSceneHandle XE::PhysicsScene::GetHandle() const
{
	return _Handle;
}
