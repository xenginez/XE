#include "float16.h"



BEG_META( XE::float16 )
END_META()

const XE::float16 XE::float16::Nan = std::numeric_limits < XE::float32 >::quiet_NaN();
const XE::float16 XE::float16::Epsilon = std::numeric_limits < XE::float32 >::epsilon();
const XE::float16 XE::float16::Infinity = std::numeric_limits < XE::float32 >::infinity();

XE::float16::float16()
		:encode(0)
{

}

XE::float16::float16( XE::float32 val )
{
	FormFloat32(val);
}

XE::float16::float16( const XE::float16 &val )
		:encode(val.encode)
{

}

XE::float16::~float16()
{

}

XE::float16 &XE::float16::operator =( XE::float32 val )
{
	FormFloat32(val);
	
	return *this;
}

XE::float16 &XE::float16::operator =( XE::float16 val )
{
	encode = val.encode;
	
	return *this;
}

XE::float16::operator XE::float32() const
{
	return ToFloat32();
}

bool XE::float16::operator <( XE::float16 val ) const
{
	return encode < val.encode;
}

bool XE::float16::operator >( XE::float16 val ) const
{
	return encode > val.encode;
}

bool XE::float16::operator <=( XE::float16 val ) const
{
	return encode <= val.encode;
}

bool XE::float16::operator >=( XE::float16 val ) const
{
	return encode >= val.encode;
}

bool XE::float16::operator ==( XE::float16 val ) const
{
	return encode == val.encode;
}

bool XE::float16::operator !=( XE::float16 val ) const
{
	return encode != val.encode;
}

bool XE::float16::operator <( XE::float32 val ) const
{
	return ToFloat32() < val;
}

bool XE::float16::operator >( XE::float32 val ) const
{
	return ToFloat32() > val;
}

bool XE::float16::operator <=( XE::float32 val ) const
{
	return ToFloat32() <= val;
}

bool XE::float16::operator >=( XE::float32 val ) const
{
	return ToFloat32() >= val;
}

bool XE::float16::operator ==( XE::float32 val ) const
{
	return ToFloat32() == val;
}

bool XE::float16::operator !=( XE::float32 val ) const
{
	return ToFloat32() != val;
}

XE::float32 XE::float16::ToFloat32() const
{
	union _float32
	{
		struct
		{
#if ENDIAN == ENDIAN_LITTLE
			XE::uint32 mantissa
					: 23;
			XE::uint16 exponent
					: 8;
			XE::uint16 sign
					: 1;
#else
			XE::uint16 sign : 1;
			XE::uint16 exponent : 8;
			XE::uint16 mantissa : 23;
#endif
		};
		
		XE::float32 encode;
	};
	
	_float32 f{};
	
	f.sign = sign;
	f.exponent = exponent;
	f.mantissa = mantissa;
	
	return f.encode;
}

void XE::float16::FormFloat32( XE::float32 val )
{
	union _float32
	{
		struct
		{
#if ENDIAN == ENDIAN_LITTLE
			XE::uint32 mantissa
					: 23;
			XE::uint16 exponent
					: 8;
			XE::uint16 sign
					: 1;
#else
			XE::uint16 sign : 1;
			XE::uint16 exponent : 8;
			XE::uint16 mantissa : 23;
#endif
		};
		
		XE::float32 encode;
	};
	
	_float32 f{};
	
	f.encode = val;
	
	sign = f.sign;
	exponent = f.exponent;
	mantissa = f.mantissa;
}

bool operator <( XE::float32 val1, XE::float16 val2 )
{
	return val1 < val2.ToFloat32();
}

bool operator >( XE::float32 val1, XE::float16 val2 )
{
	return val1 > val2.ToFloat32();
}

bool operator <=( XE::float32 val1, XE::float16 val2 )
{
	return val1 <= val2.ToFloat32();
}

bool operator >=( XE::float32 val1, XE::float16 val2 )
{
	return val1 >= val2.ToFloat32();
}

bool operator ==( XE::float32 val1, XE::float16 val2 )
{
	return val1 == val2.ToFloat32();
}

bool operator !=( XE::float32 val1, XE::float16 val2 )
{
	return val1 != val2.ToFloat32();
}
