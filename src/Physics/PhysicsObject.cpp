#include "PhysicsObject.h"

USING_XE

BEG_META( PhysicsObject )
END_META()

XE::PhysicsObject::PhysicsObject()
	:_Context( nullptr )
{

}

XE::PhysicsObject::~PhysicsObject()
{

}

XE::IPhysicsContextRPtr XE::PhysicsObject::GetPhysicsContext() const
{
	return _Context;
}

void XE::PhysicsObject::SetPhysicsContext( IPhysicsContextRPtr val )
{
	_Context = val;
}
