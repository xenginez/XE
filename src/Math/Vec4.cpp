#include "Vec4.h"

BEG_META( XE::Vec4i )
type->Property( "x", &Vec4i::x );
type->Property( "y", &Vec4i::y );
type->Property( "z", &Vec4i::z );
type->Property( "w", &Vec4i::w );
END_META()

BEG_META( XE::Vec4f )
type->Property( "x", &Vec4f::x );
type->Property( "y", &Vec4f::y );
type->Property( "z", &Vec4f::z );
type->Property( "w", &Vec4f::w );
END_META()

BEG_META( XE::Vec4d )
type->Property( "x", &Vec4d::x );
type->Property( "y", &Vec4d::y );
type->Property( "z", &Vec4d::z );
type->Property( "w", &Vec4d::w );
END_META()
