#include "RigidActor.h"

#include <PhysX/PxPhysicsAPI.h>

#include "RigidBody.h"
#include "RigidStatic.h"
#include "RigidDynamic.h"

#define _p reinterpret_cast< physx::PxRigidActor * >( GetHandle().GetValue() )

BEG_META( XE::RigidActor )
END_META()

XE::RigidActor::RigidActor()
{

}

XE::RigidActor::~RigidActor()
{

}

XE::RigidActorPtr XE::RigidActor::CreateRigidActor( XE::RigidActorHandle val )
{
	XE::RigidActorPtr res = nullptr;

	switch( reinterpret_cast< physx::PxRigidActor * >( val.GetValue() )->getType() )
	{
	case physx::PxActorType::eRIGID_STATIC:
		res = XE::MakeShared<XE::RigidStatic>();
		break;
	case physx::PxActorType::eRIGID_DYNAMIC:
		res = XE::MakeShared<XE::RigidDynamic>();
		break;
	case physx::PxActorType::eARTICULATION_LINK:
	case physx::PxActorType::eACTOR_COUNT:
	case physx::PxActorType::eACTOR_FORCE_DWORD:
	default:
		break;
	}

	if( res )
	{
		res->SetHandle( val );
	}

	return res;
}

XE::RigidActorHandle XE::RigidActor::GetHandle() const
{
	return _Handle;
}

void XE::RigidActor::SetHandle( XE::RigidActorHandle val )
{
	_Handle = val;
}

XE::PhysicsSceneHandle XE::RigidActor::GetSceneHandle() const
{
	return reinterpret_cast< XE::uint64 >( _p->getScene() );
}

XE::String XE::RigidActor::GetName() const
{
	return _p->getName();
}

void XE::RigidActor::SetName( const XE::String & val )
{
	_p->setName( val.ToCString() );
}

XE::Mat4 XE::RigidActor::GetWorldPose() const
{
	auto trans = _p->getGlobalPose();

	return XE::Mathf::TRS( { trans.p.x,trans.p.y,trans.p.z }, { trans.q.x, trans.q.y, trans.q.z, trans.q.w }, XE::Vec3::One );
}

void XE::RigidActor::SetWorldPose( const XE::Mat4 & val )
{
	XE::Quat rot;
	XE::Vec3 pos, scale;

	XE::Mathf::TRS( val, pos, rot, scale );

	_p->setGlobalPose( physx::PxTransform( { pos.x, pos.y, pos.z }, { rot.x, rot.y, rot.z, rot.w } ) );
}

XE::RigidActorFlags XE::RigidActor::GetRigidActorFlags() const
{
	return XE::uint8( _p->getActorFlags() );
}

void XE::RigidActor::SetRigidActorFlags( XE::RigidActorFlags val )
{
	_p->setActorFlags( physx::PxActorFlags( val.GetValue() ) );
}

XE::uint64 XE::RigidActor::GetShapeCount() const
{
	return _p->getNbShapes();
}

XE::uint64 XE::RigidActor::GetConstraintCount() const
{
	return _p->getNbConstraints();
}

void XE::RigidActor::AttachShape( XE::ShapeHandle val )
{
	_p->attachShape( *reinterpret_cast< physx::PxShape * >( val.GetValue() ) );
}

void XE::RigidActor::DetachShape( XE::ShapeHandle val )
{
	_p->detachShape( *reinterpret_cast< physx::PxShape * >( val.GetValue() ) );
}

XE::Array<XE::ShapeHandle> XE::RigidActor::GetShapes() const
{
	XE::Array<XE::ShapeHandle> res;

	physx::PxShape * shapes[1024];

	auto size = _p->getShapes( shapes, 1024 );

	for( int i = 0; i < size; ++i )
	{
		res.push_back( reinterpret_cast< XE::uint64 >( shapes[i] ) );
	}

	return std::move( res );
}

XE::Array<XE::ConstraintHandle> XE::RigidActor::GetConstraints() const
{
	XE::Array<XE::ConstraintHandle> res;

	physx::PxConstraint * constraint[1024];

	auto size = _p->getConstraints( constraint, 1024 );

	for( int i = 0; i < size; ++i )
	{
		res.push_back( reinterpret_cast< XE::uint64 >( constraint[i] ) );
	}

	return std::move( res );
}
