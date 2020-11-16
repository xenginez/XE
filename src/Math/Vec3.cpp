#include "Vec3.h"

BEG_META( XE::Vec3i )
type->Property( "x", &Vec3i::x );
type->Property( "y", &Vec3i::y );
type->Property( "z", &Vec3i::z );
END_META()

BEG_META( XE::Vec3f )
type->Property( "x", &Vec3f::x );
type->Property( "y", &Vec3f::y );
type->Property( "z", &Vec3f::z );
END_META()

BEG_META( XE::Vec3d )
type->Property( "x", &Vec3d::x );
type->Property( "y", &Vec3d::y );
type->Property( "z", &Vec3d::z );
END_META()
