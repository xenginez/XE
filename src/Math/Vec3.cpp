#include "Vec3.h"

#include "Mathf.h"

USING_XE

BEG_META( Vec3 )
type->Property( "x", &Vec3::x );
type->Property( "y", &Vec3::y );
type->Property( "z", &Vec3::z );
END_META()

const Vec3 Vec3::One = { 1, 1, 1 };
const Vec3 Vec3::Zero = { 0, 0, 0 };
const Vec3 Vec3::Forward = { 0, 0, 1 };
const Vec3 Vec3::Backward = { 0, 0, -1 };
const Vec3 Vec3::Left = { -1, 0, 0 };
const Vec3 Vec3::Right = { 1, 0, 0 };
const Vec3 Vec3::Up = { 0, 1, 0 };
const Vec3 Vec3::Down = { 0, -1, 0 };
const Vec3 Vec3::Infinity = { Mathf::Infinity , Mathf::Infinity, Mathf::Infinity };

XE::Vec3::Vec3()
	:x( 0 ), y( 0 ), z( 0 )
{
}

XE::Vec3::Vec3( float val )
	: x( val ), y( val ), z( val )
{

}

XE::Vec3::Vec3( const Vec3& val )
	: x( val.x ), y( val.y ), z( val.z )
{

}

XE::Vec3::Vec3( float x, float y, float z )
	: x( x ), y( y ), z( z )
{

}

XE::Vec3& XE::Vec3::operator=( float val )
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
