#define Swizzle( a, x, y, z, w) ( _mm_shuffle_ps( a, a, _MM_SHUFFLE( x, y, z, w ) ) )

XE::real XE::SIMD::X( XE::SIMD::simd_t a )
{
	return _mm_cvtss_f32( a );
}

XE::real XE::SIMD::Y( XE::SIMD::simd_t a )
{
	const XE::SIMD::simd_t yyyy = Swizzle( a, 1, 1, 1, 1 );
	return _mm_cvtss_f32( yyyy );
}

XE::real XE::SIMD::Z( XE::SIMD::simd_t a )
{
	const XE::SIMD::simd_t zzzz = Swizzle( a, 2, 2, 2, 2 );
	return _mm_cvtss_f32( zzzz );
}

XE::real XE::SIMD::W( XE::SIMD::simd_t a )
{
	const XE::SIMD::simd_t wwww = Swizzle( a, 3, 3, 3, 3 );
	return _mm_cvtss_f32( wwww );
}

void XE::SIMD::Stream( XE::real * ptr, XE::SIMD::simd_t a )
{
	_mm_stream_ps( ptr, a );
}

XE::SIMD::simd_t XE::SIMD::Load( const XE::real * ptr )
{
	return _mm_load_ps( ptr );
}

XE::SIMD::simd_t XE::SIMD::Load( XE::real x, XE::real y, XE::real z, XE::real w )
{
	return _mm_set_ps( w, z, y, x );
}

XE::SIMD::simd_t XE::SIMD::Zero()
{
	return _mm_setzero_ps();
}

XE::SIMD::simd_t XE::SIMD::Add( XE::SIMD::simd_t a, XE::SIMD::simd_t b )
{
	return _mm_add_ps( a, b );
}

XE::SIMD::simd_t XE::SIMD::Sub( XE::SIMD::simd_t a, XE::SIMD::simd_t b )
{
	return _mm_sub_ps( a, b );
}

XE::SIMD::simd_t XE::SIMD::Mul( XE::SIMD::simd_t a, XE::SIMD::simd_t b )
{
	return _mm_mul_ps( a, b );
}

XE::SIMD::simd_t XE::SIMD::Div( XE::SIMD::simd_t a, XE::SIMD::simd_t b )
{
	return _mm_div_ps( a, b );
}

XE::SIMD::simd_t XE::SIMD::Rcp( XE::SIMD::simd_t a )
{
	return _mm_rcp_ps( a );
}

XE::SIMD::simd_t XE::SIMD::Sqrt( XE::SIMD::simd_t a )
{
	return _mm_sqrt_ps( a );
}

XE::SIMD::simd_t XE::SIMD::Rsqrt( XE::SIMD::simd_t a )
{
	return _mm_rsqrt_ps( a );
}

XE::SIMD::simd_t XE::SIMD::Dot3( XE::SIMD::simd_t a, XE::SIMD::simd_t b )
{
	const XE::SIMD::simd_t xyzw = Mul( a, b );
	const XE::SIMD::simd_t xxxx = Swizzle( xyzw, 0, 0, 0, 0 );
	const XE::SIMD::simd_t yyyy = Swizzle( xyzw, 1, 1, 1, 1 );
	const XE::SIMD::simd_t zzzz = Swizzle( xyzw, 2, 2, 2, 2 );
	const XE::SIMD::simd_t tmp1 = Add( xxxx, yyyy );
	return Add( zzzz, tmp1 );
}

XE::SIMD::simd_t XE::SIMD::Dot( XE::SIMD::simd_t a, XE::SIMD::simd_t b )
{
	const XE::SIMD::simd_t xyzw = Mul( a, b );
	const XE::SIMD::simd_t yzwx = Swizzle( xyzw, 1, 2, 3, 0 );
	const XE::SIMD::simd_t tmp0 = Add( xyzw, yzwx );
	const XE::SIMD::simd_t zwxy = Swizzle( tmp0, 2, 3, 0, 1 );
	return Add( tmp0, zwxy );
}

XE::SIMD::simd_t XE::SIMD::Cmpeq( XE::SIMD::simd_t a, XE::SIMD::simd_t b )
{
	return _mm_cmpeq_ps( a, b );
}

XE::SIMD::simd_t XE::SIMD::Cmplt( XE::SIMD::simd_t a, XE::SIMD::simd_t b )
{
	return _mm_cmplt_ps( a, b );
}

XE::SIMD::simd_t XE::SIMD::Cmple( XE::SIMD::simd_t a, XE::SIMD::simd_t b )
{
	return _mm_cmple_ps( a, b );
}

XE::SIMD::simd_t XE::SIMD::Cmpgt( XE::SIMD::simd_t a, XE::SIMD::simd_t b )
{
	return _mm_cmpgt_ps( a, b );
}

XE::SIMD::simd_t XE::SIMD::Cmpge( XE::SIMD::simd_t a, XE::SIMD::simd_t b )
{
	return _mm_cmpge_ps( a, b );
}

XE::SIMD::simd_t XE::SIMD::Min( XE::SIMD::simd_t a, XE::SIMD::simd_t b )
{
	return _mm_min_ps( a, b );
}

XE::SIMD::simd_t XE::SIMD::Max( XE::SIMD::simd_t a, XE::SIMD::simd_t b )
{
	return _mm_max_ps( a, b );
}

XE::SIMD::simd_t XE::SIMD::And( XE::SIMD::simd_t a, XE::SIMD::simd_t b )
{
	return _mm_and_ps( a, b );
}

XE::SIMD::simd_t XE::SIMD::AndNot( XE::SIMD::simd_t a, XE::SIMD::simd_t b )
{
	return _mm_andnot_ps( b, a );
}

XE::SIMD::simd_t XE::SIMD::Or( XE::SIMD::simd_t a, XE::SIMD::simd_t b )
{
	return _mm_or_ps( a, b );
}

XE::SIMD::simd_t XE::SIMD::Xor( XE::SIMD::simd_t a, XE::SIMD::simd_t b )
{
	return _mm_xor_ps( a, b );
}

XE::SIMD::simd_t XE::SIMD::Neg( XE::SIMD::simd_t a )
{
	return Sub( Zero(), a );
}

XE::SIMD::simd_t XE::SIMD::Madd( XE::SIMD::simd_t a, XE::SIMD::simd_t b, XE::SIMD::simd_t c )
{
	return Add( Mul( a, b ), c );
}

XE::SIMD::simd_t XE::SIMD::Nmsub( XE::SIMD::simd_t a, XE::SIMD::simd_t b, XE::SIMD::simd_t c )
{
	return Sub( c, Mul( a, b ) );
}

XE::SIMD::simd_t XE::SIMD::Selb( XE::SIMD::simd_t mask, XE::SIMD::simd_t a, XE::SIMD::simd_t b )
{
	return Or( And( a, mask ), AndNot( b, mask ) );
}

XE::SIMD::simd_t XE::SIMD::Abs( XE::SIMD::simd_t a )
{
	return Max( Neg( a ), a );
}

XE::SIMD::simd_t XE::SIMD::Clamp( XE::SIMD::simd_t a, XE::SIMD::simd_t min, XE::SIMD::simd_t max )
{
	return Max( Min( a, min ), max );
}

XE::SIMD::simd_t XE::SIMD::Lerp( XE::SIMD::simd_t a, XE::SIMD::simd_t b, XE::SIMD::simd_t s )
{
	return Madd( s, Sub( b, a ), a );
}

XE::SIMD::simd_t XE::SIMD::Cross3( XE::SIMD::simd_t a, XE::SIMD::simd_t b )
{
	const XE::SIMD::simd_t a_yzxw = Swizzle( a, 1, 2, 0, 4 );
	const XE::SIMD::simd_t b_yzxw = Swizzle( b, 1, 2, 0, 4 );
	const XE::SIMD::simd_t tmp0 = Mul( a, b_yzxw );
	const XE::SIMD::simd_t tmp1 = Nmsub( a_yzxw, b, tmp0 );
	return Swizzle( tmp1, 1, 2, 0, 4 );
}

XE::SIMD::simd_t XE::SIMD::Normalize3( XE::SIMD::simd_t a )
{
	return Mul( a, Rsqrt( Dot3( a, a ) ) );
}
