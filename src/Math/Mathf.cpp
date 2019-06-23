#include "Mathf.h"

USING_XE

BEG_META( Mathf )
type->Property( "Pi", &Mathf::Pi );
type->Property( "Pi2", &Mathf::Pi2 );
type->Property( "Pi4", &Mathf::Pi4 );
type->Property( "Nan", &Mathf::Nan );
type->Property( "Epsilon", &Mathf::Epsilon );
type->Property( "Infinity", &Mathf::Infinity );
END_META()


const XE::real Mathf::Pi = 3.141592f;
const XE::real Mathf::Pi2 = 1.570796f;
const XE::real Mathf::Pi4 = 0.7853981f;
const XE::real Mathf::Nan = std::numeric_limits<XE::real>::quiet_NaN();
const XE::real Mathf::Epsilon = std::numeric_limits<XE::real>::epsilon();
const XE::real Mathf::Infinity = std::numeric_limits<XE::real>::infinity();
