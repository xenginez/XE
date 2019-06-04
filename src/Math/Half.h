/*!
 * \file   Half.h
 *
 * \author ZhengYuanQing
 * \date   2019/02/25
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __HALF_H__A3198368_5080_4B3C_9DD7_867156762D19
#define __HALF_H__A3198368_5080_4B3C_9DD7_867156762D19

#include "Type.h"

BEG_XE_NAMESPACE

class MATH_API Half
{
public:
	static const Half Nan;
	static const Half Zero;
	static const Half Epsilon;
	static const Half Infinity;

public:
	union
	{
		struct
		{
#if ENDIAN == ENDIAN_LITTLE
			uint16 mantissa : 10;
			uint16 exponent : 5;
			uint16 sign : 1;
#else			   
			uint16 sign : 1;
			uint16 exponent : 5;
			uint16 mantissa : 10;
#endif
		};

		uint16 encode;
	};

public:
	Half();

	Half( XE::float32 val );

	Half( uint16 val );

	Half( const Half& val );

	~Half();

public:
	Half& operator=( XE::float32 val );

	Half& operator=( const Half& val );

public:
	operator XE::float32() const;

public:
	bool operator<( XE::float32 val ) const;

	bool operator>( XE::float32 val ) const;

	bool operator<=( XE::float32 val ) const;

	bool operator>=( XE::float32 val ) const;

	bool operator==( XE::float32 val ) const;

	bool operator!=( XE::float32 val ) const;

	bool operator<( const Half& val ) const;

	bool operator>( const Half& val ) const;

	bool operator<=( const Half& val ) const;

	bool operator>=( const Half& val ) const;

	bool operator==( const Half& val ) const;

	bool operator!=( const Half& val ) const;

private:
	void Set( XE::float32 val );
};
DECL_META_CLASS( MATH_API, Half );

END_XE_NAMESPACE

bool operator<( XE::float32 val1, const XE::Half& val2 );

bool operator>( XE::float32 val1, const XE::Half& val2 );

bool operator<=( XE::float32 val1, const XE::Half& val2 );

bool operator>=( XE::float32 val1, const XE::Half& val2 );

bool operator==( XE::float32 val1, const XE::Half& val2 );

bool operator!=( XE::float32 val1, const XE::Half& val2 );

#endif // __HALF_H__A3198368_5080_4B3C_9DD7_867156762D19
