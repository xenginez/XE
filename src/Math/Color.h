/*!
 * \file   Color.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __COLOR_H__5581235E_91F0_4146_AC67_2A35AE35C660
#define __COLOR_H__5581235E_91F0_4146_AC67_2A35AE35C660

#include "Type.h"

BEG_XE_NAMESPACE

class MATH_API Color
{
public:
	static const Color White;
	static const Color Black;
	static const Color Red;
	static const Color DarkRed;
	static const Color Green;
	static const Color DarkGreen;
	static const Color Blue;
	static const Color DarkBlue;
	static const Color Cyan;
	static const Color DarkCyan;
	static const Color Magenta;
	static const Color DarkMagenta;
	static const Color Yellow;
	static const Color DarkYellow;
	static const Color Gray;
	static const Color DarkGray;
	static const Color LightGray;

public:
	union
	{
		struct
		{
			float r, g, b, a;
		};

		float d[4];
	};

public:
	Color();

	Color( uint32 val );

	Color( const Color& val );

	Color( float r, float g, float b, float a = 1.0f );

	~Color();

public:
	Color& operator=( const Color& val );

	Color& operator *=( float val );

	Color& operator *=( const Color& val );

	Color& operator +=( const Color& val );

	Color& operator -=( const Color& val );

	Color operator *( float val ) const;

	Color operator *( const Color& val ) const;

	Color operator +( const Color& val ) const;

	Color operator -( const Color& val ) const;

	bool operator ==( const Color& val ) const;

	bool operator !=( const Color& val ) const;

public:
	friend Color operator *( float a, const Color& b );

public:
	uint32 GetHex() const;

	void SetHex( uint32 val );

	uint8 GetR() const;

	void SetR( uint8 val );

	uint8 GetG() const;

	void SetG( uint8 val );

	uint8 GetB() const;

	void SetB( uint8 val );

	uint8 GetA() const;

	void SetA( uint8 val );

public:
	static Color Lerp( const Color& val1, const Color& val2, float val );
};
DECL_META_CLASS( MATH_API, Color );

END_XE_NAMESAPCE

#endif // __COLOR_H__5581235E_91F0_4146_AC67_2A35AE35C660
