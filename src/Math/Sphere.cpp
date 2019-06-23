#include "Sphere.h"

#include "Mathf.h"
#include "Ray.h"
#include "AABB.h"
#include "Plane.h"

USING_XE

BEG_META( Sphere )
type->Property( "center", &Sphere::center );
type->Property( "radius", &Sphere::radius );
END_META()

const XE::Sphere XE::Sphere::Zero = { Vec3::Zero, 0.0f };

XE::Sphere::Sphere()
	: radius( 0 )
{

}

XE::Sphere::Sphere( const Sphere& val )
	: center( val.center ), radius( val.radius )
{

}

XE::Sphere::Sphere( const Vec3&center, XE::real radius )
	: center( center ), radius( radius )
{

}

Sphere& XE::Sphere::operator=( const Sphere & val )
{
	center = val.center;
	radius = val.radius;
	return *this;
}

bool XE::Sphere::operator==( const Sphere& val ) const
{
	return ( Mathf::Abs( radius - val.radius ) <= Mathf::Epsilon ) && center == val.center;
}

bool XE::Sphere::operator!=( const Sphere& val ) const
{
	return ( Mathf::Abs( radius - val.radius ) > Mathf::Epsilon ) || center != val.center;
}

void XE::Sphere::Merge( const Vec3& val )
{
	XE::real dist = Mathf::Distance( val, center );
	radius = Mathf::Max( radius, dist );
}

void XE::Sphere::Merge( const Sphere& val )
{
	Vec3 newCenter = ( center + val.center ) * 0.5f;

	XE::real newRadiusA = Mathf::Distance( newCenter, center ) + radius;
	XE::real newRadiusB = Mathf::Distance( newCenter, val.center ) + val.radius;

	center = newCenter;
	radius = Mathf::Max( newRadiusA, newRadiusB );
}

bool XE::Sphere::Contains( const Vec3& val ) const
{
	return Mathf::SqrLength( val - center ) <= Mathf::Sqrt( radius );
}

bool XE::Sphere::Intersect( const AABB& val ) const
{
	return val.Intersect( *this );
}

bool XE::Sphere::Intersect( const Plane& val ) const
{
	return ( Mathf::Abs( val.GetDistance( center ) ) <= radius );
}

bool XE::Sphere::Intersect( const Sphere& val ) const
{
	return Mathf::SqrLength( val.center - center ) <= Mathf::Sqrt( val.radius + radius );
}

std::pair<bool, XE::real> XE::Sphere::Intersect( const Ray& ray, bool discardInside /*= true */ ) const
{
	const Vec3& raydir = ray.direction;
	const Vec3& rayorig = ray.origin - center;

	if ( Mathf::SqrLength( rayorig ) <= radius * radius && discardInside )
	{
		return std::pair<bool, XE::real>( true, 0.0f );
	}

	XE::real a = Mathf::Dot( raydir, raydir );
	XE::real b = 2 * Mathf::Dot( rayorig, raydir );
	XE::real c = Mathf::Dot( rayorig, rayorig ) - radius * radius;

	XE::real d = ( b * b ) - ( 4 * a * c );
	if ( d < 0 )
	{
		return std::pair<bool, XE::real>( false, 0.0f );
	}
	else
	{
		XE::real t = ( -b - Mathf::Sqrt( d ) ) / ( 2 * a );
		if ( t < 0 )
			t = ( -b + Mathf::Sqrt( d ) ) / ( 2 * a );

		return std::pair<bool, XE::real>( true, t );
	}
}

void XE::Sphere::Transform( const Mat4& val )
{
	XE::real lengthSqrd[3];
	for ( XE::uint32 i = 0; i < 3; i++ )
	{
		Vec3 column( val[0][i], val[1][i], val[2][i] );
		lengthSqrd[i] = Mathf::Dot( column, column );
	}

	XE::real maxLengthSqrd = Mathf::Max( lengthSqrd[0], Mathf::Max( lengthSqrd[1], lengthSqrd[2] ) );

	center = Mathf::MultiplyAffine( val, center );
	radius *= Mathf::Sqrt( maxLengthSqrd );
}
