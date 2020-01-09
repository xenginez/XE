#include "IWorldService.h"

USING_XE

BEG_META( IWorldService )
END_META()

XE::IWorldService::IWorldService()
{

}

XE::IWorldService::~IWorldService()
{

}

bool IWorldService::AddGameObject( const GameObjectPtr & val )
{
	return GetCurrentWorld()->AddGameObject( val );
}

GameObjectPtr IWorldService::FindGameObject( const String & val ) const
{
	return GetCurrentWorld()->FindGameObject( val );
}

GameObjectPtr IWorldService::FindGameObject( GameObjectHandle val ) const
{
	return GetCurrentWorld()->FindGameObject( val );
}

const Array< GameObjectPtr > & IWorldService::GetGameObjects() const
{
	return GetCurrentWorld()->GetGameObjects();
}

GameObjectPtr IWorldService::Intersect( const Array<GameObjectPtr> exclude, const Ray & val ) const
{
	return GetCurrentWorld()->Intersect( exclude, val );
}

GameObjectPtr IWorldService::Intersect( const Array<GameObjectPtr> exclude, const AABB & val ) const
{
	return GetCurrentWorld()->Intersect( exclude, val );
}

GameObjectPtr IWorldService::Intersect( const Array<GameObjectPtr> exclude, const Line & val ) const
{
	return GetCurrentWorld()->Intersect( exclude, val );
}

GameObjectPtr IWorldService::Intersect( const Array<GameObjectPtr> exclude, const Plane & val ) const
{
	return GetCurrentWorld()->Intersect( exclude, val );
}

GameObjectPtr IWorldService::Intersect( const Array<GameObjectPtr> exclude, const Sphere & val ) const
{
	return GetCurrentWorld()->Intersect( exclude, val );
}

GameObjectPtr IWorldService::Intersect( const Array<GameObjectPtr> exclude, const Frustum & val ) const
{
	return GetCurrentWorld()->Intersect( exclude, val );
}

Array<GameObjectPtr> IWorldService::Intersects( const Ray & val ) const
{
	return GetCurrentWorld()->Intersects( val );
}

Array<GameObjectPtr> IWorldService::Intersects( const AABB & val ) const
{
	return GetCurrentWorld()->Intersects( val );
}

Array<GameObjectPtr> IWorldService::Intersects( const Line & val ) const
{
	return GetCurrentWorld()->Intersects( val );
}

Array<GameObjectPtr> IWorldService::Intersects( const Plane & val ) const
{
	return GetCurrentWorld()->Intersects( val );
}

Array<GameObjectPtr> IWorldService::Intersects( const Sphere & val ) const
{
	return GetCurrentWorld()->Intersects( val );
}

Array<GameObjectPtr> IWorldService::Intersects( const Frustum & val ) const
{
	return GetCurrentWorld()->Intersects( val );
}
