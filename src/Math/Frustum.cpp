#include "Frustum.h"

USING_XE

BEG_META( Frustum )
type->Property( "top", &Frustum::top );
type->Property( "bottom", &Frustum::bottom );
type->Property( "left", &Frustum::left );
type->Property( "right", &Frustum::right );
type->Property( "near", &Frustum::near );
type->Property( "far", &Frustum::far );
END_META()

XE::Frustum::Frustum()
{

}

XE::Frustum::Frustum( const Frustum & val )
	:top( val.top ), bottom( val.bottom ), left( val.left ), right( val.right ), far( val.far ), near( val.near )
{

}

XE::Frustum::~Frustum()
{

}

XE::Frustum & XE::Frustum::operator=( const Frustum & val )
{
	top = val.top;
	bottom = val.bottom;
	left = val.left;
	right = val.right;
	far = val.far;
	near = val.near;

	return *this;
}

bool XE::Frustum::Intersect( const OBB & val ) const
{
	return false;
}

bool XE::Frustum::Intersect( const AABB & val ) const
{
	return false;
}

bool XE::Frustum::Intersect( const Line & val ) const
{
	return false;
}

bool XE::Frustum::Intersect( const Plane & val ) const
{
	return false;
}

bool XE::Frustum::Intersect( const Sphere & val ) const
{
	return false;
}

bool XE::Frustum::Intersect( const Frustum & val ) const
{
	return false;
}

std::pair<bool, XE::real> XE::Frustum::Intersect( const Ray & ray, bool discardInside /*= true */ ) const
{
	return { false, 0.0f };
}
