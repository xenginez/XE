#define Swizzle( a, x, y, z, w) ( __builtin_shuffle( a, (uint32x4_t){ x, y, z, w } ) )

float XE::SIMD::X( simd_t a )
{
	return vgetq_lane_f32( a, 0 );
}

float XE::SIMD::Y( simd_t a )
{
	return vgetq_lane_f32( a, 1 );
}

float XE::SIMD::Z( simd_t a )
{
	return vgetq_lane_f32( a, 2 );
}

float XE::SIMD::W( simd_t a )
{
	return vgetq_lane_f32( a, 3 );
}

void XE::SIMD::Stream( float * ptr, simd_t a )
{
	vst1q_f32( ptr, a );
}

XE::SIMD::simd_t XE::SIMD::Load( const float * ptr )
{
	return vld1q_f32( ptr );
}

XE::SIMD::simd_t XE::SIMD::Load( float x, float y, float z, float w )
{
	const float val[4] = { x, y, z, w };
	return Load( val );
}

XE::SIMD::simd_t XE::SIMD::Zero()
{
	return vdupq_n_f32( 0.0f );
}

XE::SIMD::simd_t XE::SIMD::Add( simd_t a, simd_t b )
{
	return vaddq_f32( a, b );
}

XE::SIMD::simd_t XE::SIMD::Sub( simd_t a, simd_t b )
{
	return vsubq_f32( a, b );
}

XE::SIMD::simd_t XE::SIMD::Mul( simd_t a, simd_t b )
{
	return vmulq_f32( a, b );
}

XE::SIMD::simd_t XE::SIMD::Div( simd_t a, simd_t b )
{
	const simd_t oneish = vreinterpretq_f32_s32( vdupq_n_s32( 0x3f800001 ) );
	const simd_t est = Rcp( b );
	const simd_t iter0 = Mul( a, est );
	const simd_t tmp1 = Nmsub( b, est, oneish );
	return Madd( tmp1, iter0, iter0 );
}

XE::SIMD::simd_t XE::SIMD::Rcp( simd_t a )
{
	return vrecpeq_f32( a );
}

XE::SIMD::simd_t XE::SIMD::Sqrt( simd_t a )
{
	const simd_t half = vdupq_n_f32( 0.5f );
	const simd_t one = vdupq_n_f32( 1.0f );
	const simd_t tmp0 = Rsqrt( a );
	const simd_t tmp1 = Mul( tmp0, a );
	const simd_t tmp2 = Mul( tmp1, half );
	const simd_t tmp3 = Nmsub( tmp0, tmp1, one );
	return Madd( tmp3, tmp2, tmp1 );
}

XE::SIMD::simd_t XE::SIMD::Rsqrt( simd_t a )
{
	return vrsqrteq_f32( a );
}

XE::SIMD::simd_t XE::SIMD::Dot3( simd_t a, simd_t b )
{
	const simd_t xyzw = Mul( a, b );
	const simd_t xxxx = Swizzle( xyzw, 0, 0, 0, 0 );
	const simd_t yyyy = Swizzle( xyzw, 1, 1, 1, 1 );
	const simd_t zzzz = Swizzle( xyzw, 2, 2, 2, 2 );
	const simd_t tmp1 = Add( xxxx, yyyy );
	return Add( zzzz, tmp1 );
}

XE::SIMD::simd_t XE::SIMD::Dot( simd_t a, simd_t b )
{
	const simd_t xyzw = Mul( a, b );
	const simd_t yzwx = Swizzle( xyzw, 1, 2, 3, 0 );
	const simd_t tmp0 = Add( xyzw, yzwx );
	const simd_t zwxy = Swizzle( tmp0, 2, 3, 0, 1 );
	return Add( tmp0, zwxy );
}

XE::SIMD::simd_t XE::SIMD::Cmpeq( simd_t a, simd_t b )
{
	return vreinterpretq_f32_u32( vceqq_f32( a, b ) );
}

XE::SIMD::simd_t XE::SIMD::Cmplt( simd_t a, simd_t b )
{
	return vreinterpretq_f32_u32( vcltq_f32( a, b ) );
}

XE::SIMD::simd_t XE::SIMD::Cmple( simd_t a, simd_t b )
{
	return vreinterpretq_f32_u32( vcleq_f32( a, b ) );
}

XE::SIMD::simd_t XE::SIMD::Cmpgt( simd_t a, simd_t b )
{
	return vreinterpretq_f32_u32( vcgtq_f32( a, b ) );
}

XE::SIMD::simd_t XE::SIMD::Cmpge( simd_t a, simd_t b )
{
	return vreinterpretq_f32_u32( vcgeq_f32( a, b ) );
}

XE::SIMD::simd_t XE::SIMD::Min( simd_t a, simd_t b )
{
	return vminq_f32( a, b );
}

XE::SIMD::simd_t XE::SIMD::Max( simd_t a, simd_t b )
{
	return vmaxq_f32( a, b );
}

XE::SIMD::simd_t XE::SIMD::And( simd_t a, simd_t b )
{
	const int32x4_t tmp0 = vreinterpretq_s32_f32( a );
	const int32x4_t tmp1 = vreinterpretq_s32_f32( b );
	const int32x4_t tmp2 = vandq_s32( tmp0, tmp1 );
	return vreinterpretq_f32_s32( tmp2 );
}

XE::SIMD::simd_t XE::SIMD::AndNot( simd_t a, simd_t b )
{
	const int32x4_t tmp0 = vreinterpretq_s32_f32( a );
	const int32x4_t tmp1 = vreinterpretq_s32_f32( b );
	const int32x4_t tmp2 = vbicq_s32( tmp0, tmp1 );
	return vreinterpretq_f32_s32( tmp2 );
}

XE::SIMD::simd_t XE::SIMD::Or( simd_t a, simd_t b )
{
	const int32x4_t tmp0 = vreinterpretq_s32_f32( a );
	const int32x4_t tmp1 = vreinterpretq_s32_f32( b );
	const int32x4_t tmp2 = vorrq_s32( tmp0, tmp1 );
	return vreinterpretq_f32_s32( tmp2 );
}

XE::SIMD::simd_t XE::SIMD::Xor( simd_t a, simd_t b )
{
	const int32x4_t tmp0 = vreinterpretq_s32_f32( a );
	const int32x4_t tmp1 = vreinterpretq_s32_f32( b );
	const int32x4_t tmp2 = veorq_s32( tmp0, tmp1 );
	return vreinterpretq_f32_s32( tmp2 );
}

XE::SIMD::simd_t XE::SIMD::Neg( simd_t a )
{
	return Sub( Zero(), a );
}

XE::SIMD::simd_t XE::SIMD::Madd( simd_t a, simd_t b, simd_t c )
{
	return Add( Mul( a, b ), c );
}

XE::SIMD::simd_t XE::SIMD::Nmsub( simd_t a, simd_t b, simd_t c )
{
	return Sub( c, Mul( a, b ) );
}

XE::SIMD::simd_t XE::SIMD::Selb( simd_t mask, simd_t a, simd_t b )
{
	return Or( And( a, mask ), AndNot( b, mask ) );
}

XE::SIMD::simd_t XE::SIMD::Abs( simd_t a )
{
	return Max( Neg( a ), a );
}

XE::SIMD::simd_t XE::SIMD::Clamp( simd_t a, simd_t min, simd_t max )
{
	return Max( Min( a, max ), min );
}

XE::SIMD::simd_t XE::SIMD::Lerp( simd_t a, simd_t b, simd_t s )
{
	return Madd( s, Sub( b, a ), a );
}

XE::SIMD::simd_t XE::SIMD::Cross3( simd_t a, simd_t b )
{
	const simd_t a_yzxw = Swizzle( a, 1, 2, 0, 3 );
	const simd_t b_yzxw = Swizzle( b, 1, 2, 0, 3 );
	const simd_t tmp0 = Mul( a, b_yzxw );
	const simd_t tmp1 = Nmsub( a_yzxw, b, tmp0 );
	const simd_t result = Swizzle( tmp1, 1, 2, 0, 3 );
}

XE::SIMD::simd_t XE::SIMD::Normalize3( simd_t a )
{
	return Mul( a, Rsqrt( Dot3( a, a ) ) );
}
