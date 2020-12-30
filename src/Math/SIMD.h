/*!
 * \file	SIMD.h
 *
 * \author	ZhengYuanQing
 * \date	2020/12/30
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef SIMD_H__C98956B9_05A0_4CD7_82F2_2EB0D46FB152
#define SIMD_H__C98956B9_05A0_4CD7_82F2_2EB0D46FB152

#include "Type.h"

#if defined(__AVX2__)
#include <immintrin.h>
#define XE_SIMD_AVX2
#define XE_SIMD_AVX
#endif

#if defined(__FMA__)
#include <immintrin.h>
#define XE_SIMD_FMA
#endif

#if defined(__AVX__)
#include <immintrin.h>
#define XE_SIMD_AVX
#define XE_SIMD_SSE4_2
#endif

#if defined(__SSE4_2__)
#include <nmmintrin.h>
#define XE_SIMD_SSE4_2
#define XE_SIMD_SSE4_1
#endif

#if defined(__SSE4_1__)
#include <smmintrin.h>
#define XE_SIMD_SSE4_1
#define XE_SIMD_SSSE3
#endif

#if defined(__SSSE3__)
#include <tmmintrin.h>
#define XE_SIMD_SSSE3
#define XE_SIMD_SSE3
#endif

#if defined(__SSE3__)
#include <pmmintrin.h>
#define XE_SIMD_SSE3
#define XE_SIMD_SSE2
#endif

#if defined(__SSE2__) || defined(_M_AMD64) || defined(_M_X64) || (_M_IX86_FP >= 2)
#include <emmintrin.h>
#define XE_SIMD_SSE2
#define XE_SIMD_SSE
#endif

#ifndef XE_SIMD_SSE
#include <sse2neon/sse2neon.h>
#define XE_SIMD_SSE2
#define XE_SIMD_SSE
#endif // XE_SIMD_SSE



#ifdef XE_SIMD_AVX
#define XE_SHUFFLE_PS1(_v, _m) _mm_permute_ps(_v, _m)
#else
#define XE_SHUFFLE_PS1(_v, _m) _mm_shuffle_ps(_v, _v, _m)
#endif

#define XE_SSE_SPLAT_F(_v, _i) XE_SHUFFLE_PS1(_v, _MM_SHUFFLE(_i, _i, _i, _i))

#define XE_SSE_SPLAT_I(_v, _i) _mm_shuffle_epi32(_v, _MM_SHUFFLE(_i, _i, _i, _i))

#define XE_SSE_HADD2_F(_v) _mm_add_ss(_v, XE_SSE_SPLAT_F(_v, 1))

#define XE_SSE_HADD3_F(_v) _mm_add_ss(_mm_add_ss(_v, XE_SSE_SPLAT_F(_v, 2)), XE_SSE_SPLAT_F(_v, 1))

#define XE_SSE_HADD4_F(_v, _r) { const __m128 haddxyzw = _mm_add_ps( _v, _mm_movehl_ps( _v, _v ) ); _r = _mm_add_ss( haddxyzw, XE_SSE_SPLAT_F( haddxyzw, 1 ) ); }

#define XE_SSE_DOT2_F(_a, _b, _r) { const __m128 ab = _mm_mul_ps(_a, _b); _r = _mm_add_ss(ab, XE_SSE_SPLAT_F(ab, 1)); }

#ifdef XE_SIMD_SSE4_1
#define XE_SSE_DOT3_F(_a, _b, _r) { _r = _mm_dp_ps(_a, _b, 0x7f); }

#define XE_SSE_DOT4_F(_a, _b, _r) { _r = _mm_dp_ps(_a, _b, 0xff); }
#else
#define XE_SSE_DOT3_F(_a, _b, _r) { const __m128 ab = _mm_mul_ps(_a, _b); _r = XE_SSE_HADD3_F(ab); }

#define XE_SSE_DOT4_F(_a, _b, _r) { const __m128 ab = _mm_mul_ps(_a, _b); XE_SSE_HADD4_F(ab, _r); }
#endif

#ifdef XE_SIMD_FMA
#define XE_MADD(_a, _b, _c) _mm_fmadd_ps(_a, _b, _c)
#define XE_MSUB(_a, _b, _c) _mm_fmsub_ps(_a, _b, _c)
#define XE_NMADD(_a, _b, _c) _mm_fnmadd_ps(_a, _b, _c)
#define XE_NMSUB(_a, _b, _c) _mm_fnmsub_ps(_a, _b, _c)
#define XE_MADDX(_a, _b, _c) _mm_fmadd_ss(_a, _b, _c)
#define XE_MSUBX(_a, _b, _c) _mm_fmsub_ss(_a, _b, _c)
#define XE_NMADDX(_a, _b, _c) _mm_fnmadd_ss(_a, _b, _c)
#define XE_NMSUBX(_a, _b, _c) _mm_fnmsub_ss(_a, _b, _c)
#else
#define XE_MADD(_a, _b, _c) _mm_add_ps(_mm_mul_ps(_a, _b), _c)
#define XE_MSUB(_a, _b, _c) _mm_sub_ps(_mm_mul_ps(_a, _b), _c)
#define XE_NMADD(_a, _b, _c) _mm_sub_ps(_c, _mm_mul_ps(_a, _b))
#define XE_NMSUB(_a, _b, _c) (-Simd::simd4f(_mm_add_ps(_mm_mul_ps(_a, _b), _c)))
#define XE_MADDX(_a, _b, _c) _mm_add_ss(_mm_mul_ss(_a, _b), _c)
#define XE_MSUBX(_a, _b, _c) _mm_sub_ss(_mm_mul_ss(_a, _b), _c)
#define XE_NMADDX(_a, _b, _c) _mm_sub_ss(_c, _mm_mul_ss(_a, _b))
#define XE_NMSUBX(_a, _b, _c) (-Simd::simd4f(_mm_add_ss(_mm_mul_ss(_a, _b), _c)))
#endif

#ifdef XE_SIMD_SSE4_1
#define XE_SSE_SELECT_F(_b, _true, _false) _mm_blendv_ps(_false, _true, _mm_castsi128_ps(_b))
#define XE_SSE_SELECT_I(_b, _true, _false) _mm_blendv_epi8(_false, _true, _b)
#else
#define XE_SSE_SELECT_F(_b, _true, _false) _mm_or_ps(_mm_and_ps(_true, _mm_castsi128_ps(_b)), _mm_andnot_ps(_mm_castsi128_ps(_b), _false))
#define XE_SSE_SELECT_I(_b, _true, _false) _mm_or_si128(_mm_and_si128(_true, _b), _mm_andnot_si128(_b, _false))
#endif

BEG_XE_NAMESPACE

namespace Simd
{
	class simd4i;
	class simd4f;
	class simd4x4;

	class alignas( 16 ) simd4i
	{
	public:
		__m128i v;

	public:
		simd4i() = default;

		simd4i( const __m128i val )
			:v( val )
		{
		}

	public:
		operator __m128i & ( )
		{
			return v;
		}

		operator const __m128i & ( ) const
		{
			return v;
		}

	public:
		static XE_INLINE simd4i Zero();

		static XE_INLINE simd4i One();

		static XE_INLINE simd4i XAxis();

		static XE_INLINE simd4i YAxis();

		static XE_INLINE simd4i ZAxis();

		static XE_INLINE simd4i WAxis();

		static XE_INLINE simd4i AllTrue();

		static XE_INLINE simd4i AllFlase();

		static XE_INLINE simd4i MaskSign();

		static XE_INLINE simd4i MaskSignXYZ();

		static XE_INLINE simd4i MaskSignW();

		static XE_INLINE simd4i MaskNotSign();

		static XE_INLINE simd4i MaskFFFF();

		static XE_INLINE simd4i Mask0000();

		static XE_INLINE simd4i MaskFFF0();

		static XE_INLINE simd4i MaskF000();

		static XE_INLINE simd4i Mask0F00();

		static XE_INLINE simd4i Mask00F0();

		static XE_INLINE simd4i Mask000F();

		static XE_INLINE simd4i Load( XE::int32 _x, XE::int32 _y, XE::int32 _z, XE::int32 _w );

		static XE_INLINE simd4i LoadX( XE::int32 _x );

		static XE_INLINE simd4i Load1( XE::int32 _x );

		static XE_INLINE simd4i Load( bool _x, bool _y, bool _z, bool _w );

		static XE_INLINE simd4i LoadX( bool _x );

		static XE_INLINE simd4i Load1( bool _x );

		static XE_INLINE simd4i LoadPtr( const XE::int32 * _i );

		static XE_INLINE simd4i LoadXPtr( const XE::int32 * _i );

		static XE_INLINE simd4i Load1Ptr( const XE::int32 * _i );

		static XE_INLINE simd4i Load2Ptr( const XE::int32 * _i );

		static XE_INLINE simd4i Load3Ptr( const XE::int32 * _i );

		static XE_INLINE simd4i LoadPtrU( const XE::int32 * _i );

		static XE_INLINE simd4i LoadXPtrU( const XE::int32 * _i );

		static XE_INLINE simd4i Load1PtrU( const XE::int32 * _i );

		static XE_INLINE simd4i Load2PtrU( const XE::int32 * _i );

		static XE_INLINE simd4i Load3PtrU( const XE::int32 * _i );

		static XE_INLINE simd4i FromFloatRound( const simd4f & _f );

		static XE_INLINE simd4i FromFloatTrunc( const simd4f & _f );

		static XE_INLINE XE::int32 GetX( const simd4i & _v );

		static XE_INLINE XE::int32 GetY( const simd4i & _v );

		static XE_INLINE XE::int32 GetZ( const simd4i & _v );

		static XE_INLINE XE::int32 GetW( const simd4i & _v );

		static XE_INLINE simd4i SetX( const simd4i & _v, const simd4i & _i );

		static XE_INLINE simd4i SetY( const simd4i & _v, const simd4i & _i );

		static XE_INLINE simd4i SetZ( const simd4i & _v, const simd4i & _i );

		static XE_INLINE simd4i SetW( const simd4i & _v, const simd4i & _i );

		static XE_INLINE simd4i SetI( const simd4i & _v, const simd4i & _i, XE::int32 _ith );

		static XE_INLINE void StorePtr( const simd4i & _v, XE::int32 * _i );

		static XE_INLINE void Store1Ptr( const simd4i & _v, XE::int32 * _i );

		static XE_INLINE void Store2Ptr( const simd4i & _v, XE::int32 * _i );

		static XE_INLINE void Store3Ptr( const simd4i & _v, XE::int32 * _i );

		static XE_INLINE void StorePtrU( const simd4i & _v, XE::int32 * _i );

		static XE_INLINE void Store1PtrU( const simd4i & _v, XE::int32 * _i );

		static XE_INLINE void Store2PtrU( const simd4i & _v, XE::int32 * _i );

		static XE_INLINE void Store3PtrU( const simd4i & _v, XE::int32 * _i );

		static XE_INLINE simd4i SplatX( const simd4i & _a );

		static XE_INLINE simd4i SplatY( const simd4i & _a );

		static XE_INLINE simd4i SplatZ( const simd4i & _a );

		static XE_INLINE simd4i SplatW( const simd4i & _a );

		template <size_t _X, size_t _Y, size_t _Z, size_t _W> static XE_INLINE simd4i Swizzle( const simd4i & _v );

		template <> static XE_INLINE simd4i Swizzle<0, 1, 2, 3>( const simd4i & _v );

		static XE_INLINE XE::int32 MoveMask( const simd4i & _v );

		static XE_INLINE bool AreAllTrue( const simd4i & _v );

		static XE_INLINE bool AreAllTrue3( const simd4i & _v );

		static XE_INLINE bool AreAllTrue2( const simd4i & _v );

		static XE_INLINE bool AreAllTrue1( const simd4i & _v );

		static XE_INLINE bool AreAllFalse( const simd4i & _v );

		static XE_INLINE bool AreAllFalse3( const simd4i & _v );

		static XE_INLINE bool AreAllFalse2( const simd4i & _v );

		static XE_INLINE bool AreAllFalse1( const simd4i & _v );

		static XE_INLINE simd4i HAdd2( const simd4i & _v );

		static XE_INLINE simd4i HAdd3( const simd4i & _v );

		static XE_INLINE simd4i HAdd4( const simd4i & _v );

		static XE_INLINE simd4i Abs( const simd4i & _v );

		static XE_INLINE simd4i Sign( const simd4i & _v );

		static XE_INLINE simd4i Min( const simd4i & _a, const simd4i & _b );

		static XE_INLINE simd4i Max( const simd4i & _a, const simd4i & _b );

		static XE_INLINE simd4i Min0( const simd4i & _v );

		static XE_INLINE simd4i Max0( const simd4i & _v );

		static XE_INLINE simd4i Clamp( const simd4i & _a, const simd4i & _v, const simd4i & _b );

		static XE_INLINE simd4i Select( const simd4i & _b, const simd4i & _true, const simd4i & _false );

		static XE_INLINE simd4i And( const simd4i & _a, const simd4i & _b );

		static XE_INLINE simd4i AndNot( const simd4i & _a, const simd4i & _b );

		static XE_INLINE simd4i Or( const simd4i & _a, const simd4i & _b );

		static XE_INLINE simd4i Xor( const simd4i & _a, const simd4i & _b );

		static XE_INLINE simd4i Not( const simd4i & _v );

		static XE_INLINE simd4i ShiftL( const simd4i & _v, XE::int32 _bits );

		static XE_INLINE simd4i ShiftR( const simd4i & _v, XE::int32 _bits );

		static XE_INLINE simd4i ShiftRu( const simd4i & _v, XE::int32 _bits );

		static XE_INLINE simd4i CmpEq( const simd4i & _a, const simd4i & _b );

		static XE_INLINE simd4i CmpNe( const simd4i & _a, const simd4i & _b );

		static XE_INLINE simd4i CmpLt( const simd4i & _a, const simd4i & _b );

		static XE_INLINE simd4i CmpLe( const simd4i & _a, const simd4i & _b );

		static XE_INLINE simd4i CmpGt( const simd4i & _a, const simd4i & _b );

		static XE_INLINE simd4i CmpGe( const simd4i & _a, const simd4i & _b );

	};

	class alignas( 16 ) simd4f
	{
	public:
		__m128 v;

	public:
		simd4f() = default;

		simd4f( const __m128 val )
			:v( val )
		{
		}

	public:
		operator __m128 & ( )
		{
			return v;
		}

		operator const __m128 & ( ) const
		{
			return v;
		}

	public:
		friend Simd::simd4f operator-( const Simd::simd4f _v );

		friend Simd::simd4f operator+( const Simd::simd4f _a, const Simd::simd4f _b );

		friend Simd::simd4f operator-( const Simd::simd4f _a, const Simd::simd4f _b );

		friend Simd::simd4f operator*( const Simd::simd4f _a, const Simd::simd4f _b );

		friend Simd::simd4f operator/( const Simd::simd4f _a, const Simd::simd4f _b );

	public:
		static XE_INLINE simd4f Zero();

		static XE_INLINE simd4f One();

		static XE_INLINE simd4f XAxis();

		static XE_INLINE simd4f YAxis();

		static XE_INLINE simd4f ZAxis();

		static XE_INLINE simd4f WAxis();

		static XE_INLINE simd4f Load( XE::float32 _x, XE::float32 _y, XE::float32 _z, XE::float32 _w );

		static XE_INLINE simd4f LoadX( XE::float32 _x );

		static XE_INLINE simd4f Load1( XE::float32 _x );

		static XE_INLINE simd4f LoadPtr( const XE::float32 * _f );

		static XE_INLINE simd4f LoadPtrU( const XE::float32 * _f );

		static XE_INLINE simd4f LoadXPtrU( const XE::float32 * _f );

		static XE_INLINE simd4f Load1PtrU( const XE::float32 * _f );

		static XE_INLINE simd4f Load2PtrU( const XE::float32 * _f );

		static XE_INLINE simd4f Load3PtrU( const XE::float32 * _f );

		static XE_INLINE simd4f FromInt( const simd4i & _i );

		static XE_INLINE XE::float32 GetX( const simd4f & _v );

		static XE_INLINE XE::float32 GetY( const simd4f & _v );

		static XE_INLINE XE::float32 GetZ( const simd4f & _v );

		static XE_INLINE XE::float32 GetW( const simd4f & _v );

		static XE_INLINE simd4f SetX( const simd4f & _v, const simd4f & _f );

		static XE_INLINE simd4f SetY( const simd4f & _v, const simd4f & _f );

		static XE_INLINE simd4f SetZ( const simd4f & _v, const simd4f & _f );

		static XE_INLINE simd4f SetW( const simd4f & _v, const simd4f & _f );

		static XE_INLINE simd4f SetI( const simd4f & _v, const simd4f & _f, XE::int32 _ith );

		static XE_INLINE void StorePtr( const simd4f & _v, XE::float32 * _f );

		static XE_INLINE void Store1Ptr( const simd4f & _v, XE::float32 * _f );

		static XE_INLINE void Store2Ptr( const simd4f & _v, XE::float32 * _f );

		static XE_INLINE void Store3Ptr( const simd4f & _v, XE::float32 * _f );

		static XE_INLINE void StorePtrU( const simd4f & _v, XE::float32 * _f );

		static XE_INLINE void Store1PtrU( const simd4f & _v, XE::float32 * _f );

		static XE_INLINE void Store2PtrU( const simd4f & _v, XE::float32 * _f );

		static XE_INLINE void Store3PtrU( const simd4f & _v, XE::float32 * _f );

		static XE_INLINE simd4f SplatX( const simd4f & _v );

		static XE_INLINE simd4f SplatY( const simd4f & _v );

		static XE_INLINE simd4f SplatZ( const simd4f & _v );

		static XE_INLINE simd4f SplatW( const simd4f & _v );

		template <size_t _X, size_t _Y, size_t _Z, size_t _W> static XE_INLINE simd4f Swizzle( const simd4f & _v );

		template <> static XE_INLINE simd4f Swizzle<0, 1, 2, 3>( const simd4f & _v );

		template <> static XE_INLINE simd4f Swizzle<0, 1, 0, 1>( const simd4f & _v );

		template <> static XE_INLINE simd4f Swizzle<2, 3, 2, 3>( const simd4f & _v );

		template <> static XE_INLINE simd4f Swizzle<0, 0, 1, 1>( const simd4f & _v );

		template <> static XE_INLINE simd4f Swizzle<2, 2, 3, 3>( const simd4f & _v );

		static XE_INLINE void Transpose4x1( const simd4f _in[4], simd4f _out[1] );

		static XE_INLINE void Transpose1x4( const simd4f _in[1], simd4f _out[4] );

		static XE_INLINE void Transpose4x2( const simd4f _in[4], simd4f _out[2] );

		static XE_INLINE void Transpose2x4( const simd4f _in[2], simd4f _out[4] );

		static XE_INLINE void Transpose4x3( const simd4f _in[4], simd4f _out[3] );

		static XE_INLINE void Transpose3x4( const simd4f _in[3], simd4f _out[4] );

		static XE_INLINE void Transpose4x4( const simd4f _in[4], simd4f _out[4] );

		static XE_INLINE void Transpose16x16( const simd4f _in[16], simd4f _out[16] );

		static XE_INLINE simd4f MAdd( const simd4f & _a, const simd4f & _b, const simd4f & _c );

		static XE_INLINE simd4f MSub( const simd4f & _a, const simd4f & _b, const simd4f & _c );

		static XE_INLINE simd4f NMAdd( const simd4f & _a, const simd4f & _b, const simd4f & _c );

		static XE_INLINE simd4f NMSub( const simd4f & _a, const simd4f & _b, const simd4f & _c );

		static XE_INLINE simd4f DivX( const simd4f & _a, const simd4f & _b );

		static XE_INLINE simd4f HAdd2( const simd4f & _v );

		static XE_INLINE simd4f HAdd3( const simd4f & _v );

		static XE_INLINE simd4f HAdd4( const simd4f & _v );

		static XE_INLINE simd4f Dot2( const simd4f & _a, const simd4f & _b );

		static XE_INLINE simd4f Dot3( const simd4f & _a, const simd4f & _b );

		static XE_INLINE simd4f Dot4( const simd4f & _a, const simd4f & _b );

		static XE_INLINE simd4f Cross3( const simd4f & _a, const simd4f & _b );

		static XE_INLINE simd4f RcpEst( const simd4f & _v );

		static XE_INLINE simd4f RcpEstNR( const simd4f & _v );

		static XE_INLINE simd4f RcpEstX( const simd4f & _v );

		static XE_INLINE simd4f RcpEstXNR( const simd4f & _v );

		static XE_INLINE simd4f Sqrt( const simd4f & _v );

		static XE_INLINE simd4f SqrtX( const simd4f & _v );

		static XE_INLINE simd4f RSqrtEst( const simd4f & _v );

		static XE_INLINE simd4f RSqrtEstNR( const simd4f & _v );

		static XE_INLINE simd4f RSqrtEstX( const simd4f & _v );

		static XE_INLINE simd4f RSqrtEstXNR( const simd4f & _v );

		static XE_INLINE simd4f Abs( const simd4f & _v );

		static XE_INLINE simd4i Sign( const simd4f & _v );

		static XE_INLINE simd4f Length2( const simd4f & _v );

		static XE_INLINE simd4f Length3( const simd4f & _v );

		static XE_INLINE simd4f Length4( const simd4f & _v );

		static XE_INLINE simd4f Length2Sqr( const simd4f & _v );

		static XE_INLINE simd4f Length3Sqr( const simd4f & _v );

		static XE_INLINE simd4f Length4Sqr( const simd4f & _v );

		static XE_INLINE simd4f Normalize2( const simd4f & _v );

		static XE_INLINE simd4f Normalize3( const simd4f & _v );

		static XE_INLINE simd4f Normalize4( const simd4f & _v );

		static XE_INLINE simd4f NormalizeEst2( const simd4f & _v );

		static XE_INLINE simd4f NormalizeEst3( const simd4f & _v );

		static XE_INLINE simd4f NormalizeEst4( const simd4f & _v );

		static XE_INLINE simd4i IsNormalized2( const simd4f & _v );

		static XE_INLINE simd4i IsNormalized3( const simd4f & _v );

		static XE_INLINE simd4i IsNormalized4( const simd4f & _v );

		static XE_INLINE simd4i IsNormalizedEst2( const simd4f & _v );

		static XE_INLINE simd4i IsNormalizedEst3( const simd4f & _v );

		static XE_INLINE simd4i IsNormalizedEst4( const simd4f & _v );

		static XE_INLINE simd4f NormalizeSafe2( const simd4f & _v, const simd4f & _safe );

		static XE_INLINE simd4f NormalizeSafe3( const simd4f & _v, const simd4f & _safe );

		static XE_INLINE simd4f NormalizeSafe4( const simd4f & _v, const simd4f & _safe );

		static XE_INLINE simd4f NormalizeSafeEst2( const simd4f & _v, const simd4f & _safe );

		static XE_INLINE simd4f NormalizeSafeEst3( const simd4f & _v, const simd4f & _safe );

		static XE_INLINE simd4f NormalizeSafeEst4( const simd4f & _v, const simd4f & _safe );

		static XE_INLINE simd4f Lerp( const simd4f & _a, const simd4f & _b, const simd4f & _alpha );

		static XE_INLINE simd4f Min( const simd4f & _a, const simd4f & _b );

		static XE_INLINE simd4f Max( const simd4f & _a, const simd4f & _b );

		static XE_INLINE simd4f Min0( const simd4f & _v );

		static XE_INLINE simd4f Max0( const simd4f & _v );

		static XE_INLINE simd4f Clamp( const simd4f & _a, const simd4f & _v, const simd4f & _b );

		static XE_INLINE simd4f Select( const simd4i & _b, const simd4f & _true, const simd4f & _false );

		static XE_INLINE simd4i CmpEq( const simd4f & _a, const simd4f & _b );

		static XE_INLINE simd4i CmpNe( const simd4f & _a, const simd4f & _b );

		static XE_INLINE simd4i CmpLt( const simd4f & _a, const simd4f & _b );

		static XE_INLINE simd4i CmpLe( const simd4f & _a, const simd4f & _b );

		static XE_INLINE simd4i CmpGt( const simd4f & _a, const simd4f & _b );

		static XE_INLINE simd4i CmpGe( const simd4f & _a, const simd4f & _b );

		static XE_INLINE simd4f And( const simd4f & _a, const simd4f & _b );

		static XE_INLINE simd4f Or( const simd4f & _a, const simd4f & _b );

		static XE_INLINE simd4f Xor( const simd4f & _a, const simd4f & _b );

		static XE_INLINE simd4f And( const simd4f & _a, const simd4i & _b );

		static XE_INLINE simd4f AndNot( const simd4f & _a, const simd4i & _b );

		static XE_INLINE simd4f Or( const simd4f & _a, const simd4i & _b );

		static XE_INLINE simd4f Xor( const simd4f & _a, const simd4i & _b );

		static XE_INLINE simd4f Cos( const simd4f & _v );

		static XE_INLINE simd4f CosX( const simd4f & _v );

		static XE_INLINE simd4f ACos( const simd4f & _v );

		static XE_INLINE simd4f ACosX( const simd4f & _v );

		static XE_INLINE simd4f Sin( const simd4f & _v );

		static XE_INLINE simd4f SinX( const simd4f & _v );

		static XE_INLINE simd4f ASin( const simd4f & _v );

		static XE_INLINE simd4f ASinX( const simd4f & _v );

		static XE_INLINE simd4f Tan( const simd4f & _v );

		static XE_INLINE simd4f TanX( const simd4f & _v );

		static XE_INLINE simd4f ATan( const simd4f & _v );

		static XE_INLINE simd4f ATanX( const simd4f & _v );

	};

	class alignas( 16 ) simd4x4
	{
	public:
		simd4f cols[4];

	public:
		friend Simd::simd4f operator*( const Simd::simd4x4 & _m, const Simd::simd4f _v );

		friend Simd::simd4x4 operator*( const Simd::simd4x4 & _a, const Simd::simd4x4 & _b );

		friend Simd::simd4x4 operator+( const Simd::simd4x4 & _a, const Simd::simd4x4 & _b );

		friend Simd::simd4x4 operator-( const Simd::simd4x4 & _a, const Simd::simd4x4 & _b );

	public:
		static XE_INLINE simd4x4 identity();

		static XE_INLINE simd4x4 Transpose( const simd4x4 & _m );

		static XE_INLINE simd4x4 Invert( const simd4x4 & _m, simd4i * _invertible );

		static XE_INLINE simd4x4 Translation( const simd4f & _v );

		static XE_INLINE simd4x4 Scaling( const simd4f & _v );

		static XE_INLINE simd4x4 Translate( const simd4x4 & _m, const simd4f & _v );

		static XE_INLINE simd4x4 Scale( const simd4x4 & _m, const simd4f & _v );

		static XE_INLINE simd4x4 ColumnMultiply( const simd4x4 & _m, const simd4f & _v );

		static XE_INLINE simd4i IsNormalized( const simd4x4 & _m );

		static XE_INLINE simd4i IsNormalizedEst( const simd4x4 & _m );

		static XE_INLINE simd4i IsOrthogonal( const simd4x4 & _m );

		static XE_INLINE simd4f ToQuaternion( const simd4x4 & _m );

		static XE_INLINE bool ToAffine( const simd4x4 & _m, simd4f * _translation, simd4f * _quaternion, simd4f * _scale );

		static XE_INLINE simd4x4 FromEuler( const simd4f & _v );

		static XE_INLINE simd4x4 FromAxisAngle( const simd4f & _axis, const simd4f & _angle );

		static XE_INLINE simd4x4 FromQuaternion( const simd4f & _quaternion );

		static XE_INLINE simd4x4 FromAffine( const simd4f & _translation, const simd4f & _quaternion, const simd4f & _scale );

		static XE_INLINE simd4f TransformPoint( const simd4x4 & _m, const simd4f & _v );

		static XE_INLINE simd4f TransformVector( const simd4x4 & _m, const simd4f & _v );

	};


	XE_INLINE simd4i simd4i::Zero()
	{
		return _mm_setzero_si128();
	}

	XE_INLINE simd4i simd4i::One()
	{
		const __m128i zero = _mm_setzero_si128();
		return _mm_sub_epi32( zero, _mm_cmpeq_epi32( zero, zero ) );
	}

	XE_INLINE simd4i simd4i::XAxis()
	{
		const __m128i zero = _mm_setzero_si128();
		return _mm_srli_si128( _mm_sub_epi32( zero, _mm_cmpeq_epi32( zero, zero ) ), 12 );
	}

	XE_INLINE simd4i simd4i::YAxis()
	{
		const __m128i zero = _mm_setzero_si128();
		return _mm_slli_si128( _mm_srli_si128( _mm_sub_epi32( zero, _mm_cmpeq_epi32( zero, zero ) ), 12 ), 4 );
	}

	XE_INLINE simd4i simd4i::ZAxis()
	{
		const __m128i zero = _mm_setzero_si128();
		return _mm_slli_si128( _mm_srli_si128( _mm_sub_epi32( zero, _mm_cmpeq_epi32( zero, zero ) ), 12 ), 8 );
	}

	XE_INLINE simd4i simd4i::WAxis()
	{
		const __m128i zero = _mm_setzero_si128();
		return _mm_slli_si128( _mm_sub_epi32( zero, _mm_cmpeq_epi32( zero, zero ) ), 12 );
	}

	XE_INLINE simd4i simd4i::AllTrue()
	{
		const __m128i zero = _mm_setzero_si128();
		return _mm_cmpeq_epi32( zero, zero );
	}

	XE_INLINE simd4i simd4i::AllFlase()
	{
		return _mm_setzero_si128();
	}

	XE_INLINE simd4i simd4i::MaskSign()
	{
		const __m128i zero = _mm_setzero_si128();
		return _mm_slli_epi32( _mm_cmpeq_epi32( zero, zero ), 31 );
	}

	XE_INLINE simd4i simd4i::MaskSignXYZ()
	{
		const __m128i zero = _mm_setzero_si128();
		return _mm_srli_si128( _mm_slli_epi32( _mm_cmpeq_epi32( zero, zero ), 31 ), 4 );
	}

	XE_INLINE simd4i simd4i::MaskSignW()
	{
		const __m128i zero = _mm_setzero_si128();
		return _mm_slli_si128( _mm_slli_epi32( _mm_cmpeq_epi32( zero, zero ), 31 ), 12 );
	}

	XE_INLINE simd4i simd4i::MaskNotSign()
	{
		const __m128i zero = _mm_setzero_si128();
		return _mm_srli_epi32( _mm_cmpeq_epi32( zero, zero ), 1 );
	}

	XE_INLINE simd4i simd4i::MaskFFFF()
	{
		const __m128i zero = _mm_setzero_si128();
		return _mm_cmpeq_epi32( zero, zero );
	}

	XE_INLINE simd4i simd4i::Mask0000()
	{
		return _mm_setzero_si128();
	}

	XE_INLINE simd4i simd4i::MaskFFF0()
	{
		const __m128i zero = _mm_setzero_si128();
		return _mm_srli_si128( _mm_cmpeq_epi32( zero, zero ), 4 );
	}

	XE_INLINE simd4i simd4i::MaskF000()
	{
		const __m128i zero = _mm_setzero_si128();
		return _mm_srli_si128( _mm_cmpeq_epi32( zero, zero ), 12 );
	}

	XE_INLINE simd4i simd4i::Mask0F00()
	{
		const __m128i zero = _mm_setzero_si128();
		return _mm_srli_si128( _mm_slli_si128( _mm_cmpeq_epi32( zero, zero ), 12 ), 8 );
	}

	XE_INLINE simd4i simd4i::Mask00F0()
	{
		const __m128i zero = _mm_setzero_si128();
		return _mm_srli_si128( _mm_slli_si128( _mm_cmpeq_epi32( zero, zero ), 12 ), 4 );
	}

	XE_INLINE simd4i simd4i::Mask000F()
	{
		const __m128i zero = _mm_setzero_si128();
		return _mm_slli_si128( _mm_cmpeq_epi32( zero, zero ), 12 );
	}

	XE_INLINE simd4i simd4i::Load( XE::int32 _x, XE::int32 _y, XE::int32 _z, XE::int32 _w )
	{
		return _mm_set_epi32( _w, _z, _y, _x );
	}

	XE_INLINE simd4i simd4i::LoadX( XE::int32 _x )
	{
		return _mm_set_epi32( 0, 0, 0, _x );
	}

	XE_INLINE simd4i simd4i::Load1( XE::int32 _x )
	{
		return _mm_set1_epi32( _x );
	}

	XE_INLINE simd4i simd4i::Load( bool _x, bool _y, bool _z, bool _w )
	{
		return _mm_sub_epi32( _mm_setzero_si128(), _mm_set_epi32( _w, _z, _y, _x ) );
	}

	XE_INLINE simd4i simd4i::LoadX( bool _x )
	{
		return _mm_sub_epi32( _mm_setzero_si128(), _mm_set_epi32( 0, 0, 0, _x ) );
	}

	XE_INLINE simd4i simd4i::Load1( bool _x )
	{
		return _mm_sub_epi32( _mm_setzero_si128(), _mm_set1_epi32( _x ) );
	}

	XE_INLINE simd4i simd4i::LoadPtr( const XE::int32 * _i )
	{
		return _mm_load_si128( reinterpret_cast< const __m128i * >( _i ) );
	}

	XE_INLINE simd4i simd4i::LoadXPtr( const XE::int32 * _i )
	{
		return _mm_cvtsi32_si128( *_i );
	}

	XE_INLINE simd4i simd4i::Load1Ptr( const XE::int32 * _i )
	{
		return _mm_shuffle_epi32( _mm_loadl_epi64( reinterpret_cast< const __m128i * >( _i ) ), _MM_SHUFFLE( 0, 0, 0, 0 ) );
	}

	XE_INLINE simd4i simd4i::Load2Ptr( const XE::int32 * _i )
	{
		return _mm_loadl_epi64( reinterpret_cast< const __m128i * >( _i ) );
	}

	XE_INLINE simd4i simd4i::Load3Ptr( const XE::int32 * _i )
	{
		return _mm_set_epi32( 0, _i[2], _i[1], _i[0] );
	}

	XE_INLINE simd4i simd4i::LoadPtrU( const XE::int32 * _i )
	{
		return _mm_loadu_si128( reinterpret_cast< const __m128i * >( _i ) );
	}

	XE_INLINE simd4i simd4i::LoadXPtrU( const XE::int32 * _i )
	{
		return _mm_cvtsi32_si128( *_i );
	}

	XE_INLINE simd4i simd4i::Load1PtrU( const XE::int32 * _i )
	{
		return _mm_set1_epi32( *_i );
	}

	XE_INLINE simd4i simd4i::Load2PtrU( const XE::int32 * _i )
	{
		return _mm_set_epi32( 0, 0, _i[1], _i[0] );
	}

	XE_INLINE simd4i simd4i::Load3PtrU( const XE::int32 * _i )
	{
		return _mm_set_epi32( 0, _i[2], _i[1], _i[0] );
	}

	XE_INLINE simd4i simd4i::FromFloatRound( const simd4f & _f )
	{
		return _mm_cvtps_epi32( _f );
	}

	XE_INLINE simd4i simd4i::FromFloatTrunc( const simd4f & _f )
	{
		return _mm_cvttps_epi32( _f );
	}

	XE_INLINE XE::int32 simd4i::GetX( const simd4i & _v )
	{
		return _mm_cvtsi128_si32( _v );
	}

	XE_INLINE XE::int32 simd4i::GetY( const simd4i & _v )
	{
		return _mm_cvtsi128_si32( XE_SSE_SPLAT_I( _v, 1 ) );
	}

	XE_INLINE XE::int32 simd4i::GetZ( const simd4i & _v )
	{
		return _mm_cvtsi128_si32( _mm_unpackhi_epi32( _v, _v ) );
	}

	XE_INLINE XE::int32 simd4i::GetW( const simd4i & _v )
	{
		return _mm_cvtsi128_si32( XE_SSE_SPLAT_I( _v, 3 ) );
	}

	XE_INLINE simd4i simd4i::SetX( const simd4i & _v, const simd4i & _i )
	{
		return _mm_castps_si128( _mm_move_ss( _mm_castsi128_ps( _v ), _mm_castsi128_ps( _i ) ) );
	}

	XE_INLINE simd4i simd4i::SetY( const simd4i & _v, const simd4i & _i )
	{
		const __m128 xfnn = _mm_castsi128_ps( _mm_unpacklo_epi32( _v, _i ) );
		return _mm_castps_si128( _mm_shuffle_ps( xfnn, _mm_castsi128_ps( _v ), _MM_SHUFFLE( 3, 2, 1, 0 ) ) );
	}

	XE_INLINE simd4i simd4i::SetZ( const simd4i & _v, const simd4i & _i )
	{
		const __m128 ffww = _mm_shuffle_ps( _mm_castsi128_ps( _i ), _mm_castsi128_ps( _v ), _MM_SHUFFLE( 3, 3, 0, 0 ) );
		return _mm_castps_si128( _mm_shuffle_ps( _mm_castsi128_ps( _v ), ffww, _MM_SHUFFLE( 2, 0, 1, 0 ) ) );
	}

	XE_INLINE simd4i simd4i::SetW( const simd4i & _v, const simd4i & _i )
	{
		const __m128 ffzz = _mm_shuffle_ps( _mm_castsi128_ps( _i ), _mm_castsi128_ps( _v ), _MM_SHUFFLE( 2, 2, 0, 0 ) );
		return _mm_castps_si128( _mm_shuffle_ps( _mm_castsi128_ps( _v ), ffzz, _MM_SHUFFLE( 0, 2, 1, 0 ) ) );
	}

	XE_INLINE simd4i simd4i::SetI( const simd4i & _v, const simd4i & _i, XE::int32 _ith )
	{
		union
		{
			simd4i ret;
			XE::int32 af[4];
		} u = { _v };
		u.af[_ith] = GetX( _i );
		return u.ret;
	}

	XE_INLINE void simd4i::StorePtr( const simd4i & _v, XE::int32 * _i )
	{
		_mm_store_si128( reinterpret_cast< __m128i * >( _i ), _v );
	}

	XE_INLINE void simd4i::Store1Ptr( const simd4i & _v, XE::int32 * _i )
	{
		*_i = _mm_cvtsi128_si32( _v );
	}

	XE_INLINE void simd4i::Store2Ptr( const simd4i & _v, XE::int32 * _i )
	{
		_i[0] = _mm_cvtsi128_si32( _v );
		_i[1] = _mm_cvtsi128_si32( XE_SSE_SPLAT_I( _v, 1 ) );
	}

	XE_INLINE void simd4i::Store3Ptr( const simd4i & _v, XE::int32 * _i )
	{
		_i[0] = _mm_cvtsi128_si32( _v );
		_i[1] = _mm_cvtsi128_si32( XE_SSE_SPLAT_I( _v, 1 ) );
		_i[2] = _mm_cvtsi128_si32( _mm_unpackhi_epi32( _v, _v ) );
	}

	XE_INLINE void simd4i::StorePtrU( const simd4i & _v, XE::int32 * _i )
	{
		_mm_storeu_si128( reinterpret_cast< __m128i * >( _i ), _v );
	}

	XE_INLINE void simd4i::Store1PtrU( const simd4i & _v, XE::int32 * _i )
	{
		*_i = _mm_cvtsi128_si32( _v );
	}

	XE_INLINE void simd4i::Store2PtrU( const simd4i & _v, XE::int32 * _i )
	{
		_i[0] = _mm_cvtsi128_si32( _v );
		_i[1] = _mm_cvtsi128_si32( XE_SSE_SPLAT_I( _v, 1 ) );
	}

	XE_INLINE void simd4i::Store3PtrU( const simd4i & _v, XE::int32 * _i )
	{
		_i[0] = _mm_cvtsi128_si32( _v );
		_i[1] = _mm_cvtsi128_si32( XE_SSE_SPLAT_I( _v, 1 ) );
		_i[2] = _mm_cvtsi128_si32( _mm_unpackhi_epi32( _v, _v ) );
	}

	XE_INLINE simd4i simd4i::SplatX( const simd4i & _a )
	{
		return XE_SSE_SPLAT_I( _a, 0 );
	}

	XE_INLINE simd4i simd4i::SplatY( const simd4i & _a )
	{
		return XE_SSE_SPLAT_I( _a, 1 );
	}

	XE_INLINE simd4i simd4i::SplatZ( const simd4i & _a )
	{
		return XE_SSE_SPLAT_I( _a, 2 );
	}

	XE_INLINE simd4i simd4i::SplatW( const simd4i & _a )
	{
		return XE_SSE_SPLAT_I( _a, 3 );
	}

	template <size_t _X, size_t _Y, size_t _Z, size_t _W> XE_INLINE simd4i simd4i::Swizzle( const simd4i & _v )
	{
		static_assert( _X <= 3 && _Y <= 3 && _Z <= 3 && _W <= 3, "Indices must be between 0 and 3" );
		return _mm_shuffle_epi32( _v, _MM_SHUFFLE( _W, _Z, _Y, _X ) );
	}

	template <> XE_INLINE simd4i simd4i::Swizzle<0, 1, 2, 3>( const simd4i & _v )
	{
		return _v;
	}

	XE_INLINE XE::int32 simd4i::MoveMask( const simd4i & _v )
	{
		return _mm_movemask_ps( _mm_castsi128_ps( _v ) );
	}

	XE_INLINE bool simd4i::AreAllTrue( const simd4i & _v )
	{
		return _mm_movemask_ps( _mm_castsi128_ps( _v ) ) == 0xf;
	}

	XE_INLINE bool simd4i::AreAllTrue3( const simd4i & _v )
	{
		return ( _mm_movemask_ps( _mm_castsi128_ps( _v ) ) & 0x7 ) == 0x7;
	}

	XE_INLINE bool simd4i::AreAllTrue2( const simd4i & _v )
	{
		return ( _mm_movemask_ps( _mm_castsi128_ps( _v ) ) & 0x3 ) == 0x3;
	}

	XE_INLINE bool simd4i::AreAllTrue1( const simd4i & _v )
	{
		return ( _mm_movemask_ps( _mm_castsi128_ps( _v ) ) & 0x1 ) == 0x1;
	}

	XE_INLINE bool simd4i::AreAllFalse( const simd4i & _v )
	{
		return _mm_movemask_ps( _mm_castsi128_ps( _v ) ) == 0;
	}

	XE_INLINE bool simd4i::AreAllFalse3( const simd4i & _v )
	{
		return ( _mm_movemask_ps( _mm_castsi128_ps( _v ) ) & 0x7 ) == 0;
	}

	XE_INLINE bool simd4i::AreAllFalse2( const simd4i & _v )
	{
		return ( _mm_movemask_ps( _mm_castsi128_ps( _v ) ) & 0x3 ) == 0;
	}

	XE_INLINE bool simd4i::AreAllFalse1( const simd4i & _v )
	{
		return ( _mm_movemask_ps( _mm_castsi128_ps( _v ) ) & 0x1 ) == 0;
	}

	XE_INLINE simd4i simd4i::HAdd2( const simd4i & _v )
	{
		const __m128i hadd = _mm_add_epi32( _v, XE_SSE_SPLAT_I( _v, 1 ) );
		return _mm_castps_si128( _mm_move_ss( _mm_castsi128_ps( _v ), _mm_castsi128_ps( hadd ) ) );
	}

	XE_INLINE simd4i simd4i::HAdd3( const simd4i & _v )
	{
		const __m128i hadd = _mm_add_epi32( _mm_add_epi32( _v, XE_SSE_SPLAT_I( _v, 1 ) ), _mm_unpackhi_epi32( _v, _v ) );
		return _mm_castps_si128( _mm_move_ss( _mm_castsi128_ps( _v ), _mm_castsi128_ps( hadd ) ) );
	}

	XE_INLINE simd4i simd4i::HAdd4( const simd4i & _v )
	{
		const __m128 v = _mm_castsi128_ps( _v );
		const __m128i haddxyzw = _mm_add_epi32( _v, _mm_castps_si128( _mm_movehl_ps( v, v ) ) );
		return _mm_castps_si128( _mm_move_ss( v, _mm_castsi128_ps( _mm_add_epi32( haddxyzw, XE_SSE_SPLAT_I( haddxyzw, 1 ) ) ) ) );
	}

	XE_INLINE simd4i simd4i::Abs( const simd4i & _v )
	{
	#ifdef XE_SIMD_SSSE3
		return _mm_abs_epi32( _v );
	#else   // XE_SIMD_SSSE3
		const __m128i zero = _mm_setzero_si128();
		return XE_SSE_SELECT_I( _mm_cmplt_epi32( _v, zero ), _mm_sub_epi32( zero, _v ), _v );
	#endif  // XE_SIMD_SSSE3
	}

	XE_INLINE simd4i simd4i::Sign( const simd4i & _v )
	{
		return _mm_slli_epi32( _mm_srli_epi32( _v, 31 ), 31 );
	}

	XE_INLINE simd4i simd4i::Min( const simd4i & _a, const simd4i & _b )
	{
	#ifdef XE_SIMD_SSE4_1
		return _mm_min_epi32( _a, _b );
	#else  // XE_SIMD_SSE4_1
		return XE_SSE_SELECT_I( _mm_cmplt_epi32( _a, _b ), _a, _b );
	#endif  // XE_SIMD_SSE4_1
	}

	XE_INLINE simd4i simd4i::Max( const simd4i & _a, const simd4i & _b )
	{
	#ifdef XE_SIMD_SSE4_1
		return _mm_max_epi32( _a, _b );
	#else  // XE_SIMD_SSE4_1
		return XE_SSE_SELECT_I( _mm_cmpgt_epi32( _a, _b ), _a, _b );
	#endif  // XE_SIMD_SSE4_1
	}

	XE_INLINE simd4i simd4i::Min0( const simd4i & _v )
	{
		const __m128i zero = _mm_setzero_si128();
	#ifdef XE_SIMD_SSE4_1
		return _mm_min_epi32( zero, _v );
	#else   // XE_SIMD_SSE4_1
		return XE_SSE_SELECT_I( _mm_cmplt_epi32( zero, _v ), zero, _v );
	#endif  // XE_SIMD_SSE4_1
	}

	XE_INLINE simd4i simd4i::Max0( const simd4i & _v )
	{
		const __m128i zero = _mm_setzero_si128();
	#ifdef XE_SIMD_SSE4_1
		return _mm_max_epi32( zero, _v );
	#else   // XE_SIMD_SSE4_1
		return XE_SSE_SELECT_I( _mm_cmpgt_epi32( zero, _v ), zero, _v );
	#endif  // XE_SIMD_SSE4_1
	}

	XE_INLINE simd4i simd4i::Clamp( const simd4i & _a, const simd4i & _v, const simd4i & _b )
	{
	#ifdef XE_SIMD_SSE4_1
		return _mm_min_epi32( _mm_max_epi32( _a, _v ), _b );
	#else   // XE_SIMD_SSE4_1
		const __m128i min = XE_SSE_SELECT_I( _mm_cmplt_epi32( _v, _b ), _v, _b );
		return XE_SSE_SELECT_I( _mm_cmpgt_epi32( _a, min ), _a, min );
	#endif  // XE_SIMD_SSE4_1
	}

	XE_INLINE simd4i simd4i::Select( const simd4i & _b, const simd4i & _true, const simd4i & _false )
	{
		return XE_SSE_SELECT_I( _b, _true, _false );
	}

	XE_INLINE simd4i simd4i::And( const simd4i & _a, const simd4i & _b )
	{
		return _mm_and_si128( _a, _b );
	}

	XE_INLINE simd4i simd4i::AndNot( const simd4i & _a, const simd4i & _b )
	{
		return _mm_andnot_si128( _b, _a );
	}

	XE_INLINE simd4i simd4i::Or( const simd4i & _a, const simd4i & _b )
	{
		return _mm_or_si128( _a, _b );
	}

	XE_INLINE simd4i simd4i::Xor( const simd4i & _a, const simd4i & _b )
	{
		return _mm_xor_si128( _a, _b );
	}

	XE_INLINE simd4i simd4i::Not( const simd4i & _v )
	{
		return _mm_xor_si128( _v, _mm_cmpeq_epi32( _v, _v ) );
	}

	XE_INLINE simd4i simd4i::ShiftL( const simd4i & _v, XE::int32 _bits )
	{
		return _mm_slli_epi32( _v, _bits );
	}

	XE_INLINE simd4i simd4i::ShiftR( const simd4i & _v, XE::int32 _bits )
	{
		return _mm_srai_epi32( _v, _bits );
	}

	XE_INLINE simd4i simd4i::ShiftRu( const simd4i & _v, XE::int32 _bits )
	{
		return _mm_srli_epi32( _v, _bits );
	}

	XE_INLINE simd4i simd4i::CmpEq( const simd4i & _a, const simd4i & _b )
	{
		return _mm_cmpeq_epi32( _a, _b );
	}

	XE_INLINE simd4i simd4i::CmpNe( const simd4i & _a, const simd4i & _b )
	{
		const __m128i eq = _mm_cmpeq_epi32( _a, _b );
		return _mm_xor_si128( eq, _mm_cmpeq_epi32( _a, _a ) );
	}

	XE_INLINE simd4i simd4i::CmpLt( const simd4i & _a, const simd4i & _b )
	{
		return _mm_cmpgt_epi32( _b, _a );
	}

	XE_INLINE simd4i simd4i::CmpLe( const simd4i & _a, const simd4i & _b )
	{
		const __m128i gt = _mm_cmpgt_epi32( _a, _b );
		return _mm_xor_si128( gt, _mm_cmpeq_epi32( _a, _a ) );
	}

	XE_INLINE simd4i simd4i::CmpGt( const simd4i & _a, const simd4i & _b )
	{
		return _mm_cmpgt_epi32( _a, _b );
	}

	XE_INLINE simd4i simd4i::CmpGe( const simd4i & _a, const simd4i & _b )
	{
		const __m128i lt = _mm_cmpgt_epi32( _b, _a );
		return _mm_xor_si128( lt, _mm_cmpeq_epi32( _a, _a ) );
	}



	XE_INLINE simd4f simd4f::Zero()
	{
		return _mm_setzero_ps();
	}

	XE_INLINE simd4f simd4f::One()
	{
		const __m128i zero = _mm_setzero_si128();
		return _mm_castsi128_ps( _mm_srli_epi32( _mm_slli_epi32( _mm_cmpeq_epi32( zero, zero ), 25 ), 2 ) );
	}

	XE_INLINE simd4f simd4f::XAxis()
	{
		const __m128i zero = _mm_setzero_si128();
		const __m128i one = _mm_srli_epi32( _mm_slli_epi32( _mm_cmpeq_epi32( zero, zero ), 25 ), 2 );
		return _mm_castsi128_ps( _mm_srli_si128( one, 12 ) );
	}

	XE_INLINE simd4f simd4f::YAxis()
	{
		const __m128i zero = _mm_setzero_si128();
		const __m128i one = _mm_srli_epi32( _mm_slli_epi32( _mm_cmpeq_epi32( zero, zero ), 25 ), 2 );
		return _mm_castsi128_ps( _mm_slli_si128( _mm_srli_si128( one, 12 ), 4 ) );
	}

	XE_INLINE simd4f simd4f::ZAxis()
	{
		const __m128i zero = _mm_setzero_si128();
		const __m128i one = _mm_srli_epi32( _mm_slli_epi32( _mm_cmpeq_epi32( zero, zero ), 25 ), 2 );
		return _mm_castsi128_ps( _mm_slli_si128( _mm_srli_si128( one, 12 ), 8 ) );
	}

	XE_INLINE simd4f simd4f::WAxis()
	{
		const __m128i zero = _mm_setzero_si128();
		const __m128i one = _mm_srli_epi32( _mm_slli_epi32( _mm_cmpeq_epi32( zero, zero ), 25 ), 2 );
		return _mm_castsi128_ps( _mm_slli_si128( one, 12 ) );
	}

	XE_INLINE simd4f simd4f::Load( XE::float32 _x, XE::float32 _y, XE::float32 _z, XE::float32 _w )
	{
		return _mm_set_ps( _w, _z, _y, _x );
	}

	XE_INLINE simd4f simd4f::LoadX( XE::float32 _x )
	{
		return _mm_set_ss( _x );
	}

	XE_INLINE simd4f simd4f::Load1( XE::float32 _x )
	{
		return _mm_set_ps1( _x );
	}

	XE_INLINE simd4f simd4f::LoadPtr( const XE::float32 * _f )
	{
		return _mm_load_ps( _f );
	}

	XE_INLINE simd4f simd4f::LoadPtrU( const XE::float32 * _f )
	{
		return _mm_loadu_ps( _f );
	}

	XE_INLINE simd4f simd4f::LoadXPtrU( const XE::float32 * _f )
	{
		return _mm_load_ss( _f );
	}

	XE_INLINE simd4f simd4f::Load1PtrU( const XE::float32 * _f )
	{
		return _mm_load_ps1( _f );
	}

	XE_INLINE simd4f simd4f::Load2PtrU( const XE::float32 * _f )
	{
		return _mm_unpacklo_ps( _mm_load_ss( _f + 0 ), _mm_load_ss( _f + 1 ) );
	}

	XE_INLINE simd4f simd4f::Load3PtrU( const XE::float32 * _f )
	{
		return _mm_movelh_ps( _mm_unpacklo_ps( _mm_load_ss( _f + 0 ), _mm_load_ss( _f + 1 ) ), _mm_load_ss( _f + 2 ) );
	}

	XE_INLINE simd4f simd4f::FromInt( const simd4i & _i )
	{
		return _mm_cvtepi32_ps( _i );
	}

	XE_INLINE XE::float32 simd4f::GetX( const simd4f & _v )
	{
		return _mm_cvtss_f32( _v );
	}

	XE_INLINE XE::float32 simd4f::GetY( const simd4f & _v )
	{
		return _mm_cvtss_f32( XE_SSE_SPLAT_F( _v, 1 ) );
	}

	XE_INLINE XE::float32 simd4f::GetZ( const simd4f & _v )
	{
		return _mm_cvtss_f32( _mm_movehl_ps( _v, _v ) );
	}

	XE_INLINE XE::float32 simd4f::GetW( const simd4f & _v )
	{
		return _mm_cvtss_f32( XE_SSE_SPLAT_F( _v, 3 ) );
	}

	XE_INLINE simd4f simd4f::SetX( const simd4f & _v, const simd4f & _f )
	{
		return _mm_move_ss( _v, _f );
	}

	XE_INLINE simd4f simd4f::SetY( const simd4f & _v, const simd4f & _f )
	{
		const __m128 xfnn = _mm_unpacklo_ps( _v, _f );
		return _mm_shuffle_ps( xfnn, _v, _MM_SHUFFLE( 3, 2, 1, 0 ) );
	}

	XE_INLINE simd4f simd4f::SetZ( const simd4f & _v, const simd4f & _f )
	{
		const __m128 ffww = _mm_shuffle_ps( _f, _v, _MM_SHUFFLE( 3, 3, 0, 0 ) );
		return _mm_shuffle_ps( _v, ffww, _MM_SHUFFLE( 2, 0, 1, 0 ) );
	}

	XE_INLINE simd4f simd4f::SetW( const simd4f & _v, const simd4f & _f )
	{
		const __m128 ffzz = _mm_shuffle_ps( _f, _v, _MM_SHUFFLE( 2, 2, 0, 0 ) );
		return _mm_shuffle_ps( _v, ffzz, _MM_SHUFFLE( 0, 2, 1, 0 ) );
	}

	XE_INLINE simd4f simd4f::SetI( const simd4f & _v, const simd4f & _f, XE::int32 _ith )
	{
		union
		{
			simd4f ret;
			XE::float32 af[4];
		} u = { _v };
		u.af[_ith] = _mm_cvtss_f32( _f );
		return u.ret;
	}

	XE_INLINE void simd4f::StorePtr( const simd4f & _v, XE::float32 * _f )
	{
		_mm_store_ps( _f, _v );
	}

	XE_INLINE void simd4f::Store1Ptr( const simd4f & _v, XE::float32 * _f )
	{
		_mm_store_ss( _f, _v );
	}

	XE_INLINE void simd4f::Store2Ptr( const simd4f & _v, XE::float32 * _f )
	{
		_mm_storel_pi( reinterpret_cast< __m64 * >( _f ), _v );
	}

	XE_INLINE void simd4f::Store3Ptr( const simd4f & _v, XE::float32 * _f )
	{
		_mm_storel_pi( reinterpret_cast< __m64 * >( _f ), _v );
		_mm_store_ss( _f + 2, _mm_movehl_ps( _v, _v ) );
	}

	XE_INLINE void simd4f::StorePtrU( const simd4f & _v, XE::float32 * _f )
	{
		_mm_storeu_ps( _f, _v );
	}

	XE_INLINE void simd4f::Store1PtrU( const simd4f & _v, XE::float32 * _f )
	{
		_mm_store_ss( _f, _v );
	}

	XE_INLINE void simd4f::Store2PtrU( const simd4f & _v, XE::float32 * _f )
	{
		_mm_store_ss( _f + 0, _v );
		_mm_store_ss( _f + 1, XE_SSE_SPLAT_F( _v, 1 ) );
	}

	XE_INLINE void simd4f::Store3PtrU( const simd4f & _v, XE::float32 * _f )
	{
		_mm_store_ss( _f + 0, _v );
		_mm_store_ss( _f + 1, XE_SSE_SPLAT_F( _v, 1 ) );
		_mm_store_ss( _f + 2, _mm_movehl_ps( _v, _v ) );
	}

	XE_INLINE simd4f simd4f::SplatX( const simd4f & _v )
	{
		return XE_SSE_SPLAT_F( _v, 0 );
	}

	XE_INLINE simd4f simd4f::SplatY( const simd4f & _v )
	{
		return XE_SSE_SPLAT_F( _v, 1 );
	}

	XE_INLINE simd4f simd4f::SplatZ( const simd4f & _v )
	{
		return XE_SSE_SPLAT_F( _v, 2 );
	}

	XE_INLINE simd4f simd4f::SplatW( const simd4f & _v )
	{
		return XE_SSE_SPLAT_F( _v, 3 );
	}

	template <size_t _X, size_t _Y, size_t _Z, size_t _W> XE_INLINE simd4f simd4f::Swizzle( const simd4f & _v )
	{
		return XE_SHUFFLE_PS1( _v, _MM_SHUFFLE( _W, _Z, _Y, _X ) );
	}

	template <> XE_INLINE simd4f simd4f::Swizzle<0, 1, 2, 3>( const simd4f & _v )
	{
		return _v;
	}

	template <> XE_INLINE simd4f simd4f::Swizzle<0, 1, 0, 1>( const simd4f & _v )
	{
		return _mm_movelh_ps( _v, _v );
	}

	template <> XE_INLINE simd4f simd4f::Swizzle<2, 3, 2, 3>( const simd4f & _v )
	{
		return _mm_movehl_ps( _v, _v );
	}

	template <> XE_INLINE simd4f simd4f::Swizzle<0, 0, 1, 1>( const simd4f & _v )
	{
		return _mm_unpacklo_ps( _v, _v );
	}

	template <> XE_INLINE simd4f simd4f::Swizzle<2, 2, 3, 3>( const simd4f & _v )
	{
		return _mm_unpackhi_ps( _v, _v );
	}

	XE_INLINE void simd4f::Transpose4x1( const simd4f _in[4], simd4f _out[1] )
	{
		const __m128 xz = _mm_unpacklo_ps( _in[0], _in[2] );
		const __m128 yw = _mm_unpacklo_ps( _in[1], _in[3] );
		_out[0] = _mm_unpacklo_ps( xz, yw );
	}

	XE_INLINE void simd4f::Transpose1x4( const simd4f _in[1], simd4f _out[4] )
	{
		const __m128 zwzw = _mm_movehl_ps( _in[0], _in[0] );
		const __m128 yyyy = XE_SSE_SPLAT_F( _in[0], 1 );
		const __m128 wwww = XE_SSE_SPLAT_F( _in[0], 3 );
		const __m128 zero = _mm_setzero_ps();
		_out[0] = _mm_move_ss( zero, _in[0] );
		_out[1] = _mm_move_ss( zero, yyyy );
		_out[2] = _mm_move_ss( zero, zwzw );
		_out[3] = _mm_move_ss( zero, wwww );
	}

	XE_INLINE void simd4f::Transpose4x2( const simd4f _in[4], simd4f _out[2] )
	{
		const __m128 tmp0 = _mm_unpacklo_ps( _in[0], _in[2] );
		const __m128 tmp1 = _mm_unpacklo_ps( _in[1], _in[3] );
		_out[0] = _mm_unpacklo_ps( tmp0, tmp1 );
		_out[1] = _mm_unpackhi_ps( tmp0, tmp1 );
	}

	XE_INLINE void simd4f::Transpose2x4( const simd4f _in[2], simd4f _out[4] )
	{
		const __m128 tmp0 = _mm_unpacklo_ps( _in[0], _in[1] );
		const __m128 tmp1 = _mm_unpackhi_ps( _in[0], _in[1] );
		const __m128 zero = _mm_setzero_ps();
		_out[0] = _mm_movelh_ps( tmp0, zero );
		_out[1] = _mm_movehl_ps( zero, tmp0 );
		_out[2] = _mm_movelh_ps( tmp1, zero );
		_out[3] = _mm_movehl_ps( zero, tmp1 );
	}

	XE_INLINE void simd4f::Transpose4x3( const simd4f _in[4], simd4f _out[3] )
	{
		const __m128 tmp0 = _mm_unpacklo_ps( _in[0], _in[2] );
		const __m128 tmp1 = _mm_unpacklo_ps( _in[1], _in[3] );
		const __m128 tmp2 = _mm_unpackhi_ps( _in[0], _in[2] );
		const __m128 tmp3 = _mm_unpackhi_ps( _in[1], _in[3] );
		_out[0] = _mm_unpacklo_ps( tmp0, tmp1 );
		_out[1] = _mm_unpackhi_ps( tmp0, tmp1 );
		_out[2] = _mm_unpacklo_ps( tmp2, tmp3 );
	}

	XE_INLINE void simd4f::Transpose3x4( const simd4f _in[3], simd4f _out[4] )
	{
		const __m128 zero = _mm_setzero_ps();
		const __m128 temp0 = _mm_unpacklo_ps( _in[0], _in[1] );
		const __m128 temp1 = _mm_unpacklo_ps( _in[2], zero );
		const __m128 temp2 = _mm_unpackhi_ps( _in[0], _in[1] );
		const __m128 temp3 = _mm_unpackhi_ps( _in[2], zero );
		_out[0] = _mm_movelh_ps( temp0, temp1 );
		_out[1] = _mm_movehl_ps( temp1, temp0 );
		_out[2] = _mm_movelh_ps( temp2, temp3 );
		_out[3] = _mm_movehl_ps( temp3, temp2 );
	}

	XE_INLINE void simd4f::Transpose4x4( const simd4f _in[4], simd4f _out[4] )
	{
		const __m128 tmp0 = _mm_unpacklo_ps( _in[0], _in[2] );
		const __m128 tmp1 = _mm_unpacklo_ps( _in[1], _in[3] );
		const __m128 tmp2 = _mm_unpackhi_ps( _in[0], _in[2] );
		const __m128 tmp3 = _mm_unpackhi_ps( _in[1], _in[3] );
		_out[0] = _mm_unpacklo_ps( tmp0, tmp1 );
		_out[1] = _mm_unpackhi_ps( tmp0, tmp1 );
		_out[2] = _mm_unpacklo_ps( tmp2, tmp3 );
		_out[3] = _mm_unpackhi_ps( tmp2, tmp3 );
	}

	XE_INLINE void simd4f::Transpose16x16( const simd4f _in[16], simd4f _out[16] )
	{
		const __m128 tmp0 = _mm_unpacklo_ps( _in[0], _in[2] );
		const __m128 tmp1 = _mm_unpacklo_ps( _in[1], _in[3] );
		_out[0] = _mm_unpacklo_ps( tmp0, tmp1 );
		_out[4] = _mm_unpackhi_ps( tmp0, tmp1 );
		const __m128 tmp2 = _mm_unpackhi_ps( _in[0], _in[2] );
		const __m128 tmp3 = _mm_unpackhi_ps( _in[1], _in[3] );
		_out[8] = _mm_unpacklo_ps( tmp2, tmp3 );
		_out[12] = _mm_unpackhi_ps( tmp2, tmp3 );
		const __m128 tmp4 = _mm_unpacklo_ps( _in[4], _in[6] );
		const __m128 tmp5 = _mm_unpacklo_ps( _in[5], _in[7] );
		_out[1] = _mm_unpacklo_ps( tmp4, tmp5 );
		_out[5] = _mm_unpackhi_ps( tmp4, tmp5 );
		const __m128 tmp6 = _mm_unpackhi_ps( _in[4], _in[6] );
		const __m128 tmp7 = _mm_unpackhi_ps( _in[5], _in[7] );
		_out[9] = _mm_unpacklo_ps( tmp6, tmp7 );
		_out[13] = _mm_unpackhi_ps( tmp6, tmp7 );
		const __m128 tmp8 = _mm_unpacklo_ps( _in[8], _in[10] );
		const __m128 tmp9 = _mm_unpacklo_ps( _in[9], _in[11] );
		_out[2] = _mm_unpacklo_ps( tmp8, tmp9 );
		_out[6] = _mm_unpackhi_ps( tmp8, tmp9 );
		const __m128 tmp10 = _mm_unpackhi_ps( _in[8], _in[10] );
		const __m128 tmp11 = _mm_unpackhi_ps( _in[9], _in[11] );
		_out[10] = _mm_unpacklo_ps( tmp10, tmp11 );
		_out[14] = _mm_unpackhi_ps( tmp10, tmp11 );
		const __m128 tmp12 = _mm_unpacklo_ps( _in[12], _in[14] );
		const __m128 tmp13 = _mm_unpacklo_ps( _in[13], _in[15] );
		_out[3] = _mm_unpacklo_ps( tmp12, tmp13 );
		_out[7] = _mm_unpackhi_ps( tmp12, tmp13 );
		const __m128 tmp14 = _mm_unpackhi_ps( _in[12], _in[14] );
		const __m128 tmp15 = _mm_unpackhi_ps( _in[13], _in[15] );
		_out[11] = _mm_unpacklo_ps( tmp14, tmp15 );
		_out[15] = _mm_unpackhi_ps( tmp14, tmp15 );
	}

	XE_INLINE simd4f simd4f::MAdd( const simd4f & _a, const simd4f & _b, const simd4f & _c )
	{
		return XE_MADD( _a, _b, _c );
	}

	XE_INLINE simd4f simd4f::MSub( const simd4f & _a, const simd4f & _b, const simd4f & _c )
	{
		return XE_MSUB( _a, _b, _c );
	}

	XE_INLINE simd4f simd4f::NMAdd( const simd4f & _a, const simd4f & _b, const simd4f & _c )
	{
		return XE_NMADD( _a, _b, _c );
	}

	XE_INLINE simd4f simd4f::NMSub( const simd4f & _a, const simd4f & _b, const simd4f & _c )
	{
		return XE_NMSUB( _a, _b, _c );
	}

	XE_INLINE simd4f simd4f::DivX( const simd4f & _a, const simd4f & _b )
	{
		return _mm_div_ss( _a, _b );
	}

	XE_INLINE simd4f simd4f::HAdd2( const simd4f & _v )
	{
		return XE_SSE_HADD2_F( _v );
	}

	XE_INLINE simd4f simd4f::HAdd3( const simd4f & _v )
	{
		return XE_SSE_HADD3_F( _v );
	}

	XE_INLINE simd4f simd4f::HAdd4( const simd4f & _v )
	{
		__m128 hadd4;
		XE_SSE_HADD4_F( _v, hadd4 );
		return hadd4;
	}

	XE_INLINE simd4f simd4f::Dot2( const simd4f & _a, const simd4f & _b )
	{
		__m128 dot2;
		XE_SSE_DOT2_F( _a, _b, dot2 );
		return dot2;
	}

	XE_INLINE simd4f simd4f::Dot3( const simd4f & _a, const simd4f & _b )
	{
		__m128 dot3;
		XE_SSE_DOT3_F( _a, _b, dot3 );
		return dot3;
	}

	XE_INLINE simd4f simd4f::Dot4( const simd4f & _a, const simd4f & _b )
	{
		__m128 dot4;
		XE_SSE_DOT4_F( _a, _b, dot4 );
		return dot4;
	}

	XE_INLINE simd4f simd4f::Cross3( const simd4f & _a, const simd4f & _b )
	{
		const __m128 shufa = XE_SHUFFLE_PS1( _a, _MM_SHUFFLE( 3, 0, 2, 1 ) );
		const __m128 shufb = XE_SHUFFLE_PS1( _b, _MM_SHUFFLE( 3, 0, 2, 1 ) );
		const __m128 shufc = XE_MSUB( _a, shufb, _mm_mul_ps( _b, shufa ) );
		return XE_SHUFFLE_PS1( shufc, _MM_SHUFFLE( 3, 0, 2, 1 ) );
	}

	XE_INLINE simd4f simd4f::RcpEst( const simd4f & _v )
	{
		return _mm_rcp_ps( _v );
	}

	XE_INLINE simd4f simd4f::RcpEstNR( const simd4f & _v )
	{
		const __m128 nr = _mm_rcp_ps( _v );
		return XE_NMADD( _mm_mul_ps( nr, nr ), _v, _mm_add_ps( nr, nr ) );
	}

	XE_INLINE simd4f simd4f::RcpEstX( const simd4f & _v )
	{
		return _mm_rcp_ss( _v );
	}

	XE_INLINE simd4f simd4f::RcpEstXNR( const simd4f & _v )
	{
		const __m128 nr = _mm_rcp_ss( _v );
		return XE_NMADDX( _mm_mul_ss( nr, nr ), _v, _mm_add_ss( nr, nr ) );
	}

	XE_INLINE simd4f simd4f::Sqrt( const simd4f & _v )
	{
		return _mm_sqrt_ps( _v );
	}

	XE_INLINE simd4f simd4f::SqrtX( const simd4f & _v )
	{
		return _mm_sqrt_ss( _v );
	}

	XE_INLINE simd4f simd4f::RSqrtEst( const simd4f & _v )
	{
		return _mm_rsqrt_ps( _v );
	}

	XE_INLINE simd4f simd4f::RSqrtEstNR( const simd4f & _v )
	{
		const __m128 nr = _mm_rsqrt_ps( _v );
		return _mm_mul_ps( _mm_mul_ps( _mm_set_ps1( .5f ), nr ), XE_NMADD( _mm_mul_ps( _v, nr ), nr, _mm_set_ps1( 3.f ) ) );
	}

	XE_INLINE simd4f simd4f::RSqrtEstX( const simd4f & _v )
	{
		return _mm_rsqrt_ss( _v );
	}

	XE_INLINE simd4f simd4f::RSqrtEstXNR( const simd4f & _v )
	{
		const __m128 nr = _mm_rsqrt_ss( _v );
		return _mm_mul_ss( _mm_mul_ss( _mm_set_ps1( .5f ), nr ), XE_NMADDX( _mm_mul_ss( _v, nr ), nr, _mm_set_ps1( 3.f ) ) );
	}

	XE_INLINE simd4f simd4f::Abs( const simd4f & _v )
	{
		const __m128i zero = _mm_setzero_si128();
		return _mm_and_ps( _mm_castsi128_ps( _mm_srli_epi32( _mm_cmpeq_epi32( zero, zero ), 1 ) ), _v );
	}

	XE_INLINE simd4i simd4f::Sign( const simd4f & _v )
	{
		return _mm_slli_epi32( _mm_srli_epi32( _mm_castps_si128( _v ), 31 ), 31 );
	}

	XE_INLINE simd4f simd4f::Length2( const simd4f & _v )
	{
		__m128 sq_len;
		XE_SSE_DOT2_F( _v, _v, sq_len );
		return _mm_sqrt_ss( sq_len );
	}

	XE_INLINE simd4f simd4f::Length3( const simd4f & _v )
	{
		__m128 sq_len;
		XE_SSE_DOT3_F( _v, _v, sq_len );
		return _mm_sqrt_ss( sq_len );
	}

	XE_INLINE simd4f simd4f::Length4( const simd4f & _v )
	{
		__m128 sq_len;
		XE_SSE_DOT4_F( _v, _v, sq_len );
		return _mm_sqrt_ss( sq_len );
	}

	XE_INLINE simd4f simd4f::Length2Sqr( const simd4f & _v )
	{
		__m128 sq_len;
		XE_SSE_DOT2_F( _v, _v, sq_len );
		return sq_len;
	}

	XE_INLINE simd4f simd4f::Length3Sqr( const simd4f & _v )
	{
		__m128 sq_len;
		XE_SSE_DOT3_F( _v, _v, sq_len );
		return sq_len;
	}

	XE_INLINE simd4f simd4f::Length4Sqr( const simd4f & _v )
	{
		__m128 sq_len;
		XE_SSE_DOT4_F( _v, _v, sq_len );
		return sq_len;
	}

	XE_INLINE simd4f simd4f::Normalize2( const simd4f & _v )
	{
		__m128 sq_len;
		XE_SSE_DOT2_F( _v, _v, sq_len );
		const __m128 inv_len = _mm_div_ss( simd4f::One(), _mm_sqrt_ss( sq_len ) );
		const __m128 inv_lenxxxx = XE_SSE_SPLAT_F( inv_len, 0 );
		const __m128 norm = _mm_mul_ps( _v, inv_lenxxxx );
		return _mm_movelh_ps( norm, _mm_movehl_ps( _v, _v ) );
	}

	XE_INLINE simd4f simd4f::Normalize3( const simd4f & _v )
	{
		__m128 sq_len;
		XE_SSE_DOT3_F( _v, _v, sq_len );
		const __m128 inv_len = _mm_div_ss( simd4f::One(), _mm_sqrt_ss( sq_len ) );
		const __m128 vwxyz = XE_SHUFFLE_PS1( _v, _MM_SHUFFLE( 0, 1, 2, 3 ) );
		const __m128 inv_lenxxxx = XE_SSE_SPLAT_F( inv_len, 0 );
		const __m128 normwxyz = _mm_move_ss( _mm_mul_ps( vwxyz, inv_lenxxxx ), vwxyz );
		return XE_SHUFFLE_PS1( normwxyz, _MM_SHUFFLE( 0, 1, 2, 3 ) );
	}

	XE_INLINE simd4f simd4f::Normalize4( const simd4f & _v )
	{
		__m128 sq_len;
		XE_SSE_DOT4_F( _v, _v, sq_len );
		const __m128 inv_len = _mm_div_ss( simd4f::One(), _mm_sqrt_ss( sq_len ) );
		const __m128 inv_lenxxxx = XE_SSE_SPLAT_F( inv_len, 0 );
		return _mm_mul_ps( _v, inv_lenxxxx );
	}

	XE_INLINE simd4f simd4f::NormalizeEst2( const simd4f & _v )
	{
		__m128 sq_len;
		XE_SSE_DOT2_F( _v, _v, sq_len );
		const __m128 inv_len = _mm_rsqrt_ss( sq_len );
		const __m128 inv_lenxxxx = XE_SSE_SPLAT_F( inv_len, 0 );
		const __m128 norm = _mm_mul_ps( _v, inv_lenxxxx );
		return _mm_movelh_ps( norm, _mm_movehl_ps( _v, _v ) );
	}

	XE_INLINE simd4f simd4f::NormalizeEst3( const simd4f & _v )
	{
		__m128 sq_len;
		XE_SSE_DOT3_F( _v, _v, sq_len );
		const __m128 inv_len = _mm_rsqrt_ss( sq_len );
		const __m128 vwxyz = XE_SHUFFLE_PS1( _v, _MM_SHUFFLE( 0, 1, 2, 3 ) );
		const __m128 inv_lenxxxx = XE_SSE_SPLAT_F( inv_len, 0 );
		const __m128 normwxyz = _mm_move_ss( _mm_mul_ps( vwxyz, inv_lenxxxx ), vwxyz );
		return XE_SHUFFLE_PS1( normwxyz, _MM_SHUFFLE( 0, 1, 2, 3 ) );
	}

	XE_INLINE simd4f simd4f::NormalizeEst4( const simd4f & _v )
	{
		__m128 sq_len;
		XE_SSE_DOT4_F( _v, _v, sq_len );
		const __m128 inv_len = _mm_rsqrt_ss( sq_len );
		const __m128 inv_lenxxxx = XE_SSE_SPLAT_F( inv_len, 0 );
		return _mm_mul_ps( _v, inv_lenxxxx );
	}

	XE_INLINE simd4i simd4f::IsNormalized2( const simd4f & _v )
	{
		const __m128 max = _mm_set_ss( 1.f + 1e-6f );
		const __m128 min = _mm_set_ss( 1.f - 1e-6f );
		__m128 dot;
		XE_SSE_DOT2_F( _v, _v, dot );
		__m128 dotx000 = _mm_move_ss( _mm_setzero_ps(), dot );
		return _mm_castps_si128( _mm_and_ps( _mm_cmplt_ss( dotx000, max ), _mm_cmpgt_ss( dotx000, min ) ) );
	}

	XE_INLINE simd4i simd4f::IsNormalized3( const simd4f & _v )
	{
		const __m128 max = _mm_set_ss( 1.f + 1e-6f );
		const __m128 min = _mm_set_ss( 1.f - 1e-6f );
		__m128 dot;
		XE_SSE_DOT3_F( _v, _v, dot );
		__m128 dotx000 = _mm_move_ss( _mm_setzero_ps(), dot );
		return _mm_castps_si128( _mm_and_ps( _mm_cmplt_ss( dotx000, max ), _mm_cmpgt_ss( dotx000, min ) ) );
	}

	XE_INLINE simd4i simd4f::IsNormalized4( const simd4f & _v )
	{
		const __m128 max = _mm_set_ss( 1.f + 1e-6f );
		const __m128 min = _mm_set_ss( 1.f - 1e-6f );
		__m128 dot;
		XE_SSE_DOT4_F( _v, _v, dot );
		__m128 dotx000 = _mm_move_ss( _mm_setzero_ps(), dot );
		return _mm_castps_si128( _mm_and_ps( _mm_cmplt_ss( dotx000, max ), _mm_cmpgt_ss( dotx000, min ) ) );
	}

	XE_INLINE simd4i simd4f::IsNormalizedEst2( const simd4f & _v )
	{
		const __m128 max = _mm_set_ss( 1.f + 2e-3f );
		const __m128 min = _mm_set_ss( 1.f - 2e-3f );
		__m128 dot;
		XE_SSE_DOT2_F( _v, _v, dot );
		__m128 dotx000 = _mm_move_ss( _mm_setzero_ps(), dot );
		return _mm_castps_si128( _mm_and_ps( _mm_cmplt_ss( dotx000, max ), _mm_cmpgt_ss( dotx000, min ) ) );
	}

	XE_INLINE simd4i simd4f::IsNormalizedEst3( const simd4f & _v )
	{
		const __m128 max = _mm_set_ss( 1.f + 2e-3f );
		const __m128 min = _mm_set_ss( 1.f - 2e-3f );
		__m128 dot;
		XE_SSE_DOT3_F( _v, _v, dot );
		__m128 dotx000 = _mm_move_ss( _mm_setzero_ps(), dot );
		return _mm_castps_si128( _mm_and_ps( _mm_cmplt_ss( dotx000, max ), _mm_cmpgt_ss( dotx000, min ) ) );
	}

	XE_INLINE simd4i simd4f::IsNormalizedEst4( const simd4f & _v )
	{
		const __m128 max = _mm_set_ss( 1.f + 2e-3f );
		const __m128 min = _mm_set_ss( 1.f - 2e-3f );
		__m128 dot;
		XE_SSE_DOT4_F( _v, _v, dot );
		__m128 dotx000 = _mm_move_ss( _mm_setzero_ps(), dot );
		return _mm_castps_si128( _mm_and_ps( _mm_cmplt_ss( dotx000, max ), _mm_cmpgt_ss( dotx000, min ) ) );
	}

	XE_INLINE simd4f simd4f::NormalizeSafe2( const simd4f & _v, const simd4f & _safe )
	{
		__m128 sq_len;
		XE_SSE_DOT2_F( _v, _v, sq_len );
		const __m128 inv_len = _mm_div_ss( simd4f::One(), _mm_sqrt_ss( sq_len ) );
		const __m128 inv_lenxxxx = XE_SSE_SPLAT_F( inv_len, 0 );
		const __m128 norm = _mm_mul_ps( _v, inv_lenxxxx );
		const __m128i cond = _mm_castps_si128( _mm_cmple_ps( XE_SSE_SPLAT_F( sq_len, 0 ), _mm_setzero_ps() ) );
		const __m128 cfalse = _mm_movelh_ps( norm, _mm_movehl_ps( _v, _v ) );
		return XE_SSE_SELECT_F( cond, _safe, cfalse );
	}

	XE_INLINE simd4f simd4f::NormalizeSafe3( const simd4f & _v, const simd4f & _safe )
	{
		__m128 sq_len;
		XE_SSE_DOT3_F( _v, _v, sq_len );
		const __m128 inv_len = _mm_div_ss( simd4f::One(), _mm_sqrt_ss( sq_len ) );
		const __m128 vwxyz = XE_SHUFFLE_PS1( _v, _MM_SHUFFLE( 0, 1, 2, 3 ) );
		const __m128 inv_lenxxxx = XE_SSE_SPLAT_F( inv_len, 0 );
		const __m128 normwxyz = _mm_move_ss( _mm_mul_ps( vwxyz, inv_lenxxxx ), vwxyz );
		const __m128i cond = _mm_castps_si128( _mm_cmple_ps( XE_SSE_SPLAT_F( sq_len, 0 ), _mm_setzero_ps() ) );
		const __m128 cfalse = XE_SHUFFLE_PS1( normwxyz, _MM_SHUFFLE( 0, 1, 2, 3 ) );
		return XE_SSE_SELECT_F( cond, _safe, cfalse );
	}

	XE_INLINE simd4f simd4f::NormalizeSafe4( const simd4f & _v, const simd4f & _safe )
	{
		__m128 sq_len;
		XE_SSE_DOT4_F( _v, _v, sq_len );
		const __m128 inv_len = _mm_div_ss( simd4f::One(), _mm_sqrt_ss( sq_len ) );
		const __m128 inv_lenxxxx = XE_SSE_SPLAT_F( inv_len, 0 );
		const __m128i cond = _mm_castps_si128( _mm_cmple_ps( XE_SSE_SPLAT_F( sq_len, 0 ), _mm_setzero_ps() ) );
		const __m128 cfalse = _mm_mul_ps( _v, inv_lenxxxx );
		return XE_SSE_SELECT_F( cond, _safe, cfalse );
	}

	XE_INLINE simd4f simd4f::NormalizeSafeEst2( const simd4f & _v, const simd4f & _safe )
	{
		__m128 sq_len;
		XE_SSE_DOT2_F( _v, _v, sq_len );
		const __m128 inv_len = _mm_rsqrt_ss( sq_len );
		const __m128 inv_lenxxxx = XE_SSE_SPLAT_F( inv_len, 0 );
		const __m128 norm = _mm_mul_ps( _v, inv_lenxxxx );
		const __m128i cond = _mm_castps_si128( _mm_cmple_ps( XE_SSE_SPLAT_F( sq_len, 0 ), _mm_setzero_ps() ) );
		const __m128 cfalse = _mm_movelh_ps( norm, _mm_movehl_ps( _v, _v ) );
		return XE_SSE_SELECT_F( cond, _safe, cfalse );
	}

	XE_INLINE simd4f simd4f::NormalizeSafeEst3( const simd4f & _v, const simd4f & _safe )
	{
		__m128 sq_len;
		XE_SSE_DOT3_F( _v, _v, sq_len );
		const __m128 inv_len = _mm_rsqrt_ss( sq_len );
		const __m128 vwxyz = XE_SHUFFLE_PS1( _v, _MM_SHUFFLE( 0, 1, 2, 3 ) );
		const __m128 inv_lenxxxx = XE_SSE_SPLAT_F( inv_len, 0 );
		const __m128 normwxyz = _mm_move_ss( _mm_mul_ps( vwxyz, inv_lenxxxx ), vwxyz );
		const __m128i cond = _mm_castps_si128( _mm_cmple_ps( XE_SSE_SPLAT_F( sq_len, 0 ), _mm_setzero_ps() ) );
		const __m128 cfalse = XE_SHUFFLE_PS1( normwxyz, _MM_SHUFFLE( 0, 1, 2, 3 ) );
		return XE_SSE_SELECT_F( cond, _safe, cfalse );
	}

	XE_INLINE simd4f simd4f::NormalizeSafeEst4( const simd4f & _v, const simd4f & _safe )
	{
		__m128 sq_len;
		XE_SSE_DOT4_F( _v, _v, sq_len );
		const __m128 inv_len = _mm_rsqrt_ss( sq_len );
		const __m128 inv_lenxxxx = XE_SSE_SPLAT_F( inv_len, 0 );
		const __m128i cond = _mm_castps_si128( _mm_cmple_ps( XE_SSE_SPLAT_F( sq_len, 0 ), _mm_setzero_ps() ) );
		const __m128 cfalse = _mm_mul_ps( _v, inv_lenxxxx );
		return XE_SSE_SELECT_F( cond, _safe, cfalse );
	}

	XE_INLINE simd4f simd4f::Lerp( const simd4f & _a, const simd4f & _b, const simd4f & _alpha )
	{
		return XE_MADD( _alpha, _mm_sub_ps( _b, _a ), _a );
	}

	XE_INLINE simd4f simd4f::Min( const simd4f & _a, const simd4f & _b )
	{
		return _mm_min_ps( _a, _b );
	}

	XE_INLINE simd4f simd4f::Max( const simd4f & _a, const simd4f & _b )
	{
		return _mm_max_ps( _a, _b );
	}

	XE_INLINE simd4f simd4f::Min0( const simd4f & _v )
	{
		return _mm_min_ps( _mm_setzero_ps(), _v );
	}

	XE_INLINE simd4f simd4f::Max0( const simd4f & _v )
	{
		return _mm_max_ps( _mm_setzero_ps(), _v );
	}

	XE_INLINE simd4f simd4f::Clamp( const simd4f & _a, const simd4f & _v, const simd4f & _b )
	{
		return _mm_max_ps( _a, _mm_min_ps( _v, _b ) );
	}

	XE_INLINE simd4f simd4f::Select( const simd4i & _b, const simd4f & _true, const simd4f & _false )
	{
		return XE_SSE_SELECT_F( _b, _true, _false );
	}

	XE_INLINE simd4i simd4f::CmpEq( const simd4f & _a, const simd4f & _b )
	{
		return _mm_castps_si128( _mm_cmpeq_ps( _a, _b ) );
	}

	XE_INLINE simd4i simd4f::CmpNe( const simd4f & _a, const simd4f & _b )
	{
		return _mm_castps_si128( _mm_cmpneq_ps( _a, _b ) );
	}

	XE_INLINE simd4i simd4f::CmpLt( const simd4f & _a, const simd4f & _b )
	{
		return _mm_castps_si128( _mm_cmplt_ps( _a, _b ) );
	}

	XE_INLINE simd4i simd4f::CmpLe( const simd4f & _a, const simd4f & _b )
	{
		return _mm_castps_si128( _mm_cmple_ps( _a, _b ) );
	}

	XE_INLINE simd4i simd4f::CmpGt( const simd4f & _a, const simd4f & _b )
	{
		return _mm_castps_si128( _mm_cmpgt_ps( _a, _b ) );
	}

	XE_INLINE simd4i simd4f::CmpGe( const simd4f & _a, const simd4f & _b )
	{
		return _mm_castps_si128( _mm_cmpge_ps( _a, _b ) );
	}

	XE_INLINE simd4f simd4f::And( const simd4f & _a, const simd4f & _b )
	{
		return _mm_and_ps( _a, _b );
	}

	XE_INLINE simd4f simd4f::Or( const simd4f & _a, const simd4f & _b )
	{
		return _mm_or_ps( _a, _b );
	}

	XE_INLINE simd4f simd4f::Xor( const simd4f & _a, const simd4f & _b )
	{
		return _mm_xor_ps( _a, _b );
	}

	XE_INLINE simd4f simd4f::And( const simd4f & _a, const simd4i & _b )
	{
		return _mm_and_ps( _a, _mm_castsi128_ps( _b ) );
	}

	XE_INLINE simd4f simd4f::AndNot( const simd4f & _a, const simd4i & _b )
	{
		return _mm_andnot_ps( _mm_castsi128_ps( _b ), _a );
	}

	XE_INLINE simd4f simd4f::Or( const simd4f & _a, const simd4i & _b )
	{
		return _mm_or_ps( _a, _mm_castsi128_ps( _b ) );
	}

	XE_INLINE simd4f simd4f::Xor( const simd4f & _a, const simd4i & _b )
	{
		return _mm_xor_ps( _a, _mm_castsi128_ps( _b ) );
	}

	XE_INLINE simd4f simd4f::Cos( const simd4f & _v )
	{
		return _mm_set_ps( std::cos( GetW( _v ) ), std::cos( GetZ( _v ) ), std::cos( GetY( _v ) ), std::cos( GetX( _v ) ) );
	}

	XE_INLINE simd4f simd4f::CosX( const simd4f & _v )
	{
		return _mm_move_ss( _v, _mm_set_ps1( std::cos( GetX( _v ) ) ) );
	}

	XE_INLINE simd4f simd4f::ACos( const simd4f & _v )
	{
		return _mm_set_ps( std::acos( GetW( _v ) ), std::acos( GetZ( _v ) ), std::acos( GetY( _v ) ), std::acos( GetX( _v ) ) );
	}

	XE_INLINE simd4f simd4f::ACosX( const simd4f & _v )
	{
		return _mm_move_ss( _v, _mm_set_ps1( std::acos( GetX( _v ) ) ) );
	}

	XE_INLINE simd4f simd4f::Sin( const simd4f & _v )
	{
		return _mm_set_ps( std::sin( GetW( _v ) ), std::sin( GetZ( _v ) ), std::sin( GetY( _v ) ), std::sin( GetX( _v ) ) );
	}

	XE_INLINE simd4f simd4f::SinX( const simd4f & _v )
	{
		return _mm_move_ss( _v, _mm_set_ps1( std::sin( GetX( _v ) ) ) );
	}

	XE_INLINE simd4f simd4f::ASin( const simd4f & _v )
	{
		return _mm_set_ps( std::asin( GetW( _v ) ), std::asin( GetZ( _v ) ), std::asin( GetY( _v ) ), std::asin( GetX( _v ) ) );
	}

	XE_INLINE simd4f simd4f::ASinX( const simd4f & _v )
	{
		return _mm_move_ss( _v, _mm_set_ps1( std::asin( GetX( _v ) ) ) );
	}

	XE_INLINE simd4f simd4f::Tan( const simd4f & _v )
	{
		return _mm_set_ps( std::tan( GetW( _v ) ), std::tan( GetZ( _v ) ), std::tan( GetY( _v ) ), std::tan( GetX( _v ) ) );
	}

	XE_INLINE simd4f simd4f::TanX( const simd4f & _v )
	{
		return _mm_move_ss( _v, _mm_set_ps1( std::tan( GetX( _v ) ) ) );
	}

	XE_INLINE simd4f simd4f::ATan( const simd4f & _v )
	{
		return _mm_set_ps( std::atan( GetW( _v ) ), std::atan( GetZ( _v ) ), std::atan( GetY( _v ) ), std::atan( GetX( _v ) ) );
	}

	XE_INLINE simd4f simd4f::ATanX( const simd4f & _v )
	{
		return _mm_move_ss( _v, _mm_set_ps1( std::atan( GetX( _v ) ) ) );
	}


	XE_INLINE simd4x4 simd4x4::identity()
	{
		const __m128i zero = _mm_setzero_si128();
		const __m128i ffff = _mm_cmpeq_epi32( zero, zero );
		const __m128i one = _mm_srli_epi32( _mm_slli_epi32( ffff, 25 ), 2 );
		const __m128i x = _mm_srli_si128( one, 12 );
		return { _mm_castsi128_ps( x ), _mm_castsi128_ps( _mm_slli_si128( x, 4 ) ), _mm_castsi128_ps( _mm_slli_si128( x, 8 ) ), _mm_castsi128_ps( _mm_slli_si128( one, 12 ) ) };
	}

	XE_INLINE simd4x4 simd4x4::Transpose( const simd4x4 & _m )
	{
		const __m128 tmp0 = _mm_unpacklo_ps( _m.cols[0], _m.cols[2] );
		const __m128 tmp1 = _mm_unpacklo_ps( _m.cols[1], _m.cols[3] );
		const __m128 tmp2 = _mm_unpackhi_ps( _m.cols[0], _m.cols[2] );
		const __m128 tmp3 = _mm_unpackhi_ps( _m.cols[1], _m.cols[3] );
		return { {_mm_unpacklo_ps( tmp0, tmp1 ), _mm_unpackhi_ps( tmp0, tmp1 ), _mm_unpacklo_ps( tmp2, tmp3 ), _mm_unpackhi_ps( tmp2, tmp3 )} };
	}

	XE_INLINE simd4x4 simd4x4::Invert( const simd4x4 & _m, simd4i * _invertible )
	{
		const __m128 _t0 = _mm_shuffle_ps( _m.cols[0], _m.cols[1], _MM_SHUFFLE( 1, 0, 1, 0 ) );
		const __m128 _t1 = _mm_shuffle_ps( _m.cols[2], _m.cols[3], _MM_SHUFFLE( 1, 0, 1, 0 ) );
		const __m128 _t2 = _mm_shuffle_ps( _m.cols[0], _m.cols[1], _MM_SHUFFLE( 3, 2, 3, 2 ) );
		const __m128 _t3 = _mm_shuffle_ps( _m.cols[2], _m.cols[3], _MM_SHUFFLE( 3, 2, 3, 2 ) );
		const __m128 c0 = _mm_shuffle_ps( _t0, _t1, _MM_SHUFFLE( 2, 0, 2, 0 ) );
		const __m128 c1 = _mm_shuffle_ps( _t1, _t0, _MM_SHUFFLE( 3, 1, 3, 1 ) );
		const __m128 c2 = _mm_shuffle_ps( _t2, _t3, _MM_SHUFFLE( 2, 0, 2, 0 ) );
		const __m128 c3 = _mm_shuffle_ps( _t3, _t2, _MM_SHUFFLE( 3, 1, 3, 1 ) );

		__m128 minor0, minor1, minor2, minor3, tmp1, tmp2;
		tmp1 = _mm_mul_ps( c2, c3 );
		tmp1 = XE_SHUFFLE_PS1( tmp1, 0xB1 );
		minor0 = _mm_mul_ps( c1, tmp1 );
		minor1 = _mm_mul_ps( c0, tmp1 );
		tmp1 = XE_SHUFFLE_PS1( tmp1, 0x4E );
		minor0 = XE_MSUB( c1, tmp1, minor0 );
		minor1 = XE_MSUB( c0, tmp1, minor1 );
		minor1 = XE_SHUFFLE_PS1( minor1, 0x4E );

		tmp1 = _mm_mul_ps( c1, c2 );
		tmp1 = XE_SHUFFLE_PS1( tmp1, 0xB1 );
		minor0 = XE_MADD( c3, tmp1, minor0 );
		minor3 = _mm_mul_ps( c0, tmp1 );
		tmp1 = XE_SHUFFLE_PS1( tmp1, 0x4E );
		minor0 = XE_NMADD( c3, tmp1, minor0 );
		minor3 = XE_MSUB( c0, tmp1, minor3 );
		minor3 = XE_SHUFFLE_PS1( minor3, 0x4E );

		tmp1 = _mm_mul_ps( XE_SHUFFLE_PS1( c1, 0x4E ), c3 );
		tmp1 = XE_SHUFFLE_PS1( tmp1, 0xB1 );
		tmp2 = XE_SHUFFLE_PS1( c2, 0x4E );
		minor0 = XE_MADD( tmp2, tmp1, minor0 );
		minor2 = _mm_mul_ps( c0, tmp1 );
		tmp1 = XE_SHUFFLE_PS1( tmp1, 0x4E );
		minor0 = XE_NMADD( tmp2, tmp1, minor0 );
		minor2 = XE_MSUB( c0, tmp1, minor2 );
		minor2 = XE_SHUFFLE_PS1( minor2, 0x4E );

		tmp1 = _mm_mul_ps( c0, c1 );
		tmp1 = XE_SHUFFLE_PS1( tmp1, 0xB1 );
		minor2 = XE_MADD( c3, tmp1, minor2 );
		minor3 = XE_MSUB( tmp2, tmp1, minor3 );
		tmp1 = XE_SHUFFLE_PS1( tmp1, 0x4E );
		minor2 = XE_MSUB( c3, tmp1, minor2 );
		minor3 = XE_NMADD( tmp2, tmp1, minor3 );

		tmp1 = _mm_mul_ps( c0, c3 );
		tmp1 = XE_SHUFFLE_PS1( tmp1, 0xB1 );
		minor1 = XE_NMADD( tmp2, tmp1, minor1 );
		minor2 = XE_MADD( c1, tmp1, minor2 );
		tmp1 = XE_SHUFFLE_PS1( tmp1, 0x4E );
		minor1 = XE_MADD( tmp2, tmp1, minor1 );
		minor2 = XE_NMADD( c1, tmp1, minor2 );

		tmp1 = _mm_mul_ps( c0, tmp2 );
		tmp1 = XE_SHUFFLE_PS1( tmp1, 0xB1 );
		minor1 = XE_MADD( c3, tmp1, minor1 );
		minor3 = XE_NMADD( c1, tmp1, minor3 );
		tmp1 = XE_SHUFFLE_PS1( tmp1, 0x4E );
		minor1 = XE_NMADD( c3, tmp1, minor1 );
		minor3 = XE_MADD( c1, tmp1, minor3 );

		__m128 det;
		det = _mm_mul_ps( c0, minor0 );
		det = _mm_add_ps( XE_SHUFFLE_PS1( det, 0x4E ), det );
		det = _mm_add_ss( XE_SHUFFLE_PS1( det, 0xB1 ), det );
		const simd4i & invertible = simd4f::CmpNe( det, simd4f::Zero() );
		if( _invertible != nullptr )
		{
			*_invertible = invertible;
		}
		tmp1 = XE_SSE_SELECT_F( invertible, simd4f::RcpEstNR( det ), simd4f::Zero() );
		det = XE_NMADDX( det, _mm_mul_ss( tmp1, tmp1 ), _mm_add_ss( tmp1, tmp1 ) );
		det = XE_SHUFFLE_PS1( det, 0x00 );

		return { {_mm_mul_ps( det, minor0 ), _mm_mul_ps( det, minor1 ), _mm_mul_ps( det, minor2 ), _mm_mul_ps( det, minor3 )} };
	}

	XE_INLINE simd4x4 simd4x4::Translation( const simd4f & _v )
	{
		const __m128i zero = _mm_setzero_si128();
		const __m128i ffff = _mm_cmpeq_epi32( zero, zero );
		const __m128i mask000f = _mm_slli_si128( ffff, 12 );
		const __m128i one = _mm_srli_epi32( _mm_slli_epi32( ffff, 25 ), 2 );
		const __m128i x = _mm_srli_si128( one, 12 );
		return { {_mm_castsi128_ps( x ), _mm_castsi128_ps( _mm_slli_si128( x, 4 ) ), _mm_castsi128_ps( _mm_slli_si128( x, 8 ) ), XE_SSE_SELECT_F( mask000f, _mm_castsi128_ps( one ), _v )} };
	}

	XE_INLINE simd4x4 simd4x4::Scaling( const simd4f & _v )
	{
		const __m128i zero = _mm_setzero_si128();
		const __m128i ffff = _mm_cmpeq_epi32( zero, zero );
		const __m128i if000 = _mm_srli_si128( ffff, 12 );
		const __m128i ione = _mm_srli_epi32( _mm_slli_epi32( ffff, 25 ), 2 );
		return { {_mm_and_ps( _v, _mm_castsi128_ps( if000 ) ), _mm_and_ps( _v, _mm_castsi128_ps( _mm_slli_si128( if000, 4 ) ) ), _mm_and_ps( _v, _mm_castsi128_ps( _mm_slli_si128( if000, 8 ) ) ), _mm_castsi128_ps( _mm_slli_si128( ione, 12 ) )} };
	}

	XE_INLINE simd4x4 simd4x4::Translate( const simd4x4 & _m, const simd4f & _v )
	{
		const __m128 a01 = XE_MADD( _m.cols[0], XE_SSE_SPLAT_F( _v, 0 ), _mm_mul_ps( _m.cols[1], XE_SSE_SPLAT_F( _v, 1 ) ) );
		const __m128 m3 = XE_MADD( _m.cols[2], XE_SSE_SPLAT_F( _v, 2 ), _m.cols[3] );
		return { {_m.cols[0], _m.cols[1], _m.cols[2], _mm_add_ps( a01, m3 )} };
	}

	XE_INLINE simd4x4 simd4x4::Scale( const simd4x4 & _m, const simd4f & _v )
	{
		return { {_mm_mul_ps( _m.cols[0], XE_SSE_SPLAT_F( _v, 0 ) ), _mm_mul_ps( _m.cols[1], XE_SSE_SPLAT_F( _v, 1 ) ), _mm_mul_ps( _m.cols[2], XE_SSE_SPLAT_F( _v, 2 ) ), _m.cols[3]} };
	}

	XE_INLINE simd4x4 simd4x4::ColumnMultiply( const simd4x4 & _m, const simd4f & _v )
	{
		return { {_mm_mul_ps( _m.cols[0], _v ), _mm_mul_ps( _m.cols[1], _v ), _mm_mul_ps( _m.cols[2], _v ), _mm_mul_ps( _m.cols[3], _v )} };
	}

	XE_INLINE simd4i simd4x4::IsNormalized( const simd4x4 & _m )
	{
		const __m128 max = _mm_set_ps1( 1.f + 1e-6f );
		const __m128 min = _mm_set_ps1( 1.f - 1e-6f );

		const __m128 tmp0 = _mm_unpacklo_ps( _m.cols[0], _m.cols[2] );
		const __m128 tmp1 = _mm_unpacklo_ps( _m.cols[1], _m.cols[3] );
		const __m128 tmp2 = _mm_unpackhi_ps( _m.cols[0], _m.cols[2] );
		const __m128 tmp3 = _mm_unpackhi_ps( _m.cols[1], _m.cols[3] );
		const __m128 row0 = _mm_unpacklo_ps( tmp0, tmp1 );
		const __m128 row1 = _mm_unpackhi_ps( tmp0, tmp1 );
		const __m128 row2 = _mm_unpacklo_ps( tmp2, tmp3 );

		const __m128 dot = XE_MADD( row0, row0, XE_MADD( row1, row1, _mm_mul_ps( row2, row2 ) ) );
		const __m128 normalized = _mm_and_ps( _mm_cmplt_ps( dot, max ), _mm_cmpgt_ps( dot, min ) );
		return _mm_castps_si128( _mm_and_ps( normalized, _mm_castsi128_ps( simd4i::MaskFFF0() ) ) );
	}

	XE_INLINE simd4i simd4x4::IsNormalizedEst( const simd4x4 & _m )
	{
		const __m128 max = _mm_set_ps1( 1.f + 2e-3f );
		const __m128 min = _mm_set_ps1( 1.f - 2e-3f );

		const __m128 tmp0 = _mm_unpacklo_ps( _m.cols[0], _m.cols[2] );
		const __m128 tmp1 = _mm_unpacklo_ps( _m.cols[1], _m.cols[3] );
		const __m128 tmp2 = _mm_unpackhi_ps( _m.cols[0], _m.cols[2] );
		const __m128 tmp3 = _mm_unpackhi_ps( _m.cols[1], _m.cols[3] );
		const __m128 row0 = _mm_unpacklo_ps( tmp0, tmp1 );
		const __m128 row1 = _mm_unpackhi_ps( tmp0, tmp1 );
		const __m128 row2 = _mm_unpacklo_ps( tmp2, tmp3 );

		const __m128 dot = XE_MADD( row0, row0, XE_MADD( row1, row1, _mm_mul_ps( row2, row2 ) ) );

		const __m128 normalized = _mm_and_ps( _mm_cmplt_ps( dot, max ), _mm_cmpgt_ps( dot, min ) );

		return _mm_castps_si128( _mm_and_ps( normalized, _mm_castsi128_ps( simd4i::MaskFFF0() ) ) );
	}

	XE_INLINE simd4i simd4x4::IsOrthogonal( const simd4x4 & _m )
	{
		const __m128 max = _mm_set_ss( 1.f + 1e-6f );
		const __m128 min = _mm_set_ss( 1.f - 1e-6f );
		const __m128 zero = _mm_setzero_ps();

		const simd4f & cross = simd4f::NormalizeSafe3( simd4f::Cross3( _m.cols[0], _m.cols[1] ), zero );
		const simd4f & at = simd4f::NormalizeSafe3( _m.cols[2], zero );

		simd4f dot;
		XE_SSE_DOT3_F( cross, at, dot );
		__m128 dotx000 = _mm_move_ss( zero, dot );
		return _mm_castps_si128( _mm_and_ps( _mm_cmplt_ss( dotx000, max ), _mm_cmpgt_ss( dotx000, min ) ) );
	}

	XE_INLINE simd4f simd4x4::ToQuaternion( const simd4x4 & _m )
	{
		const __m128i zero = _mm_setzero_si128();
		const __m128i ffff = _mm_cmpeq_epi32( zero, zero );
		const __m128 half = _mm_set1_ps( 0.5f );
		const __m128i mask_f000 = _mm_srli_si128( ffff, 12 );
		const __m128i mask_000f = _mm_slli_si128( ffff, 12 );
		const __m128 one = _mm_castsi128_ps( _mm_srli_epi32( _mm_slli_epi32( ffff, 25 ), 2 ) );
		const __m128i mask_0f00 = _mm_slli_si128( mask_f000, 4 );
		const __m128i mask_00f0 = _mm_slli_si128( mask_f000, 8 );

		const __m128 xx_yy = XE_SSE_SELECT_F( mask_0f00, _m.cols[1], _m.cols[0] );
		const __m128 xx_yy_0010 = XE_SHUFFLE_PS1( xx_yy, _MM_SHUFFLE( 0, 0, 1, 0 ) );
		const __m128 xx_yy_zz_xx = XE_SSE_SELECT_F( mask_00f0, _m.cols[2], xx_yy_0010 );
		const __m128 yy_zz_xx_yy = XE_SHUFFLE_PS1( xx_yy_zz_xx, _MM_SHUFFLE( 1, 0, 2, 1 ) );
		const __m128 zz_xx_yy_zz = XE_SHUFFLE_PS1( xx_yy_zz_xx, _MM_SHUFFLE( 2, 1, 0, 2 ) );

		const __m128 diag_sum = _mm_add_ps( _mm_add_ps( xx_yy_zz_xx, yy_zz_xx_yy ), zz_xx_yy_zz );
		const __m128 diag_diff = _mm_sub_ps( _mm_sub_ps( xx_yy_zz_xx, yy_zz_xx_yy ), zz_xx_yy_zz );
		const __m128 radicand = _mm_add_ps( XE_SSE_SELECT_F( mask_000f, diag_sum, diag_diff ), one );
		const __m128 invSqrt = one / _mm_sqrt_ps( radicand );

		__m128 zy_xz_yx = XE_SSE_SELECT_F( mask_00f0, _m.cols[1], _m.cols[0] );
		zy_xz_yx = XE_SHUFFLE_PS1( zy_xz_yx, _MM_SHUFFLE( 0, 1, 2, 2 ) );
		zy_xz_yx = XE_SSE_SELECT_F( mask_0f00, XE_SSE_SPLAT_F( _m.cols[2], 0 ), zy_xz_yx );
		__m128 yz_zx_xy = XE_SSE_SELECT_F( mask_f000, _m.cols[1], _m.cols[0] );
		yz_zx_xy = XE_SHUFFLE_PS1( yz_zx_xy, _MM_SHUFFLE( 0, 0, 2, 0 ) );
		yz_zx_xy = XE_SSE_SELECT_F( mask_f000, XE_SSE_SPLAT_F( _m.cols[2], 1 ), yz_zx_xy );
		const __m128 sum = _mm_add_ps( zy_xz_yx, yz_zx_xy );
		const __m128 diff = _mm_sub_ps( zy_xz_yx, yz_zx_xy );
		const __m128 scale = _mm_mul_ps( invSqrt, half );

		const __m128 sum0 = XE_SHUFFLE_PS1( sum, _MM_SHUFFLE( 0, 1, 2, 0 ) );
		const __m128 sum1 = XE_SHUFFLE_PS1( sum, _MM_SHUFFLE( 0, 0, 0, 2 ) );
		const __m128 sum2 = XE_SHUFFLE_PS1( sum, _MM_SHUFFLE( 0, 0, 0, 1 ) );
		__m128 res0 = XE_SSE_SELECT_F( mask_000f, XE_SSE_SPLAT_F( diff, 0 ), sum0 );
		__m128 res1 = XE_SSE_SELECT_F( mask_000f, XE_SSE_SPLAT_F( diff, 1 ), sum1 );
		__m128 res2 = XE_SSE_SELECT_F( mask_000f, XE_SSE_SPLAT_F( diff, 2 ), sum2 );
		res0 = _mm_mul_ps( XE_SSE_SELECT_F( mask_f000, radicand, res0 ), XE_SSE_SPLAT_F( scale, 0 ) );
		res1 = _mm_mul_ps( XE_SSE_SELECT_F( mask_0f00, radicand, res1 ), XE_SSE_SPLAT_F( scale, 1 ) );
		res2 = _mm_mul_ps( XE_SSE_SELECT_F( mask_00f0, radicand, res2 ), XE_SSE_SPLAT_F( scale, 2 ) );
		__m128 res3 = _mm_mul_ps( XE_SSE_SELECT_F( mask_000f, radicand, diff ), XE_SSE_SPLAT_F( scale, 3 ) );

		const __m128 xx = XE_SSE_SPLAT_F( _m.cols[0], 0 );
		const __m128 yy = XE_SSE_SPLAT_F( _m.cols[1], 1 );
		const __m128 zz = XE_SSE_SPLAT_F( _m.cols[2], 2 );
		const __m128i cond0 = _mm_castps_si128( _mm_cmpgt_ps( yy, xx ) );
		const __m128i cond1 = _mm_castps_si128( _mm_and_ps( _mm_cmpgt_ps( zz, xx ), _mm_cmpgt_ps( zz, yy ) ) );
		const __m128i cond2 = _mm_castps_si128( _mm_cmpgt_ps( XE_SSE_SPLAT_F( diag_sum, 0 ), _mm_castsi128_ps( zero ) ) );
		__m128 res = XE_SSE_SELECT_F( cond0, res1, res0 );
		res = XE_SSE_SELECT_F( cond1, res2, res );
		res = XE_SSE_SELECT_F( cond2, res3, res );

		return res;
	}

	XE_INLINE bool simd4x4::ToAffine( const simd4x4 & _m, simd4f * _translation, simd4f * _quaternion, simd4f * _scale )
	{
		const __m128 zero = _mm_setzero_ps();
		const __m128 one = simd4f::One();
		const __m128i fff0 = simd4i::MaskFFF0();
		const __m128 max = _mm_set_ps1( 1e-16f );
		const __m128 min = _mm_set_ps1( -1e-16f );

		*_translation = XE_SSE_SELECT_F( fff0, _m.cols[3], one );

		const __m128 m_tmp0 = _mm_unpacklo_ps( _m.cols[0], _m.cols[2] );
		const __m128 m_tmp1 = _mm_unpacklo_ps( _m.cols[1], _m.cols[3] );
		const __m128 m_tmp2 = _mm_unpackhi_ps( _m.cols[0], _m.cols[2] );
		const __m128 m_tmp3 = _mm_unpackhi_ps( _m.cols[1], _m.cols[3] );
		const __m128 m_row0 = _mm_unpacklo_ps( m_tmp0, m_tmp1 );
		const __m128 m_row1 = _mm_unpackhi_ps( m_tmp0, m_tmp1 );
		const __m128 m_row2 = _mm_unpacklo_ps( m_tmp2, m_tmp3 );

		const __m128 dot = XE_MADD( m_row0, m_row0, XE_MADD( m_row1, m_row1, _mm_mul_ps( m_row2, m_row2 ) ) );
		const __m128 abs_scale = _mm_sqrt_ps( dot );

		const __m128 zero_axis = _mm_and_ps( _mm_cmplt_ps( dot, max ), _mm_cmpgt_ps( dot, min ) );

		simd4x4 orthonormal;
		XE::int32 mask = _mm_movemask_ps( zero_axis );
		if( mask & 1 )
		{
			if( mask & 6 )
			{
				return false;
			}
			orthonormal.cols[1] = _mm_div_ps( _m.cols[1], XE_SSE_SPLAT_F( abs_scale, 1 ) );
			orthonormal.cols[0] = simd4f::Normalize3( simd4f::Cross3( orthonormal.cols[1], _m.cols[2] ) );
			orthonormal.cols[2] = simd4f::Normalize3( simd4f::Cross3( orthonormal.cols[0], orthonormal.cols[1] ) );
		}
		else if( mask & 4 )
		{
			if( mask & 3 )
			{
				return false;
			}
			orthonormal.cols[0] = _mm_div_ps( _m.cols[0], XE_SSE_SPLAT_F( abs_scale, 0 ) );
			orthonormal.cols[2] = simd4f::Normalize3( simd4f::Cross3( orthonormal.cols[0], _m.cols[1] ) );
			orthonormal.cols[1] = simd4f::Normalize3( simd4f::Cross3( orthonormal.cols[2], orthonormal.cols[0] ) );
		}
		else
		{
			if( mask & 5 )
			{
				return false;
			}
			orthonormal.cols[2] = _mm_div_ps( _m.cols[2], XE_SSE_SPLAT_F( abs_scale, 2 ) );
			orthonormal.cols[1] = simd4f::Normalize3( simd4f::Cross3( orthonormal.cols[2], _m.cols[0] ) );
			orthonormal.cols[0] = simd4f::Normalize3( simd4f::Cross3( orthonormal.cols[1], orthonormal.cols[2] ) );
		}
		orthonormal.cols[3] = simd4f::WAxis();

		const __m128 o_tmp0 = _mm_unpacklo_ps( orthonormal.cols[0], orthonormal.cols[2] );
		const __m128 o_tmp1 = _mm_unpacklo_ps( orthonormal.cols[1], orthonormal.cols[3] );
		const __m128 o_tmp2 = _mm_unpackhi_ps( orthonormal.cols[0], orthonormal.cols[2] );
		const __m128 o_tmp3 = _mm_unpackhi_ps( orthonormal.cols[1], orthonormal.cols[3] );
		const __m128 o_row0 = _mm_unpacklo_ps( o_tmp0, o_tmp1 );
		const __m128 o_row1 = _mm_unpackhi_ps( o_tmp0, o_tmp1 );
		const __m128 o_row2 = _mm_unpacklo_ps( o_tmp2, o_tmp3 );

		const __m128 scale_dot = XE_MADD( o_row0, m_row0, XE_MADD( o_row1, m_row1, _mm_mul_ps( o_row2, m_row2 ) ) );

		const __m128i cond = _mm_castps_si128( _mm_cmpgt_ps( scale_dot, zero ) );
		const __m128 cfalse = _mm_sub_ps( zero, abs_scale );
		const __m128 scale = XE_SSE_SELECT_F( cond, abs_scale, cfalse );
		*_scale = XE_SSE_SELECT_F( fff0, scale, one );

		*_quaternion = ToQuaternion( orthonormal );
		return true;
	}

	XE_INLINE simd4x4 simd4x4::FromEuler( const simd4f & _v )
	{
		const __m128 cos = simd4f::Cos( _v );
		const __m128 sin = simd4f::Sin( _v );

		const XE::float32 cx = simd4f::GetX( cos );
		const XE::float32 sx = simd4f::GetX( sin );
		const XE::float32 cy = simd4f::GetY( cos );
		const XE::float32 sy = simd4f::GetY( sin );
		const XE::float32 cz = simd4f::GetZ( cos );
		const XE::float32 sz = simd4f::GetZ( sin );

		const XE::float32 sycz = sy * cz;
		const XE::float32 sysz = sy * sz;

		return { simd4f::Load( cx * cy, sx * sz - cx * sycz, cx * sysz + sx * cz, 0.f ),
							   simd4f::Load( sy, cy * cz, -cy * sz, 0.f ),
							   simd4f::Load( -sx * cy, sx * sycz + cx * sz, -sx * sysz + cx * cz, 0.f ),
							   simd4f::WAxis() };
	}

	XE_INLINE simd4x4 simd4x4::FromAxisAngle( const simd4f & _axis, const simd4f & _angle )
	{
		const __m128i zero = _mm_setzero_si128();
		const __m128i ffff = _mm_cmpeq_epi32( zero, zero );
		const __m128i ione = _mm_srli_epi32( _mm_slli_epi32( ffff, 25 ), 2 );
		const __m128 fff0 = _mm_castsi128_ps( _mm_srli_si128( ffff, 4 ) );
		const __m128 one = _mm_castsi128_ps( ione );
		const __m128 w_axis = _mm_castsi128_ps( _mm_slli_si128( ione, 12 ) );

		const __m128 sin = simd4f::SplatX( simd4f::SinX( _angle ) );
		const __m128 cos = simd4f::SplatX( simd4f::CosX( _angle ) );
		const __m128 one_minus_cos = _mm_sub_ps( one, cos );

		const __m128 v0 = _mm_mul_ps( _mm_mul_ps( one_minus_cos, XE_SHUFFLE_PS1( _axis, _MM_SHUFFLE( 3, 0, 2, 1 ) ) ), XE_SHUFFLE_PS1( _axis, _MM_SHUFFLE( 3, 1, 0, 2 ) ) );
		const __m128 r0 = _mm_add_ps( _mm_mul_ps( _mm_mul_ps( one_minus_cos, _axis ), _axis ), cos );
		const __m128 r1 = _mm_add_ps( _mm_mul_ps( sin, _axis ), v0 );
		const __m128 r2 = _mm_sub_ps( v0, _mm_mul_ps( sin, _axis ) );
		const __m128 r0fff0 = _mm_and_ps( r0, fff0 );
		const __m128 r1r22120 = _mm_shuffle_ps( r1, r2, _MM_SHUFFLE( 2, 1, 2, 0 ) );
		const __m128 v1 = XE_SHUFFLE_PS1( r1r22120, _MM_SHUFFLE( 0, 3, 2, 1 ) );
		const __m128 r1r20011 = _mm_shuffle_ps( r1, r2, _MM_SHUFFLE( 0, 0, 1, 1 ) );
		const __m128 v2 = XE_SHUFFLE_PS1( r1r20011, _MM_SHUFFLE( 2, 0, 2, 0 ) );

		const __m128 t0 = _mm_shuffle_ps( r0fff0, v1, _MM_SHUFFLE( 1, 0, 3, 0 ) );
		const __m128 t1 = _mm_shuffle_ps( r0fff0, v1, _MM_SHUFFLE( 3, 2, 3, 1 ) );
		return { XE_SHUFFLE_PS1( t0, _MM_SHUFFLE( 1, 3, 2, 0 ) ), XE_SHUFFLE_PS1( t1, _MM_SHUFFLE( 1, 3, 0, 2 ) ), _mm_shuffle_ps( v2, r0fff0, _MM_SHUFFLE( 3, 2, 1, 0 ) ), w_axis };
	}

	XE_INLINE simd4x4 simd4x4::FromQuaternion( const simd4f & _quaternion )
	{
		const __m128i zero = _mm_setzero_si128();
		const __m128i ffff = _mm_cmpeq_epi32( zero, zero );
		const __m128i ione = _mm_srli_epi32( _mm_slli_epi32( ffff, 25 ), 2 );
		const __m128 fff0 = _mm_castsi128_ps( _mm_srli_si128( ffff, 4 ) );
		const __m128 c1110 = _mm_castsi128_ps( _mm_srli_si128( ione, 4 ) );
		const __m128 w_axis = _mm_castsi128_ps( _mm_slli_si128( ione, 12 ) );

		const __m128 vsum = _mm_add_ps( _quaternion, _quaternion );
		const __m128 vms = _mm_mul_ps( _quaternion, vsum );

		const __m128 r0 = _mm_sub_ps( _mm_sub_ps( c1110, _mm_and_ps( XE_SHUFFLE_PS1( vms, _MM_SHUFFLE( 3, 0, 0, 1 ) ), fff0 ) ), _mm_and_ps( XE_SHUFFLE_PS1( vms, _MM_SHUFFLE( 3, 1, 2, 2 ) ), fff0 ) );
		const __m128 v0 = _mm_mul_ps( XE_SHUFFLE_PS1( _quaternion, _MM_SHUFFLE( 3, 1, 0, 0 ) ), XE_SHUFFLE_PS1( vsum, _MM_SHUFFLE( 3, 2, 1, 2 ) ) );
		const __m128 v1 = _mm_mul_ps( XE_SHUFFLE_PS1( _quaternion, _MM_SHUFFLE( 3, 3, 3, 3 ) ), XE_SHUFFLE_PS1( vsum, _MM_SHUFFLE( 3, 0, 2, 1 ) ) );

		const __m128 r1 = _mm_add_ps( v0, v1 );
		const __m128 r2 = _mm_sub_ps( v0, v1 );

		const __m128 r1r21021 = _mm_shuffle_ps( r1, r2, _MM_SHUFFLE( 1, 0, 2, 1 ) );
		const __m128 v2 = XE_SHUFFLE_PS1( r1r21021, _MM_SHUFFLE( 1, 3, 2, 0 ) );
		const __m128 r1r22200 = _mm_shuffle_ps( r1, r2, _MM_SHUFFLE( 2, 2, 0, 0 ) );
		const __m128 v3 = XE_SHUFFLE_PS1( r1r22200, _MM_SHUFFLE( 2, 0, 2, 0 ) );

		const __m128 q0 = _mm_shuffle_ps( r0, v2, _MM_SHUFFLE( 1, 0, 3, 0 ) );
		const __m128 q1 = _mm_shuffle_ps( r0, v2, _MM_SHUFFLE( 3, 2, 3, 1 ) );
		return { XE_SHUFFLE_PS1( q0, _MM_SHUFFLE( 1, 3, 2, 0 ) ),
							   XE_SHUFFLE_PS1( q1, _MM_SHUFFLE( 1, 3, 0, 2 ) ),
							   _mm_shuffle_ps( v3, r0, _MM_SHUFFLE( 3, 2, 1, 0 ) ),
							   w_axis };
	}

	XE_INLINE simd4x4 simd4x4::FromAffine( const simd4f & _translation, const simd4f & _quaternion, const simd4f & _scale )
	{
		const __m128i zero = _mm_setzero_si128();
		const __m128i ffff = _mm_cmpeq_epi32( zero, zero );
		const __m128i ione = _mm_srli_epi32( _mm_slli_epi32( ffff, 25 ), 2 );
		const __m128 fff0 = _mm_castsi128_ps( _mm_srli_si128( ffff, 4 ) );
		const __m128 c1110 = _mm_castsi128_ps( _mm_srli_si128( ione, 4 ) );

		const __m128 vsum = _mm_add_ps( _quaternion, _quaternion );
		const __m128 vms = _mm_mul_ps( _quaternion, vsum );

		const __m128 r0 = _mm_sub_ps( _mm_sub_ps( c1110, _mm_and_ps( XE_SHUFFLE_PS1( vms, _MM_SHUFFLE( 3, 0, 0, 1 ) ), fff0 ) ), _mm_and_ps( XE_SHUFFLE_PS1( vms, _MM_SHUFFLE( 3, 1, 2, 2 ) ), fff0 ) );
		const __m128 v0 = _mm_mul_ps( XE_SHUFFLE_PS1( _quaternion, _MM_SHUFFLE( 3, 1, 0, 0 ) ), XE_SHUFFLE_PS1( vsum, _MM_SHUFFLE( 3, 2, 1, 2 ) ) );
		const __m128 v1 = _mm_mul_ps( XE_SHUFFLE_PS1( _quaternion, _MM_SHUFFLE( 3, 3, 3, 3 ) ), XE_SHUFFLE_PS1( vsum, _MM_SHUFFLE( 3, 0, 2, 1 ) ) );

		const __m128 r1 = _mm_add_ps( v0, v1 );
		const __m128 r2 = _mm_sub_ps( v0, v1 );

		const __m128 r1r21021 = _mm_shuffle_ps( r1, r2, _MM_SHUFFLE( 1, 0, 2, 1 ) );
		const __m128 v2 = XE_SHUFFLE_PS1( r1r21021, _MM_SHUFFLE( 1, 3, 2, 0 ) );
		const __m128 r1r22200 = _mm_shuffle_ps( r1, r2, _MM_SHUFFLE( 2, 2, 0, 0 ) );
		const __m128 v3 = XE_SHUFFLE_PS1( r1r22200, _MM_SHUFFLE( 2, 0, 2, 0 ) );

		const __m128 q0 = _mm_shuffle_ps( r0, v2, _MM_SHUFFLE( 1, 0, 3, 0 ) );
		const __m128 q1 = _mm_shuffle_ps( r0, v2, _MM_SHUFFLE( 3, 2, 3, 1 ) );

		return { _mm_mul_ps( XE_SHUFFLE_PS1( q0, _MM_SHUFFLE( 1, 3, 2, 0 ) ), XE_SSE_SPLAT_F( _scale, 0 ) ),
			 _mm_mul_ps( XE_SHUFFLE_PS1( q1, _MM_SHUFFLE( 1, 3, 0, 2 ) ), XE_SSE_SPLAT_F( _scale, 1 ) ),
			 _mm_mul_ps( _mm_shuffle_ps( v3, r0, _MM_SHUFFLE( 3, 2, 1, 0 ) ), XE_SSE_SPLAT_F( _scale, 2 ) ),
			 _mm_movelh_ps( _translation, _mm_unpackhi_ps( _translation, c1110 ) ) };
	}

	XE_INLINE simd4f simd4x4::TransformPoint( const simd4x4 & _m, const simd4f & _v )
	{
		const __m128 xxxx = _mm_mul_ps( XE_SSE_SPLAT_F( _v, 0 ), _m.cols[0] );
		const __m128 a23 = XE_MADD( XE_SSE_SPLAT_F( _v, 2 ), _m.cols[2], _m.cols[3] );
		const __m128 a01 = XE_MADD( XE_SSE_SPLAT_F( _v, 1 ), _m.cols[1], xxxx );
		return _mm_add_ps( a01, a23 );
	}

	XE_INLINE simd4f simd4x4::TransformVector( const simd4x4 & _m, const simd4f & _v )
	{
		const __m128 xxxx = _mm_mul_ps( _m.cols[0], XE_SSE_SPLAT_F( _v, 0 ) );
		const __m128 zzzz = _mm_mul_ps( _m.cols[1], XE_SSE_SPLAT_F( _v, 1 ) );
		const __m128 a21 = XE_MADD( _m.cols[2], XE_SSE_SPLAT_F( _v, 2 ), xxxx );
		return _mm_add_ps( zzzz, a21 );
	}

}


XE_INLINE Simd::simd4f operator-( const Simd::simd4f _v )
{
	return _mm_sub_ps( _mm_setzero_ps(), _v );
}

XE_INLINE Simd::simd4f operator+( const Simd::simd4f _a, const Simd::simd4f _b )
{
	return _mm_add_ps( _a, _b );
}

XE_INLINE Simd::simd4f operator-( const Simd::simd4f _a, const Simd::simd4f _b )
{
	return _mm_sub_ps( _a, _b );
}

XE_INLINE Simd::simd4f operator*( const Simd::simd4f _a, const Simd::simd4f _b )
{
	return _mm_mul_ps( _a, _b );
}

XE_INLINE Simd::simd4f operator/( const Simd::simd4f _a, const Simd::simd4f _b )
{
	return _mm_div_ps( _a, _b );
}


XE_INLINE Simd::simd4f operator*( const Simd::simd4x4 & _m, const Simd::simd4f _v )
{
	const __m128 xxxx = _mm_mul_ps( XE_SSE_SPLAT_F( _v, 0 ), _m.cols[0] );
	const __m128 zzzz = _mm_mul_ps( XE_SSE_SPLAT_F( _v, 2 ), _m.cols[2] );
	const __m128 a01 = XE_MADD( XE_SSE_SPLAT_F( _v, 1 ), _m.cols[1], xxxx );
	const __m128 a23 = XE_MADD( XE_SSE_SPLAT_F( _v, 3 ), _m.cols[3], zzzz );
	return _mm_add_ps( a01, a23 );
}

XE_INLINE Simd::simd4x4 operator*( const Simd::simd4x4 & _a, const Simd::simd4x4 & _b )
{
	Simd::simd4x4 ret;
	{
		const __m128 xxxx = _mm_mul_ps( XE_SSE_SPLAT_F( _b.cols[0], 0 ), _a.cols[0] );
		const __m128 zzzz = _mm_mul_ps( XE_SSE_SPLAT_F( _b.cols[0], 2 ), _a.cols[2] );
		const __m128 a01 =
			XE_MADD( XE_SSE_SPLAT_F( _b.cols[0], 1 ), _a.cols[1], xxxx );
		const __m128 a23 =
			XE_MADD( XE_SSE_SPLAT_F( _b.cols[0], 3 ), _a.cols[3], zzzz );
		ret.cols[0] = _mm_add_ps( a01, a23 );
	}
	{
		const __m128 xxxx = _mm_mul_ps( XE_SSE_SPLAT_F( _b.cols[1], 0 ), _a.cols[0] );
		const __m128 zzzz = _mm_mul_ps( XE_SSE_SPLAT_F( _b.cols[1], 2 ), _a.cols[2] );
		const __m128 a01 =
			XE_MADD( XE_SSE_SPLAT_F( _b.cols[1], 1 ), _a.cols[1], xxxx );
		const __m128 a23 =
			XE_MADD( XE_SSE_SPLAT_F( _b.cols[1], 3 ), _a.cols[3], zzzz );
		ret.cols[1] = _mm_add_ps( a01, a23 );
	}
	{
		const __m128 xxxx = _mm_mul_ps( XE_SSE_SPLAT_F( _b.cols[2], 0 ), _a.cols[0] );
		const __m128 zzzz = _mm_mul_ps( XE_SSE_SPLAT_F( _b.cols[2], 2 ), _a.cols[2] );
		const __m128 a01 =
			XE_MADD( XE_SSE_SPLAT_F( _b.cols[2], 1 ), _a.cols[1], xxxx );
		const __m128 a23 =
			XE_MADD( XE_SSE_SPLAT_F( _b.cols[2], 3 ), _a.cols[3], zzzz );
		ret.cols[2] = _mm_add_ps( a01, a23 );
	}
	{
		const __m128 xxxx = _mm_mul_ps( XE_SSE_SPLAT_F( _b.cols[3], 0 ), _a.cols[0] );
		const __m128 zzzz = _mm_mul_ps( XE_SSE_SPLAT_F( _b.cols[3], 2 ), _a.cols[2] );
		const __m128 a01 =
			XE_MADD( XE_SSE_SPLAT_F( _b.cols[3], 1 ), _a.cols[1], xxxx );
		const __m128 a23 =
			XE_MADD( XE_SSE_SPLAT_F( _b.cols[3], 3 ), _a.cols[3], zzzz );
		ret.cols[3] = _mm_add_ps( a01, a23 );
	}
	return ret;
}

XE_INLINE Simd::simd4x4 operator+( const Simd::simd4x4 & _a, const Simd::simd4x4 & _b )
{
	return {
		{_mm_add_ps( _a.cols[0], _b.cols[0] ), _mm_add_ps( _a.cols[1], _b.cols[1] ),
		 _mm_add_ps( _a.cols[2], _b.cols[2] ), _mm_add_ps( _a.cols[3], _b.cols[3] )} };
}

XE_INLINE Simd::simd4x4 operator-( const Simd::simd4x4 & _a, const Simd::simd4x4 & _b )
{
	return {
		{_mm_sub_ps( _a.cols[0], _b.cols[0] ), _mm_sub_ps( _a.cols[1], _b.cols[1] ),
		 _mm_sub_ps( _a.cols[2], _b.cols[2] ), _mm_sub_ps( _a.cols[3], _b.cols[3] )} };
}

END_XE_NAMESPACE

#endif // SIMD_H__C98956B9_05A0_4CD7_82F2_2EB0D46FB152
