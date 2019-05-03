#include "Ray.h"

#include "Mathf.h"
#include "AABB.h"
#include "Plane.h"
#include "Sphere.h"

USING_XE

BEGIN_META( Ray )
type->Property( "origin", &Ray::origin );
type->Property( "direction", &Ray::direction );
END_META()


Ray::Ray()
{
}

Ray::Ray( const Vec3& origin, const Vec3& direction )
	:origin( origin ), direction( direction )
{

}

XE::Ray& XE::Ray::operator=( const Ray & val )
{
	origin = val.origin;
	direction = val.direction;
	return *this;
}

bool XE::Ray::operator==( const Ray& val ) const
{
	return origin == val.origin && direction == val.direction;
}

bool XE::Ray::operator!=( const Ray& val ) const
{
	return origin != val.origin || direction != val.direction;
}

XE::Vec3 XE::Ray::GetPoint( float val ) const
{
	return origin + ( direction * val );
}

std::pair<bool, float> XE::Ray::Intersect( const AABB& val ) const
{
	return val.Intersect( *this );
}

std::pair<bool, float> XE::Ray::Intersect( const Plane& val ) const
{
	return val.Intersect( *this );
}

std::pair<bool, float> XE::Ray::Intersect( const Sphere& val ) const
{
	return val.Intersect( *this );
}

std::pair<bool, float> XE::Ray::Intersect( const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& normal, bool positiveSide /*= true*/, bool negativeSide /*= true */ ) const
{
	float t;
	{
		float denom = Mathf::Dot( normal, direction );

		if ( denom > + Mathf::Epsilon )
		{
			if ( !negativeSide )
				return std::pair<bool, float>( false, 0.0f );
		}
		else if ( denom < -Mathf::Epsilon )
		{
			if ( !positiveSide )
				return std::pair<bool, float>( false, 0.0f );
		}
		else
		{
			return std::pair<bool, float>( false, 0.0f );
		}

		
		t = Mathf::Dot( normal, a - origin ) / denom;

		if ( t < 0 )
		{
			return std::pair<bool, float>( false, 0.0f );
		}
	}

	uint32 i0, i1;
	{
		float n0 = Mathf::Abs( normal[0] );
		float n1 = Mathf::Abs( normal[1] );
		float n2 = Mathf::Abs( normal[2] );

		i0 = 1; i1 = 2;
		if ( n1 > n2 )
		{
			if ( n1 > n0 ) i0 = 0;
		}
		else
		{
			if ( n2 > n0 ) i1 = 0;
		}
	}

	{
		float u1 = b[i0] - a[i0];
		float v1 = b[i1] - a[i1];
		float u2 = c[i0] - a[i0];
		float v2 = c[i1] - a[i1];
		float u0 = t * direction[i0] + origin[i0] - a[i0];
		float v0 = t * direction[i1] + origin[i1] - a[i1];

		float alpha = u0 * v2 - u2 * v0;
		float beta = u1 * v0 - u0 * v1;
		float area = u1 * v2 - u2 * v1;

		float tolerance = -Mathf::Epsilon * area;

		if ( area > 0 )
		{
			if ( alpha < tolerance || beta < tolerance || alpha + beta > area - tolerance )
				return std::pair<bool, float>( false, 0.0f );
		}
		else
		{
			if ( alpha > tolerance || beta > tolerance || alpha + beta < area - tolerance )
				return std::pair<bool, float>( false, 0.0f );
		}
	}

	return std::pair<bool, float>( true, t );
}

void XE::Ray::Transform( const Mat4& val )
{
	Vec3 end = GetPoint( 1.0f );

	origin = val * origin;
	end = val * end;

	direction = Mathf::Normalize( end - origin );
}

void XE::Ray::TransformAffine( const Mat4& val )
{
	Vec3 end = GetPoint( 1.0f );

	origin = Mathf::MultiplyAffine( val, origin );
	end = Mathf::MultiplyAffine( val, end );

	direction = Mathf::Normalize( end - origin );
}
