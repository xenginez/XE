#include "Vec2.h"

#include "Mathf.h"

USING_XE

BEG_META( Vec2 )
type->Property( "x", &Vec2::x );
type->Property( "y", &Vec2::y );
END_META()

const XE::Vec2 XE::Vec2::One = { 1 , 1 };
const XE::Vec2 XE::Vec2::Zero = { 0 , 0 };
const XE::Vec2 XE::Vec2::Infinity = { Mathf::Infinity , Mathf::Infinity };

XE::Vec2::Vec2()
	:x( 0 ), y( 0 )
{

}

XE::Vec2::Vec2( float val )
	: x( val ), y( val )
{

}

XE::Vec2::Vec2( const Vec2& val )
	: x( val.x ), y( val.y )
{

}

XE::Vec2::Vec2( float x, float y )
	: x( x ), y( y )
{

}

XE::Vec2& XE::Vec2::operator=( float val )
{
	x = val;
	y = val;
	return *this;
}

XE::Vec2& XE::Vec2::operator=( const XE::Vec2& val )
{
	x = val.x;
	y = val.y;
	return *this;
}
