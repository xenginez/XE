#include "PhysicsService.h"

#include <physx/PxPhysicsAPI.h>

USING_XE

BEG_META( PhysicsService )
END_META()

struct XE::PhysicsService::Private
{
	physx::PxScene * _Scene = nullptr;
	physx::PxPhysics * _Physicis = nullptr;
	physx::PxFoundation * _Foundation = nullptr;
};

XE::PhysicsService::PhysicsService()
{

}

XE::PhysicsService::~PhysicsService()
{

}

void XE::PhysicsService::Prepare()
{

}

bool XE::PhysicsService::Startup()
{
// 	physx::PxDefaultErrorCallback gDefaultErrorCallback;
// 	physx::PxDefaultAllocator gDefaultAllocatorCallback;
// 
// 	_p->_Foundation = PxCreateFoundation( PX_PHYSICS_VERSION, gDefaultAllocatorCallback,
// 									  gDefaultErrorCallback );
// 	if( !_p->_Foundation )
// 		XE_LOG( LoggerLevel::Error, "PxCreateFoundation failed!" );
// 
// 	physx::PxTolerancesScale scale;
// 
// 	scale.length = 100;
// 	scale.speed = GetFramework()->GetConfigService()->GetInt32( "Physicis.Gravity", 981 );
// 
// 	_p->_Physicis = PxCreatePhysics( PX_PHYSICS_VERSION, *_p->_Foundation, scale, true, nullptr );
// 	if( !_p->_Physicis )
// 	{
// 		XE_LOG( LoggerLevel::Error, "PxCreatePhysics failed!" );
// 	}
// 
// 	if( !PxInitExtensions( *_p->_Physicis, nullptr ) )
// 	{
// 		XE_LOG( LoggerLevel::Error, "PxInitExtensions failed!" );
// 	}
// 
// 	physx::PxSceneDesc desc( scale );
// 	physx::PxDefaultCpuDispatcher * CpuDispatcher = physx::PxDefaultCpuDispatcherCreate( 0 );
// 	if( !CpuDispatcher )
// 	{
// 		XE_LOG( LoggerLevel::Error, "PxDefaultCpuDispatcherCreate failed!" );
// 	}
// 
// 	desc.cpuDispatcher = CpuDispatcher;
// 
// 	_p->_Scene = _p->_Physicis->createScene( desc );
// 	if( !_p->_Scene )
// 	{
// 		XE_LOG( LoggerLevel::Error, "PxPhysics::createScene failed!" );
// 	}

	return false;
}

void XE::PhysicsService::Update()
{
// 	_p->_Scene->fetchResults( true );
// 	_p->_Scene->simulate( GetFramework()->GetTimerService()->GetFixedDeltaTime() );
}

void XE::PhysicsService::Clearup()
{
// 	if( _p->_Scene )
// 	{
// 		_p->_Scene->release();
// 	}
// 	if( _p->_Physicis )
// 	{
// 		_p->_Physicis->release();
// 	}
// 	if( _p->_Foundation )
// 	{
// 		_p->_Foundation->release();
// 	}
}
