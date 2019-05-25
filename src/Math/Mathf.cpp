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


const XE::float32 Mathf::Pi = 3.141592f;
const XE::float32 Mathf::Pi2 = 1.570796f;
const XE::float32 Mathf::Pi4 = 0.7853981f;
const XE::float32 Mathf::Nan = std::numeric_limits<XE::float32>::quiet_NaN();
const XE::float32 Mathf::Epsilon = std::numeric_limits<XE::float32>::epsilon();
const XE::float32 Mathf::Infinity = std::numeric_limits<XE::float32>::infinity();
