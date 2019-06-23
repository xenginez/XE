#include "Line.h"

#include "Mathf.h"

USING_XE

BEG_META( Line )
type->Property( "start", &Line::start );
type->Property( "end", &Line::end );
END_META()

XE::Line::Line()
{

}

XE::Line::Line( const Ray& ray, XE::real distance )
	:start( ray.origin ), end( ray.direction * distance )
{

}

XE::Line::Line( const Vec3& start, const Vec3& end )
	: start( start ), end( end )
{

}

XE::Line::~Line()
{

}

XE::Line& XE::Line::operator=( const Line& val )
{
	start = val.start;
	end = val.end;

	return *this;
}

bool XE::Line::operator==( const Line& val ) const
{
	return start == val.start && end == val.end;
}

bool XE::Line::operator!=( const Line& val ) const
{
	return start != val.start || end != val.end;
}

XE::Ray XE::Line::GetRay() const
{
	return { start, Mathf::Normalize( end - start ) };
}

XE::real XE::Line::GetDistance() const
{
	return Mathf::Distance( start, end );
}

XE::Vec3 XE::Line::GetDirection() const
{
	return Mathf::Normalize( end - start );
}

bool XE::Line::Intersect( const OBB& val ) const
{
	return false;
}

bool XE::Line::Intersect( const AABB& val ) const
{
	return false;
}

bool XE::Line::Intersect( const Line& val ) const
{
	return false;
}

bool XE::Line::Intersect( const Plane& val ) const
{
	return false;
}

bool XE::Line::Intersect( const Sphere& val ) const
{
	return false;
}

bool XE::Line::Intersect( const Frustum& val ) const
{
	return false;
}

std::pair<bool, XE::real> XE::Line::Intersect( const Ray& ray, bool discardInside /*= true */ ) const
{
	return { false, 0.0f };
}
