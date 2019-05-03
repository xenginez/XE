#include "Type.h"

USING_XE

BEGIN_META( SideType )
type->Value( "NOOP", SideType::NOOP );
type->Value( "BOTH", SideType::BOTH );
type->Value( "POSITIVE", SideType::POSITIVE );
type->Value( "NEGATIVE", SideType::NEGATIVE );
END_META()


BEGIN_META( AxisType )
type->Value( "X", AxisType::X );
type->Value( "Y", AxisType::Y );
type->Value( "Z", AxisType::Z );
type->Value( "XY", AxisType::XY );
type->Value( "XZ", AxisType::XZ );
type->Value( "YZ", AxisType::YZ );
type->Value( "XYZ", AxisType::XYZ );
END_META()


BEGIN_META( RotationType )
type->Value( "XYZ", RotationType::XYZ );
type->Value( "XZY", RotationType::XZY );
type->Value( "YXZ", RotationType::YXZ );
type->Value( "YZX", RotationType::YZX );
type->Value( "ZXY", RotationType::ZXY );
type->Value( "ZYX", RotationType::ZYX );
END_META()
