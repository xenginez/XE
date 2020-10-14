#include "Vec2.h"

#include "Mathf.h"

BEG_META( XE::Vec2 )
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

XE::Vec2::Vec2( XE::float32 val )
	: x( val ), y( val )
{

}

XE::Vec2::Vec2( const Vec2& val )
	: x( val.x ), y( val.y )
{

}

XE::Vec2::Vec2( XE::float32 x, XE::float32 y )
	: x( x ), y( y )
{

}

XE::Vec2& XE::Vec2::operator=( XE::float32 val )
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
