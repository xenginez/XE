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

class XE_API alignas( 16 ) Color
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
			XE::uint8 r, g, b, a;
		};
		
		XE::uint8 d[4];
		XE::uint32 hex;
	};

public:
	Color();

	Color( XE::uint32 val );

	Color( const Color& val );
	
	Color( const FColor& val );

	Color( XE::uint8 r, XE::uint8 g, XE::uint8 b, XE::uint8 a = 1 );

	~Color();

public:
	Color& operator=( const Color& val );

	Color& operator *=( XE::uint8 val );

	Color& operator *=( const Color& val );

	Color& operator +=( const Color& val );

	Color& operator -=( const Color& val );

	XE::uint8 & operator[]( XE::uint64 val );

	XE::uint8 operator[]( XE::uint64 val ) const;

	Color operator *( XE::uint8 val ) const;

	Color operator *( const Color& val ) const;

	Color operator +( const Color& val ) const;

	Color operator -( const Color& val ) const;

	bool operator ==( const Color& val ) const;

	bool operator !=( const Color& val ) const;

public:
	friend Color operator *( XE::uint8 a, const Color& b );

public:
	XE::uint32 GetHex() const;

	void SetHex( XE::uint32 val );

public:
	static Color Lerp( const Color& val1, const Color& val2, XE::uint8 val );
};
DECL_META_CLASS( XE_API, Color );

class XE_API FColor
{
public:
	static const FColor White;
	static const FColor Black;
	static const FColor Red;
	static const FColor DarkRed;
	static const FColor Green;
	static const FColor DarkGreen;
	static const FColor Blue;
	static const FColor DarkBlue;
	static const FColor Cyan;
	static const FColor DarkCyan;
	static const FColor Magenta;
	static const FColor DarkMagenta;
	static const FColor Yellow;
	static const FColor DarkYellow;
	static const FColor Gray;
	static const FColor DarkGray;
	static const FColor LightGray;

public:
	union
	{
		struct
		{
			XE::float32 r, g, b, a;
		};
		
		XE::float32 d[4];
	};

public:
	FColor();
	
	FColor( XE::uint32 val );
	
	FColor( const Color& val );
	
	FColor( const FColor& val );
	
	FColor( XE::float32 r, XE::float32 g, XE::float32 b, XE::float32 a = 1.0f );
	
	~FColor();

public:
	FColor& operator=( const FColor& val );
	
	FColor& operator *=( XE::float32 val );
	
	FColor& operator *=( const FColor& val );
	
	FColor& operator +=( const FColor& val );
	
	FColor& operator -=( const FColor& val );
	
	FColor operator *( XE::float32 val ) const;
	
	FColor operator *( const FColor& val ) const;
	
	FColor operator +( const FColor& val ) const;
	
	FColor operator -( const FColor& val ) const;
	
	bool operator ==( const FColor& val ) const;
	
	bool operator !=( const FColor& val ) const;

public:
	friend FColor operator *( XE::float32 a, const FColor& b );

public:
	XE::uint32 GetHex() const;
	
	void SetHex( XE::uint32 val );

public:
	static FColor Lerp( const FColor& val1, const FColor& val2, XE::float32 val );
};
DECL_META_CLASS( XE_API, FColor );

END_XE_NAMESPACE

#endif // __COLOR_H__5581235E_91F0_4146_AC67_2A35AE35C660
