#include "Vec2.h"

BEG_META( XE::Vec2i )
type->Property( "x", &Vec2i::x );
type->Property( "y", &Vec2i::y );
END_META()

BEG_META( XE::Vec2f )
type->Property( "x", &Vec2f::x );
type->Property( "y", &Vec2f::y );
END_META()

BEG_META( XE::Vec2d )
type->Property( "x", &Vec2d::x );
type->Property( "y", &Vec2d::y );
END_META()
