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

#include "Vec2.h"
#include "Mat4.h"

BEG_XE_NAMESPACE

class XE_API alignas( 16 ) Rect
{
public:
	static const Rect Zero;

public:
	XE::float32 x;
	XE::float32 y;
	XE::float32 width;
	XE::float32 height;

public:
	Rect();

	Rect( const Rect& val );

	Rect( const Vec2f & center, const Vec2f & size );

	Rect( XE::float32 x, XE::float32 y, XE::float32 w, XE::float32 h );

public:
	Rect& operator=( const Rect& val );

	bool operator ==( const Rect& val ) const;

	bool operator !=( const Rect& val ) const;

public:
	Vec2f GetMin() const;

	Vec2f GetMax() const;

	Vec2f GetSize() const;

	Vec2f GetCenter() const;

public:
	bool Contains( const Vec2f& val ) const;

	bool Contains( const Rect & val ) const;

public:
	bool Intersect( const Rect & val ) const;

	bool Intersect( const Vec2f & beg, const Vec2f & end )const;

public:
	void Clip( const Rect& val );

	void Encapsulate( const Rect& val );

public:
	void Transform( const Mat4f& val );

};
DECL_META_CLASS( XE_API, Rect );

END_XE_NAMESPACE

#endif // __RECT_H__CFAED4A1_7564_4C31_AC1F_E7BD88EE9157
