#include "IWorldService.h"



BEG_META( XE::IWorldService )
END_META()

XE::IWorldService::IWorldService()
{

}

XE::IWorldService::~IWorldService()
{

}

bool XE::IWorldService::AddGameObject( const XE::GameObjectPtr & val )
{
	return GetCurrentWorld()->AddGameObject( val );
}

bool XE::IWorldService::RemoveGameObject( const XE::GameObjectPtr & val )
{
	return GetCurrentWorld()->RemoveGameObject( val );
}

XE::GameObjectPtr XE::IWorldService::FindGameObject( const String & val ) const
{
	return GetCurrentWorld()->FindGameObject( val );
}

XE::GameObjectPtr XE::IWorldService::FindGameObject( GameObjectHandle val ) const
{
	return GetCurrentWorld()->FindGameObject( val );
}

const XE::Array< XE::GameObjectPtr > & XE::IWorldService::GetGameObjects() const
{
	return GetCurrentWorld()->GetGameObjects();
}

XE::GameObjectPtr XE::IWorldService::Intersect( const Array<XE::GameObjectPtr> exclude, const Ray & val ) const
{
	return GetCurrentWorld()->Intersect( exclude, val );
}

XE::GameObjectPtr XE::IWorldService::Intersect( const Array<XE::GameObjectPtr> exclude, const AABB & val ) const
{
	return GetCurrentWorld()->Intersect( exclude, val );
}

XE::GameObjectPtr XE::IWorldService::Intersect( const Array<XE::GameObjectPtr> exclude, const Line & val ) const
{
	return GetCurrentWorld()->Intersect( exclude, val );
}

XE::GameObjectPtr XE::IWorldService::Intersect( const Array<XE::GameObjectPtr> exclude, const Plane & val ) const
{
	return GetCurrentWorld()->Intersect( exclude, val );
}

XE::GameObjectPtr XE::IWorldService::Intersect( const Array<XE::GameObjectPtr> exclude, const Sphere & val ) const
{
	return GetCurrentWorld()->Intersect( exclude, val );
}

XE::GameObjectPtr XE::IWorldService::Intersect( const Array<XE::GameObjectPtr> exclude, const Frustum & val ) const
{
	return GetCurrentWorld()->Intersect( exclude, val );
}

XE::Array<XE::GameObjectPtr> XE::IWorldService::Intersects( const Ray & val ) const
{
	return GetCurrentWorld()->Intersects( val );
}

XE::Array<XE::GameObjectPtr> XE::IWorldService::Intersects( const AABB & val ) const
{
	return GetCurrentWorld()->Intersects( val );
}

XE::Array<XE::GameObjectPtr> XE::IWorldService::Intersects( const Line & val ) const
{
	return GetCurrentWorld()->Intersects( val );
}

XE::Array<XE::GameObjectPtr> XE::IWorldService::Intersects( const Plane & val ) const
{
	return GetCurrentWorld()->Intersects( val );
}

XE::Array<XE::GameObjectPtr> XE::IWorldService::Intersects( const Sphere & val ) const
{
	return GetCurrentWorld()->Intersects( val );
}

XE::Array<XE::GameObjectPtr> XE::IWorldService::Intersects( const Frustum & val ) const
{
	return GetCurrentWorld()->Intersects( val );
}
