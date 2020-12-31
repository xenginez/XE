#include "AABB.h"

#include "Mathf.h"
#include "Ray.h"
#include "Plane.h"
#include "Sphere.h"

BEG_META( XE::AABB )
type->Property( "min", &AABB::min );
type->Property( "max", &AABB::max );
END_META()

XE::AABB::AABB()
{
}

XE::AABB::AABB( const AABB& val )
	:min( val.min ), max( val.max )
{

}

XE::AABB::AABB( const Vec3f& min, const Vec3f& max )
	: min( min ), max( max )
{

}

XE::AABB& XE::AABB::operator=( const AABB& val )
{
	if ( &val != this )
	{
		min = val.min;
		max = val.max;
	}

	return *this;
}

bool XE::AABB::operator==( const AABB& val ) const
{
	return min == val.min && max == val.max;
}

bool XE::AABB::operator!=( const AABB& val ) const
{
	return min != val.min || max != val.max;
}

XE::Vec3f XE::AABB::GetSize() const
{
	return max - min;
}

XE::Vec3f XE::AABB::GetCenter() const
{
	return ( max + min ) / 2;
}

XE::float32 XE::AABB::GetRadius() const
{
	return Mathf::Length( ( max - min ) * 0.5 );
}

XE::float32 XE::AABB::GetVolume() const
{
	Vec3f diff = max - min;
	return diff.x * diff.y * diff.z;
}

XE::Vec3f XE::AABB::GetFarLeftTop() const
{
	return { min.x, max.y, min.z };
}

XE::Vec3f XE::AABB::GetFarRightTop() const
{
	return { max.x, max.y, min.z };
}

XE::Vec3f XE::AABB::GetFarLeftBottom() const
{
	return { min.x, min.y, min.z };
}

XE::Vec3f XE::AABB::GetFarRightBottom() const
{
	return { max.x, min.y, min.z };
}

XE::Vec3f XE::AABB::GetNearLeftTop() const
{
	return { min.x, max.y, max.z };
}

XE::Vec3f XE::AABB::GetNearRightTop() const
{
	return { max.x, max.y, max.z };
}

XE::Vec3f XE::AABB::GetNearLeftBottom() const
{
	return { min.x, min.y, max.z };
}

XE::Vec3f XE::AABB::GetNearRightBottom() const
{
	return { max.x, min.y, max.z };
}

bool XE::AABB::Contains( const Vec3f& val ) const
{
	return min.x <= val.x && val.x <= max.x &&
		min.y <= val.y && val.y <= max.y &&
		min.z <= val.z && val.z <= max.z;
}

bool XE::AABB::Contains( const AABB& val ) const
{
	return min.x <= val.min.x &&
		   min.y <= val.min.y &&
		   min.z <= val.min.z &&
		   val.max.x <= max.x &&
		   val.max.y <= max.y &&
		   val.max.z <= max.z;
}

bool XE::AABB::Intersect( const OBB & val ) const
{
	// todo:
	return false;
}

bool XE::AABB::Intersect( const AABB& val ) const
{
	if ( max.x < val.min.x )
		return false;
	if ( max.y < val.min.y )
		return false;
	if ( max.z < val.min.z )
		return false;

	if ( min.x > val.max.x )
		return false;
	if ( min.y > val.max.y )
		return false;
	if ( min.z > val.max.z )
		return false;

	return true;
}

bool XE::AABB::Intersect( const Line & val ) const
{
	// todo:
	return false;
}

bool XE::AABB::Intersect( const Plane& val ) const
{
	return ( val.GetSide( *this ) == SideType::BOTH );
}

bool XE::AABB::Intersect( const Sphere& val ) const
{
	XE::float32 radius = val.radius;
	const Vec3f& center = val.center;

	XE::float32 s, d = 0;
	for ( int i = 0; i < 3; ++i )
	{
		if ( center[i] < min[i] )
		{
			s = center[i] - min[i];
			d += s * s;
		}
		else if ( center[i] > max[i] )
		{
			s = center[i] - max[i];
			d += s * s;
		}
	}
	return d <= radius * radius;
}

bool XE::AABB::Intersect( const Frustum & val ) const
{
	// todo:
	return false;
}

std::pair<bool, XE::float32> XE::AABB::Intersect( const Ray& ray, bool discardInside /*= true */ ) const
{
	XE::float32 lowt = 0.0f;
	XE::float32 t;
	bool hit = false;
	Vec3f hitpoint;
	const Vec3f& rayorig = ray.origin;
	const Vec3f& raydir = ray.direction;

	if ( ( rayorig.x > min.x && rayorig.y > min.y && rayorig.z > min.z ) && ( rayorig.x < max.x && rayorig.y < max.y && rayorig.z < max.z ) )
	{
		return std::pair<bool, XE::float32>( true, 0.0f );
	}

	if ( rayorig.x <= min.x && raydir.x > 0 )
	{
		t = ( min.x - rayorig.x ) / raydir.x;
		if ( t >= 0 )
		{
			hitpoint = rayorig + raydir * t;
			if ( hitpoint.y >= min.y && hitpoint.y <= max.y &&
				 hitpoint.z >= min.z && hitpoint.z <= max.z &&
				 ( !hit || t < lowt ) )
			{
				hit = true;
				lowt = t;
			}
		}
	}

	if ( rayorig.x >= max.x && raydir.x < 0 )
	{
		t = ( max.x - rayorig.x ) / raydir.x;
		if ( t >= 0 )
		{
			hitpoint = rayorig + raydir * t;
			if ( hitpoint.y >= min.y && hitpoint.y <= max.y &&
				 hitpoint.z >= min.z && hitpoint.z <= max.z &&
				 ( !hit || t < lowt ) )
			{
				hit = true;
				lowt = t;
			}
		}
	}

	if ( rayorig.y <= min.y && raydir.y > 0 )
	{
		t = ( min.y - rayorig.y ) / raydir.y;
		if ( t >= 0 )
		{
			hitpoint = rayorig + raydir * t;
			if ( hitpoint.x >= min.x && hitpoint.x <= max.x &&
				 hitpoint.z >= min.z && hitpoint.z <= max.z &&
				 ( !hit || t < lowt ) )
			{
				hit = true;
				lowt = t;
			}
		}
	}

	if ( rayorig.y >= max.y && raydir.y < 0 )
	{
		t = ( max.y - rayorig.y ) / raydir.y;
		if ( t >= 0 )
		{
			hitpoint = rayorig + raydir * t;
			if ( hitpoint.x >= min.x && hitpoint.x <= max.x &&
				 hitpoint.z >= min.z && hitpoint.z <= max.z &&
				 ( !hit || t < lowt ) )
			{
				hit = true;
				lowt = t;
			}
		}
	}

	if ( rayorig.z <= min.z && raydir.z > 0 )
	{
		t = ( min.z - rayorig.z ) / raydir.z;
		if ( t >= 0 )
		{
			hitpoint = rayorig + raydir * t;
			if ( hitpoint.x >= min.x && hitpoint.x <= max.x &&
				 hitpoint.y >= min.y && hitpoint.y <= max.y &&
				 ( !hit || t < lowt ) )
			{
				hit = true;
				lowt = t;
			}
		}
	}
	
	if ( rayorig.z >= max.z && raydir.z < 0 )
	{
		t = ( max.z - rayorig.z ) / raydir.z;
		if ( t >= 0 )
		{
			hitpoint = rayorig + raydir * t;
			if ( hitpoint.x >= min.x && hitpoint.x <= max.x &&
				 hitpoint.y >= min.y && hitpoint.y <= max.y &&
				 ( !hit || t < lowt ) )
			{
				hit = true;
				lowt = t;
			}
		}
	}

	return std::pair<bool, XE::float32>( hit, lowt );
}

void XE::AABB::Scale( XE::float32 val )
{
	Vec3f center = GetCenter();
	min = center + ( min - center ) * val;
	max = center + ( max - center ) * val;
}

void XE::AABB::Scale( const Vec3f& val )
{
	Vec3f center = GetCenter();
	min = center + ( min - center ) * val;
	max = center + ( max - center ) * val;
}

void XE::AABB::Merge( const Vec3f& val )
{
	max = Mathf::Max( max, val );
	min = Mathf::Min( min, val );
}

void XE::AABB::Merge( const AABB& val )
{
	max = Mathf::Max( max, val.max );
	min = Mathf::Min( min, val.min );
}

void XE::AABB::Transform( const Mat4x4f& matrix )
{
	Vec3f corner;
	Vec3f old_min = min;
	Vec3f old_max = max;

	corner = old_min;
	Merge( Mathf::MultiplyAffine( matrix, corner ) );

	corner.z = old_max.z;
	Merge( Mathf::MultiplyAffine( matrix, corner ) );

	corner.y = old_max.y;
	Merge( Mathf::MultiplyAffine( matrix, corner ) );

	corner.z = old_min.z;
	Merge( Mathf::MultiplyAffine( matrix, corner ) );

	corner.x = old_max.x;
	Merge( Mathf::MultiplyAffine( matrix, corner ) );

	corner.z = old_max.z;
	Merge( Mathf::MultiplyAffine( matrix, corner ) );

	corner.y = old_min.y;
	Merge( Mathf::MultiplyAffine( matrix, corner ) );

	corner.z = old_min.z;
	Merge( Mathf::MultiplyAffine( matrix, corner ) );
}

void XE::AABB::TransformAffine( const Mat4x4f& val )
{
	Vec3f min = Mathf::Translation( val );
	Vec3f max = Mathf::Translation( val );

	for ( XE::uint32 i = 0; i < 3; i++ )
	{
		for ( XE::uint32 j = 0; j < 3; j++ )
		{
			XE::float32 e = val[i][j] * this->min[j];
			XE::float32 f = val[i][j] * this->max[j];

			if ( e < f )
			{
				min[i] += e;
				max[i] += f;
			}
			else
			{
				min[i] += f;
				max[i] += e;
			}
		}

	}

	this->min = min;
	this->max = max;
}
