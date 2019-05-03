#include "Mathf.h"

USING_XE

BEGIN_META( Mathf )
type->Property( "Pi", &Mathf::Pi );
type->Property( "Pi2", &Mathf::Pi2 );
type->Property( "Pi4", &Mathf::Pi4 );
type->Property( "Nan", &Mathf::Nan );
type->Property( "Epsilon", &Mathf::Epsilon );
type->Property( "Infinity", &Mathf::Infinity );
END_META()


const float Mathf::Pi = 3.141592f;
const float Mathf::Pi2 = 1.570796f;
const float Mathf::Pi4 = 0.7853981f;
const float Mathf::Nan = std::numeric_limits<float>::quiet_NaN();
const float Mathf::Epsilon = std::numeric_limits<float>::epsilon();
const float Mathf::Infinity = std::numeric_limits<float>::infinity();
