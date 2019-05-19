#include "Quat.h"

#include "Mathf.h"

USING_XE

BEG_META( Quat )
type->Property( "x", &Quat::x );
type->Property( "y", &Quat::y );
type->Property( "z", &Quat::z );
type->Property( "w", &Quat::w );
END_META()

const Quat Quat::Zero = { 0, 0, 0, 0 };
const Quat Quat::Identity = { 0, 0, 0, 1 };


XE::Quat::Quat()
	:x( 0 ), y( 0 ), z( 0 ), w( 0 )
{
}

XE::Quat::Quat( const Quat& val )
	: x( val.x ), y( val.y ), z( val.z ), w( val.w )
{

}

XE::Quat::Quat( float x, float y, float z, float w )
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

