/*!
 * \file   float16.h
 *
 * \author ZhengYuanQing
 * \date   2019/02/25
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __FLOAT16_H__A3198368_5080_4B3C_9DD7_867156762D19
#define __FLOAT16_H__A3198368_5080_4B3C_9DD7_867156762D19

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API float16
{
public:
	static const XE::float16 Nan;
	static const XE::float16 Epsilon;
	static const XE::float16 Infinity;

public:
	union
	{
		struct
		{
#if ENDIAN == ENDIAN_LITTLE
			XE::uint16 mantissa : 10;
			XE::uint16 exponent : 5;
			XE::uint16 sign : 1;
#else			   
			XE::uint16 sign : 1;
			XE::uint16 exponent : 5;
			XE::uint16 mantissa : 10;
#endif
		};

		XE::uint16 encode;
	};

public:
	float16();

	float16( XE::float32 val );
	
	float16( const XE::float16& val );

	~float16();

public:
	float16& operator=( XE::float16 val );
	
	float16& operator=( XE::float32 val );

public:
	explicit operator XE::float32() const;

public:
	bool operator<( XE::float16 val ) const;
	
	bool operator>( XE::float16 val ) const;
	
	bool operator<=( XE::float16 val ) const;
	
	bool operator>=( XE::float16 val ) const;
	
	bool operator==( XE::float16 val ) const;
	
	bool operator!=( XE::float16 val ) const;
	
	bool operator<( XE::float32 val ) const;

	bool operator>( XE::float32 val ) const;

	bool operator<=( XE::float32 val ) const;

	bool operator>=( XE::float32 val ) const;

	bool operator==( XE::float32 val ) const;

	bool operator!=( XE::float32 val ) const;

public:
	XE::float32 ToFloat32() const;
	
	void FormFloat32( XE::float32 val );
	
};
DECL_META_CLASS(XE_API, float16);

END_XE_NAMESPACE

bool operator<( XE::float32 val1, XE::float16 val2 );

bool operator>( XE::float32 val1, XE::float16 val2 );

bool operator<=( XE::float32 val1, XE::float16 val2 );

bool operator>=( XE::float32 val1, XE::float16 val2 );

bool operator==( XE::float32 val1, XE::float16 val2 );

bool operator!=( XE::float32 val1, XE::float16 val2 );

#endif // __FLOAT16_H__A3198368_5080_4B3C_9DD7_867156762D19
