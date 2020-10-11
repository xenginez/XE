#include "PhysicsService.h"

#include <PhysX/PxPhysicsAPI.h>
#include <tbb/concurrent_vector.h>
#include <tbb/scalable_allocator.h>
#include <tbb/concurrent_hash_map.h>

#include "Utils/Logger.h"
#include "Interface/IThreadService.h"

using namespace physx;

class XEPPhysXCpuDispatcher : public PxCpuDispatcher
{
public:
	void submitTask( PxBaseTask & task ) override
	{
		XE::IFramework::GetCurrentFramework()->GetThreadService()->PostTask( XE::ThreadType::PHYSICS, [&]()
																			 {
																				 task.run();
																				 task.release();
																			 } );
	}

	uint32_t getWorkerCount() const override
	{
		return 1;
	}
};

class XEPPhysXErrorCallback : public physx::PxErrorCallback
{
public:
	void reportError( physx::PxErrorCode::Enum code, const char * message, const char * file, int line ) override
	{
		switch( code )
		{
		case physx::PxErrorCode::Enum::eDEBUG_INFO:
			XE_LOG( XE::LoggerLevel::Message, "PhysX  %1-%2 %3", message, file, line );
			break;
		case physx::PxErrorCode::Enum::eDEBUG_WARNING:
			XE_LOG( XE::LoggerLevel::Warning, "PhysX  %1-%2 %3", message, file, line );
			break;
		case physx::PxErrorCode::Enum::eINVALID_PARAMETER:
			XE_LOG( XE::LoggerLevel::Error, "PhysX invalid parameter %1-%2 %3", message, file, line );
			break;
		case physx::PxErrorCode::Enum::eINVALID_OPERATION:
			XE_LOG( XE::LoggerLevel::Error, "PhysX invalid operation %1-%2 %3", message, file, line );
			break;
		case physx::PxErrorCode::Enum::eOUT_OF_MEMORY:
			XE_LOG( XE::LoggerLevel::Error, "PhysX out of memory %1-%2 %3", message, file, line );
			break;
		case physx::PxErrorCode::Enum::eINTERNAL_ERROR:
			XE_LOG( XE::LoggerLevel::Error, "PhysX internal error %1-%2 %3", message, file, line );
			break;
		case physx::PxErrorCode::Enum::eABORT:
			XE_LOG( XE::LoggerLevel::Error, "PhysX abort %1-%2 %3", message, file, line );
			break;
		case physx::PxErrorCode::Enum::ePERF_WARNING:
			XE_LOG( XE::LoggerLevel::Error, "PhysX perf warning %1-%2 %3", message, file, line );
			break;
		case physx::PxErrorCode::Enum::eMASK_ALL:
			XE_LOG( XE::LoggerLevel::Error, "PhysX mask all %1-%2 %3", message, file, line );
			break;
		default:
			break;
		}
	}
};

class XEPPhysXAllocator : public physx::PxAllocatorCallback
{
public:
	void * allocate( size_t size, const char *, const char *, int )
	{
		return scalable_malloc( size );
	}

	void deallocate( void * ptr )
	{
		scalable_free( ptr );
	}
};

BEG_META( XE::PhysicsService )
END_META()

struct XE::PhysicsService::Private
{
	XE::float32 _CurTime = 0;
	physx::PxPhysics * _Physicis = nullptr;
	physx::PxFoundation * _Foundation = nullptr;
	XEPPhysXErrorCallback _ErrorCallback;
	XEPPhysXAllocator _AllocatorCallback;
	XE::HandleAllocator<XE::PhysicsSceneHandle> _SceneHandleAlloc;
	tbb::concurrent_hash_map<XE::PhysicsSceneHandle, physx::PxScene *> _Scenes;
};

XE::PhysicsService::PhysicsService()
	:_p( new Private )
{

}

XE::PhysicsService::~PhysicsService()
{
	delete _p;
}

void XE::PhysicsService::Prepare()
{

}

bool XE::PhysicsService::Startup()
{
	physx::PxTolerancesScale scale;
	scale.length = 100;
	scale.speed = GetFramework()->GetInt32( "Physicis.Gravity", 981 );

	_p->_Foundation = PxCreateFoundation( PX_PHYSICS_VERSION, _p->_AllocatorCallback, _p->_ErrorCallback );
	if( !_p->_Foundation )
	{
		XE_LOG( LoggerLevel::Error, "PxCreateFoundation failed!" );
		return false;
	}

	_p->_Physicis = PxCreateBasePhysics( PX_PHYSICS_VERSION, *_p->_Foundation, scale, false, nullptr );
	if( !_p->_Physicis )
	{
		XE_LOG( LoggerLevel::Error, "PxCreatePhysics failed!" );
		return false;
	}
	PxRegisterHeightFields( *_p->_Physicis );

	return true;
}

void XE::PhysicsService::Update()
{
	_p->_CurTime += GetFramework()->GetTimerService()->GetDeltaTime();
	XE::float32 ftime = GetFramework()->GetTimerService()->GetFixedDeltaTime();

	if( _p->_CurTime >= ftime )
	{
		_p->_CurTime -= ftime;

		for( auto it : _p->_Scenes )
		{
			it.second->fetchResults( true );

			it.second->simulate( ftime );
		}
	}
}

void XE::PhysicsService::Clearup()
{
	_p->_CurTime = 0;

	for( auto it : _p->_Scenes )
	{
		it.second->release();
	}
	_p->_Scenes.clear();

	if( _p->_Physicis )
	{
		_p->_Physicis->release();
	}
	if( _p->_Foundation )
	{
		_p->_Foundation->release();
	}
}

XE::PhysicsSceneHandle XE::PhysicsService::CreateScene()
{
	physx::PxTolerancesScale scale;
	scale.length = 100;
	scale.speed = GetFramework()->GetInt32( "Physicis.Gravity", 981 );

	physx::PxSceneDesc desc( scale );

	desc.cpuDispatcher = new XEPPhysXCpuDispatcher;

	auto scene = _p->_Physicis->createScene( desc );
	if( !scene )
	{
		XE_LOG( LoggerLevel::Error, "PxPhysics::createScene failed!" );
		return XE::PhysicsSceneHandle::Invalid;
	}

	auto handle = _p->_SceneHandleAlloc.Alloc();

	_p->_Scenes.insert( { handle, scene } );

	return handle;
}

void XE::PhysicsService::ReleaseScene( XE::PhysicsSceneHandle handle )
{
	if( handle )
	{
		tbb::concurrent_hash_map<XE::PhysicsSceneHandle, physx::PxScene *>::accessor accessor;
		if( _p->_Scenes.find( accessor, handle ) )
		{
			_p->_Scenes.erase( accessor );
		}
	}
}

void * XE::PhysicsService::FindScene( XE::PhysicsSceneHandle handle )
{
	tbb::concurrent_hash_map<XE::PhysicsSceneHandle, physx::PxScene *>::accessor accessor;
	if( _p->_Scenes.find( accessor, handle ) )
	{
		return accessor->second;
	}

	return nullptr;
}
