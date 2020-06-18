#include "Vec3.h"

#include "Mathf.h"



BEG_META( XE::Vec3 )
type->Property( "x", &Vec3::x );
type->Property( "y", &Vec3::y );
type->Property( "z", &Vec3::z );
END_META()

const XE::Vec3 XE::Vec3::One = { 1, 1, 1 };
const XE::Vec3 XE::Vec3::Zero = { 0, 0, 0 };
const XE::Vec3 XE::Vec3::Forward = { 0, 0, 1 };
const XE::Vec3 XE::Vec3::Backward = { 0, 0, -1 };
const XE::Vec3 XE::Vec3::Left = { -1, 0, 0 };
const XE::Vec3 XE::Vec3::Right = { 1, 0, 0 };
const XE::Vec3 XE::Vec3::Up = { 0, 1, 0 };
const XE::Vec3 XE::Vec3::Down = { 0, -1, 0 };
const XE::Vec3 XE::Vec3::Infinity = { XE::Mathf::Infinity , XE::Mathf::Infinity, XE::Mathf::Infinity };

XE::Vec3::Vec3()
	:x( 0 ), y( 0 ), z( 0 )
{
}

XE::Vec3::Vec3( XE::real val )
	: x( val ), y( val ), z( val )
{

}

XE::Vec3::Vec3( const Vec3& val )
	: x( val.x ), y( val.y ), z( val.z )
{

}

XE::Vec3::Vec3( XE::real x, XE::real y, XE::real z )
	: x( x ), y( y ), z( z )
{

}

XE::Vec3& XE::Vec3::operator=( XE::real val )
{
	x = val;
	y = val;
	z = val;
	return *this;
}

XE::Vec3& XE::Vec3::operator=( const XE::Vec3 & val )
{
	x = val.x;
	y = val.y;
	z = val.z;
	return *this;
}
