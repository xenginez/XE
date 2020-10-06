#include "Capsule.h"

BEG_META( XE::Capsule )
type->Property( "radius", &Capsule::radius );
type->Property( "height", &Capsule::height );
END_META()

XE::Capsule::Capsule()
	:radius( 0.0f ), height( 0.0f )
{

}

XE::Capsule::Capsule( const Capsule & val )
	: radius( val.radius ), height( val.height )
{

}

XE::Capsule::Capsule( XE::real radius, XE::real height )
	: radius( radius ), height( height )
{

}

XE::Capsule & XE::Capsule::operator=( const Capsule & val )
{
	radius = val.radius;
	height = val.height;

	return *this;
}

bool XE::Capsule::operator==( const Capsule & val ) const
{
	return radius == val.radius && height == val.height;
}

bool XE::Capsule::operator!=( const Capsule & val ) const
{
	return radius != val.radius || height != val.height;
}

bool XE::Capsule::Contains( const Vec3 & val ) const
{
	return false;
}

bool XE::Capsule::Intersect( const OBB & val ) const
{
	return false;
}

bool XE::Capsule::Intersect( const AABB & val ) const
{
	return false;
}

bool XE::Capsule::Intersect( const Line & val ) const
{
	return false;
}

bool XE::Capsule::Intersect( const Plane & val ) const
{
	return false;
}

bool XE::Capsule::Intersect( const Sphere & val ) const
{
	return false;
}

bool XE::Capsule::Intersect( const Frustum & val ) const
{
	return false;
}

std::pair<bool, XE::real> XE::Capsule::Intersect( const Ray & ray, bool discardInside /*= true */ ) const
{
	return { false, 0.0f };
}
