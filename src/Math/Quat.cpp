#include "Quat.h"

#include "Mathf.h"

BEG_META( XE::Quat )
type->Property( "x", &Quat::x );
type->Property( "y", &Quat::y );
type->Property( "z", &Quat::z );
type->Property( "w", &Quat::w );
END_META()

const XE::Quat XE::Quat::Zero = { 0, 0, 0, 0 };
const XE::Quat XE::Quat::Identity = { 0, 0, 0, 1 };


XE::Quat::Quat()
	:x( 0 ), y( 0 ), z( 0 ), w( 1 )
{
}

XE::Quat::Quat( const Quat& val )
	: x( val.x ), y( val.y ), z( val.z ), w( val.w )
{

}

XE::Quat::Quat( XE::float32 x, XE::float32 y, XE::float32 z, XE::float32 w )
	: x( x ), y( y ), z( z ), w( w )
{

}

XE::Quat& XE::Quat::operator=( const Quat& val )
{
	x = val.x;
	y = val.y;
	z = val.z;
	w = val.w;
	return *this;
}

