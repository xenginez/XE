/*!
 * \file   Rect.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __RECT_H__CFAED4A1_7564_4C31_AC1F_E7BD88EE9157
#define __RECT_H__CFAED4A1_7564_4C31_AC1F_E7BD88EE9157

#include "Type.h"

BEG_XE_NAMESPACE

class MATH_API Rect
{
public:
	static const Rect Zero;

public:
	float x;
	float y;
	float width;
	float height;

public:
	Rect();

	Rect( const Rect& val );

	Rect( const Vec2& min, const Vec2& max );

	Rect( float x, float y, float w, float h );

public:
	Rect& operator=( const Rect& val );

	bool operator ==( const Rect& val ) const;

	bool operator !=( const Rect& val ) const;

public:
	bool contains( const Vec2& val ) const;

	bool overlaps( const Rect& val ) const;

public:
	void clip( const Rect& val );

	void encapsulate( const Rect& val );

public:
	void Transform( const Mat4& val );

};
DECL_META_CLASS( MATH_API, Rect );

END_XE_NAMESAPCE

#endif // __RECT_H__CFAED4A1_7564_4C31_AC1F_E7BD88EE9157
