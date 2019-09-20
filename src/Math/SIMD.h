/*!
 * \file   SIMD.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __SIMD_H__888145AB_7695_494A_8FD9_1083D764E431
#define __SIMD_H__888145AB_7695_494A_8FD9_1083D764E431

#include "Type.h"

#ifdef SIMD_TYPE

BEG_XE_NAMESPACE

class MATH_API SIMD
{
public:
#if SIMD_TYPE == SIMD_SSE
	using simd_t = __m128;
#else
	using simd_t = realx4_t;
#endif

public:
	static XE_INLINE XE::float32 X( simd_t a );

	static XE_INLINE XE::float32 Y( simd_t a );

	static XE_INLINE XE::float32 Z( simd_t a );

	static XE_INLINE XE::float32 W( simd_t a );

	static XE_INLINE void Stream( XE::float32 * ptr, simd_t a );

	static XE_INLINE simd_t Load( const XE::float32 * ptr );

	static XE_INLINE simd_t Load( XE::float32 x, XE::float32 y, XE::float32 z, XE::float32 w );

	static XE_INLINE simd_t Zero();

	static XE_INLINE simd_t Add( simd_t a, simd_t b );

	static XE_INLINE simd_t Sub( simd_t a, simd_t b );

	static XE_INLINE simd_t Mul( simd_t a, simd_t b );

	static XE_INLINE simd_t Div( simd_t a, simd_t b );

	static XE_INLINE simd_t Rcp( simd_t a );

	static XE_INLINE simd_t Sqrt( simd_t a );

	static XE_INLINE simd_t Rsqrt( simd_t a );

	static XE_INLINE simd_t Dot3( simd_t a, simd_t b );

	static XE_INLINE simd_t Dot( simd_t a, simd_t b );

	static XE_INLINE simd_t Cmpeq( simd_t a, simd_t b );

	static XE_INLINE simd_t Cmplt( simd_t a, simd_t b );

	static XE_INLINE simd_t Cmple( simd_t a, simd_t b );

	static XE_INLINE simd_t Cmpgt( simd_t a, simd_t b );

	static XE_INLINE simd_t Cmpge( simd_t a, simd_t b );

	static XE_INLINE simd_t Min( simd_t a, simd_t b );

	static XE_INLINE simd_t Max( simd_t a, simd_t b );

	static XE_INLINE simd_t And( simd_t a, simd_t b );

	static XE_INLINE simd_t AndNot( simd_t a, simd_t b );

	static XE_INLINE simd_t Or( simd_t a, simd_t b );

	static XE_INLINE simd_t Xor( simd_t a, simd_t b );

	static XE_INLINE simd_t Neg( simd_t a );

	static XE_INLINE simd_t Madd( simd_t a, simd_t b, simd_t c );

	static XE_INLINE simd_t Nmsub( simd_t a, simd_t b, simd_t c );

	static XE_INLINE simd_t Selb( simd_t mask, simd_t a, simd_t b );

	static XE_INLINE simd_t Abs( simd_t a );

	static XE_INLINE simd_t Clamp( simd_t a, simd_t min, simd_t max );

	static XE_INLINE simd_t Lerp( simd_t a, simd_t b, simd_t s );

	static XE_INLINE simd_t Cross3( simd_t a, simd_t b );

	static XE_INLINE simd_t Normalize3( simd_t a );
	
};

END_XE_NAMESPACE

#if SIMD_TYPE == SIMD_SSE
#include "SIMD_SSE.inc"
#else
#include "SIMD_NEON.inc"
#endif

#endif

#endif // __SIMD_H__888145AB_7695_494A_8FD9_1083D764E431
