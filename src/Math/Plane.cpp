#include "Plane.h"

#include "Mathf.h"
#include "Ray.h"
#include "AABB.h"
#include "Sphere.h"

USING_XE

BEG_META( Plane )
type->Property( "normal", &Plane::normal );
type->Property( "distance", &Plane::distance );
END_META()

XE::Plane::Plane()
	:distance( 0 )
{

}

XE::Plane::Plane( const Plane& val )
	: normal( val.normal ), distance( val.distance )
{

}

XE::Plane::Plane( const Vec3& normal, XE::real d )
	: normal( normal ), distance( d )
{

}

XE::Plane::Plane( XE::real a, XE::real b, XE::real c, XE::real d )
	: normal( a, b, c ), distance( d )
{

}

XE::Plane::Plane( const Vec3& normal, const Vec3& point )
	: normal( normal ), distance( Mathf::Dot(normal, point ) )
{

}

XE::Plane::Plane( const Vec3& point0, const Vec3& point1, const Vec3& point2 )
{
	Vec3 kEdge1 = point1 - point0;
	Vec3 kEdge2 = point2 - point0;
	normal = Mathf::Cross( kEdge1, kEdge2 );
	normal = Mathf::Normalize( normal );
	distance = Mathf::Dot( normal, point0 );
}

XE::Plane& XE::Plane::operator=( const Plane& val )
{
	if ( &val != this )
	{
		distance = val.distance;
		normal = val.normal;
	}
	return *this;
}

bool XE::Plane::operator==( const Plane& val ) const
{
	return ( Mathf::Abs( val.distance - distance ) <= Mathf::Epsilon ) && normal == val.normal;
}

bool XE::Plane::operator!=( const Plane& val ) const
{
	return ( Mathf::Abs( val.distance - distance ) > Mathf::Epsilon ) || normal != val.normal;
}

XE::SideType XE::Plane::GetSide( const Vec3& val ) const
{
	XE::real dist = GetDistance( val );

	if ( dist > Mathf::Epsilon )
		return SideType::POSITIVE;

	if ( dist < -Mathf::Epsilon )
		return SideType::NEGATIVE;

	return SideType::NOOP;
}

XE::SideType XE::Plane::GetSide( const AABB& val ) const
{
	XE::real dist = GetDistance( val.GetCenter() );

	Vec3 halfSize = val.GetSize() * 0.5f;
	XE::real maxAbsDist = Mathf::Abs( normal.x * halfSize.x ) + Mathf::Abs( normal.y * halfSize.y ) + Mathf::Abs( normal.z * halfSize.z );

	if ( dist < -maxAbsDist )
		return SideType::NEGATIVE;

	if ( dist > +maxAbsDist )
		return SideType::POSITIVE;

	return SideType::BOTH;
}

XE::SideType XE::Plane::GetSide( const Sphere& val ) const
{
	XE::real dist = GetDistance( val.center );
	XE::real radius = val.radius;

	if ( dist < -radius )
		return SideType::NEGATIVE;

	if ( dist > +radius )
		return SideType::POSITIVE;

	return SideType::BOTH;
}

XE::real XE::Plane::Normalize()
{
	XE::real fLength = Mathf::Length( normal );

	if ( fLength > Mathf::Epsilon )
	{
		XE::real fInvLength = 1.0f / fLength;
		normal *= fInvLength;
		distance *= fInvLength;
	}

	return fLength;
}

XE::real XE::Plane::GetDistance( const Vec3& val ) const
{
	return Mathf::Dot( normal, val ) - distance;
}

bool XE::Plane::Intersect( const AABB& val ) const
{
	return val.Intersect( *this );
}

bool XE::Plane::Intersect( const Sphere& val ) const
{
	return val.Intersect( *this );
}

std::pair<bool, XE::real> XE::Plane::Intersect( const Ray& val, bool discardInside/* = true*/ ) const
{
	XE::real denom = Mathf::Dot( normal, val.direction );
	if ( Mathf::Abs( denom ) < Mathf::Epsilon )
	{
		return std::pair<bool, XE::real>( false, 0.0f );
	}

	XE::real nom = Mathf::Dot( normal, val.origin ) - distance;
	XE::real t = -( nom / denom );
	return std::pair<bool, XE::real>( t >= 0.0f, t );
}

XE::Vec3 XE::Plane::Project( const Vec3& val ) const
{
	Mat3 xform;
	xform[0][0] = 1.0f - normal.x * normal.x;
	xform[0][1] = -normal.x * normal.y;
	xform[0][2] = -normal.x * normal.z;
	xform[1][0] = -normal.y * normal.x;
	xform[1][1] = 1.0f - normal.y * normal.y;
	xform[1][2] = -normal.y * normal.z;
	xform[2][0] = -normal.z * normal.x;
	xform[2][1] = -normal.z * normal.y;
	xform[2][2] = 1.0f - normal.z * normal.z;
	return xform * val;
}
