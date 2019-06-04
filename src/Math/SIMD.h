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

#if SIMD_TYPE == SIMD_SSE
#include <xmmintrin.h>
#elif SIMD_TYPE == SIMD_NEON
#include <xmmintrin.h>
#endif

BEG_XE_NAMESPACE

class MATH_API SIMD
{
public:
#if SIMD_TYPE == SIMD_SSE
	using simd_t = __m128;
#else
	using simd_t = XE::float3232x4_t;
#endif

public:
	static inline XE::float32 X( simd_t a );

	static inline XE::float32 Y( simd_t a );

	static inline XE::float32 Z( simd_t a );

	static inline XE::float32 W( simd_t a );

	static inline void Stream( XE::float32 * ptr, simd_t a );

	static inline simd_t Load( const XE::float32 * ptr );

	static inline simd_t Load( XE::float32 x, XE::float32 y, XE::float32 z, XE::float32 w );

	static inline simd_t Zero();

	static inline simd_t Add( simd_t a, simd_t b );

	static inline simd_t Sub( simd_t a, simd_t b );

	static inline simd_t Mul( simd_t a, simd_t b );

	static inline simd_t Div( simd_t a, simd_t b );

	static inline simd_t Rcp( simd_t a );

	static inline simd_t Sqrt( simd_t a );

	static inline simd_t Rsqrt( simd_t a );

	static inline simd_t Dot3( simd_t a, simd_t b );

	static inline simd_t Dot( simd_t a, simd_t b );

	static inline simd_t Cmpeq( simd_t a, simd_t b );

	static inline simd_t Cmplt( simd_t a, simd_t b );

	static inline simd_t Cmple( simd_t a, simd_t b );

	static inline simd_t Cmpgt( simd_t a, simd_t b );

	static inline simd_t Cmpge( simd_t a, simd_t b );

	static inline simd_t Min( simd_t a, simd_t b );

	static inline simd_t Max( simd_t a, simd_t b );

	static inline simd_t And( simd_t a, simd_t b );

	static inline simd_t AndNot( simd_t a, simd_t b );

	static inline simd_t Or( simd_t a, simd_t b );

	static inline simd_t Xor( simd_t a, simd_t b );

	static inline simd_t Neg( simd_t a );

	static inline simd_t Madd( simd_t a, simd_t b, simd_t c );

	static inline simd_t Nmsub( simd_t a, simd_t b, simd_t c );

	static inline simd_t Selb( simd_t mask, simd_t a, simd_t b );

	static inline simd_t Abs( simd_t a );

	static inline simd_t Clamp( simd_t a, simd_t min, simd_t max );

	static inline simd_t Lerp( simd_t a, simd_t b, simd_t s );

	static inline simd_t Cross3( simd_t a, simd_t b );

	static inline simd_t Normalize3( simd_t a );
	
};

END_XE_NAMESPACE

#if SIMD_TYPE == SIMD_SSE
#include "SIMD_SSE.inc"
#else
#include "SIMD_NEON.inc"
#endif

#endif

#endif // __SIMD_H__888145AB_7695_494A_8FD9_1083D764E431
