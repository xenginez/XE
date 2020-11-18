#include "Rect.h"

BEG_META( XE::Recti )
type->Property( "x", &XE::Recti::x );
type->Property( "y", &XE::Recti::y );
type->Property( "width", &XE::Recti::width );
type->Property( "height", &XE::Recti::height );
END_META()

BEG_META( XE::Rectf )
type->Property( "x", &XE::Rectf::x );
type->Property( "y", &XE::Rectf::y );
type->Property( "width", &XE::Rectf::width );
type->Property( "height", &XE::Rectf::height );
END_META()

BEG_META( XE::Rectd )
type->Property( "x", &XE::Rectd::x );
type->Property( "y", &XE::Rectd::y );
type->Property( "width", &XE::Rectd::width );
type->Property( "height", &XE::Rectd::height );
END_META()
