#include "NavigationObstacle.h"

#include "Interface/IFramework.h"
#include "Interface/INavigationService.h"

BEG_META( XE::NavigationObstacle )
END_META()

XE::NavigationObstacle::NavigationObstacle()
{

}

XE::NavigationObstacle::~NavigationObstacle()
{

}

const XE::Vec3 & XE::NavigationObstacle::GetPosition() const
{
	return _Position;
}

void XE::NavigationObstacle::SetPosition( const XE::Vec3 & val )
{
	_Position = val;
}

XE::NavigationObstacleType XE::NavigationObstacle::GetType() const
{
	return _Type;
}

void XE::NavigationObstacle::SetType( XE::NavigationObstacleType val )
{
	_Type = val;
}

XE::NavigationObstacleHandle XE::NavigationObstacle::GetHandle() const
{
	return _Handle;
}

void XE::NavigationObstacle::SetHandle( XE::NavigationObstacleHandle val )
{
	_Handle = val;
}

void XE::NavigationObstacle::Startup()
{

}

void XE::NavigationObstacle::Update()
{
	XE::IFramework::GetCurrentFramework()->GetINavigationService()->UpdateObstacle( GetHandle(), GetPosition() );
}

void XE::NavigationObstacle::Clearup()
{
	XE::IFramework::GetCurrentFramework()->GetINavigationService()->RemoveObstacle( GetHandle() );
}

BEG_META( XE::NavigationOBBObstacle )
type->Property( "Geometry", &XE::NavigationOBBObstacle::_OBB );
END_META()

XE::NavigationOBBObstacle::NavigationOBBObstacle()
{
	SetType( NavigationObstacleType::OBB );
}

XE::NavigationOBBObstacle::~NavigationOBBObstacle()
{

}

const XE::OBB & XE::NavigationOBBObstacle::GetOBB() const
{
	return _OBB;
}

void XE::NavigationOBBObstacle::SetOBB( const XE::OBB & val )
{
	_OBB = val;
}

void XE::NavigationOBBObstacle::Startup()
{
	SetHandle( XE::IFramework::GetCurrentFramework()->GetINavigationService()->AddObstacle( _OBB, GetPosition() ) );
}

BEG_META( XE::NavigationAABBObstacle )
type->Property( "Geometry", &XE::NavigationAABBObstacle::_AABB );
END_META()

XE::NavigationAABBObstacle::NavigationAABBObstacle()
{
	SetType( NavigationObstacleType::AABB );
}

XE::NavigationAABBObstacle::~NavigationAABBObstacle()
{

}

const XE::AABB & XE::NavigationAABBObstacle::GetAABB() const
{
	return _AABB;
}

void XE::NavigationAABBObstacle::SetAABB( const XE::AABB & val )
{
	_AABB = val;
}

void XE::NavigationAABBObstacle::Startup()
{
	SetHandle( XE::IFramework::GetCurrentFramework()->GetINavigationService()->AddObstacle( _AABB, GetPosition() ) );
}

BEG_META( XE::NavigationCapsuleObstacle )
type->Property( "Geometry", &XE::NavigationCapsuleObstacle::_Capsule );
END_META()

XE::NavigationCapsuleObstacle::NavigationCapsuleObstacle()
{
	SetType( NavigationObstacleType::CAPSULE );
}

XE::NavigationCapsuleObstacle::~NavigationCapsuleObstacle()
{

}

const XE::Capsule & XE::NavigationCapsuleObstacle::GetCapsule() const
{
	return _Capsule;
}

void XE::NavigationCapsuleObstacle::SetCapsule( const XE::Capsule & val )
{
	_Capsule = val;
}

void XE::NavigationCapsuleObstacle::Startup()
{
	SetHandle( XE::IFramework::GetCurrentFramework()->GetINavigationService()->AddObstacle( _Capsule, GetPosition() ) );
}
