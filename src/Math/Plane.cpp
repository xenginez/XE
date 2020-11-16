#include "Plane.h"

#include "Mathf.h"
#include "Ray.h"
#include "AABB.h"
#include "Sphere.h"

BEG_META( XE::Plane )
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

XE::Plane::Plane( const Vec3f& normal, XE::float32 d )
	: normal( normal ), distance( d )
{

}

XE::Plane::Plane( XE::float32 a, XE::float32 b, XE::float32 c, XE::float32 d )
	: normal( a, b, c ), distance( d )
{

}

XE::Plane::Plane( const Vec3f& normal, const Vec3f& point )
	: normal( normal ), distance( Mathf::Dot(normal, point ) )
{

}

XE::Plane::Plane( const Vec3f& point0, const Vec3f& point1, const Vec3f& point2 )
{
	Vec3f kEdge1 = point1 - point0;
	Vec3f kEdge2 = point2 - point0;
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

XE::SideType XE::Plane::GetSide( const Vec3f& val ) const
{
	XE::float32 dist = GetDistance( val );

	if ( dist > Mathf::Epsilon )
		return SideType::POSITIVE;

	if ( dist < -Mathf::Epsilon )
		return SideType::NEGATIVE;

	return SideType::NOOP;
}

XE::SideType XE::Plane::GetSide( const AABB& val ) const
{
	XE::float32 dist = GetDistance( val.GetCenter() );

	Vec3f halfSize = val.GetSize() * 0.5f;
	XE::float32 maxAbsDist = Mathf::Abs( normal.x * halfSize.x ) + Mathf::Abs( normal.y * halfSize.y ) + Mathf::Abs( normal.z * halfSize.z );

	if ( dist < -maxAbsDist )
		return SideType::NEGATIVE;

	if ( dist > +maxAbsDist )
		return SideType::POSITIVE;

	return SideType::BOTH;
}

XE::SideType XE::Plane::GetSide( const Sphere& val ) const
{
	XE::float32 dist = GetDistance( val.center );
	XE::float32 radius = val.radius;

	if ( dist < -radius )
		return SideType::NEGATIVE;

	if ( dist > +radius )
		return SideType::POSITIVE;

	return SideType::BOTH;
}

XE::float32 XE::Plane::Normalize()
{
	XE::float32 fLength = Mathf::Length( normal );

	if ( fLength > Mathf::Epsilon )
	{
		XE::float32 fInvLength = 1.0f / fLength;
		normal *= fInvLength;
		distance *= fInvLength;
	}

	return fLength;
}

XE::float32 XE::Plane::GetDistance( const Vec3f& val ) const
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

std::pair<bool, XE::float32> XE::Plane::Intersect( const Ray& val, bool discardInside/* = true*/ ) const
{
	XE::float32 denom = Mathf::Dot( normal, val.direction );
	if ( Mathf::Abs( denom ) < Mathf::Epsilon )
	{
		return std::pair<bool, XE::float32>( false, 0.0f );
	}

	XE::float32 nom = Mathf::Dot( normal, val.origin ) - distance;
	XE::float32 t = -( nom / denom );
	return std::pair<bool, XE::float32>( t >= 0.0f, t );
}

XE::Vec3f XE::Plane::Project( const Vec3f& val ) const
{
	Mat3f xform;
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
