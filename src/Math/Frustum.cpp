#include "Frustum.h"

USING_XE

BEG_META( Frustum )
type->Property( "top", &Frustum::top );
type->Property( "bottom", &Frustum::bottom );
type->Property( "left", &Frustum::left );
type->Property( "right", &Frustum::right );
type->Property( "near", &Frustum::near );
type->Property( "far", &Frustum::far );
END_META()

XE::Frustum::Frustum()
{

}

XE::Frustum::~Frustum()
{

}
