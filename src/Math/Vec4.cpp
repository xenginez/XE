#include "Vec4.h"

#include "Mathf.h"



BEG_META( XE::Vec4 )
type->Property( "x", &Vec4::x );
type->Property( "y", &Vec4::y );
type->Property( "z", &Vec4::z );
type->Property( "w", &Vec4::w );
END_META()


const XE::Vec4 XE::Vec4::One = { 1, 1, 1, 1 };
const XE::Vec4 XE::Vec4::Zero = { 0, 0, 0, 0 };
const XE::Vec4 XE::Vec4::Infinity = { XE::Mathf::Infinity , XE::Mathf::Infinity, XE::Mathf::Infinity, XE::Mathf::Infinity };


XE::Vec4::Vec4()
	:x( 0 ), y( 0 ), z( 0 ), w( 0 )
{
}

XE::Vec4::Vec4( XE::real x, XE::real y, XE::real z, XE::real w )
	: x( x ), y( y ), z( z ), w( w )
{
}

XE::Vec4::Vec4( const XE::Vec4& val )
	: x( val.x ), y( val.y ), z( val.z ), w( val.w )
{
}

XE::Vec4& XE::Vec4::operator=( const XE::Vec4& val )
{
	x = val.x;
	y = val.y;
	z = val.z;
	w = val.w;

	return *this;
}
