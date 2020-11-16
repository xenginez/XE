#include "Mat3.h"

BEG_META( XE::Mat3i )
type->Property( "m00", &Mat3i::m00 );
type->Property( "m01", &Mat3i::m01 );
type->Property( "m02", &Mat3i::m02 );
type->Property( "m10", &Mat3i::m10 );
type->Property( "m11", &Mat3i::m11 );
type->Property( "m12", &Mat3i::m12 );
type->Property( "m20", &Mat3i::m20 );
type->Property( "m21", &Mat3i::m21 );
type->Property( "m22", &Mat3i::m22 );
END_META()

BEG_META( XE::Mat3f )
type->Property( "m00", &Mat3f::m00 );
type->Property( "m01", &Mat3f::m01 );
type->Property( "m02", &Mat3f::m02 );
type->Property( "m10", &Mat3f::m10 );
type->Property( "m11", &Mat3f::m11 );
type->Property( "m12", &Mat3f::m12 );
type->Property( "m20", &Mat3f::m20 );
type->Property( "m21", &Mat3f::m21 );
type->Property( "m22", &Mat3f::m22 );
END_META()

BEG_META( XE::Mat3d )
type->Property( "m00", &Mat3d::m00 );
type->Property( "m01", &Mat3d::m01 );
type->Property( "m02", &Mat3d::m02 );
type->Property( "m10", &Mat3d::m10 );
type->Property( "m11", &Mat3d::m11 );
type->Property( "m12", &Mat3d::m12 );
type->Property( "m20", &Mat3d::m20 );
type->Property( "m21", &Mat3d::m21 );
type->Property( "m22", &Mat3d::m22 );
END_META()
