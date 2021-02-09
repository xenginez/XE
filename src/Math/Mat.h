/*!
 * \file	Mat.h
 *
 * \author	ZhengYuanQing
 * \date	2020/12/22
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef __MAT_H__265D4806_2D3D_4557_B44F_80A8A7ACE9F4
#define __MAT_H__265D4806_2D3D_4557_B44F_80A8A7ACE9F4

#include "Type.h"

BEG_XE_NAMESPACE

template< typename T, XE::uint64 R, XE::uint64 C > class alignas( 16 ) Mat
{
public:
	using value_type = T;
	static constexpr XE::uint64 row_size = R;
	static constexpr XE::uint64 col_size = C;
	static constexpr XE::uint64 value_size = row_size * col_size;

public:
	static const Mat< T, R, C > Zero;
	static const Mat< T, R, C > Identity;

public:
	union
	{
		value_type d[value_size];
		value_type m[row_size][col_size];
	};

public:
	Mat()
	{
		std::memset( d, 0, sizeof( value_type ) * value_size );
	}

	Mat( value_type * val )
	{
		std::memcpy( d, val, sizeof( value_type ) * value_size );
	}

	Mat( const Mat & val )
	{
		std::memcpy( d, val.d, sizeof( value_type ) * value_size );
	}

	template< typename U > Mat( const Mat< U, R, C > & val )
	{
		for( int i = 0; i < value_size; ++i )
		{
			d[i] = static_cast< value_type >( val.d[i] );
		}
	}

	Mat( std::initializer_list< value_type > val )
	{
		int i = 0;
		for( auto it = val.begin(); it != val.end(); ++it, ++i )
		{
			d[i] = *it;
		}
	}

public:
	Mat & operator = ( const Mat & val )
	{
		std::memcpy( d, val.d, sizeof( value_type ) * value_size );

		return *this;
	}

public:
	value_type * operator []( XE::uint64 val )
	{
		XE_ASSERT( val < row_size );

		return m[val];
	}

	const value_type * operator []( XE::uint64 val ) const
	{
		XE_ASSERT( val < row_size );

		return m[val];
	}
};

using Mat2x2f = XE::Mat< XE::float32, 2, 2 >;
using Mat2x3f = XE::Mat< XE::float32, 2, 3 >;
using Mat2x4f = XE::Mat< XE::float32, 2, 4 >;
using Mat3x2f = XE::Mat< XE::float32, 3, 2 >;
using Mat3x3f = XE::Mat< XE::float32, 3, 3 >;
using Mat3x4f = XE::Mat< XE::float32, 3, 4 >;
using Mat4x2f = XE::Mat< XE::float32, 4, 2 >;
using Mat4x3f = XE::Mat< XE::float32, 4, 3 >;
using Mat4x4f = XE::Mat< XE::float32, 4, 4 >;

using Mat2x2d = XE::Mat< XE::float64, 2, 2 >;
using Mat2x3d = XE::Mat< XE::float64, 2, 3 >;
using Mat2x4d = XE::Mat< XE::float64, 2, 4 >;
using Mat3x2d = XE::Mat< XE::float64, 3, 2 >;
using Mat3x3d = XE::Mat< XE::float64, 3, 3 >;
using Mat3x4d = XE::Mat< XE::float64, 3, 4 >;
using Mat4x2d = XE::Mat< XE::float64, 4, 2 >;
using Mat4x3d = XE::Mat< XE::float64, 4, 3 >;
using Mat4x4d = XE::Mat< XE::float64, 4, 4 >;

DECL_META_CLASS( XE_API, Mat2x2f );
DECL_META_CLASS( XE_API, Mat2x3f );
DECL_META_CLASS( XE_API, Mat2x4f );
DECL_META_CLASS( XE_API, Mat3x2f );
DECL_META_CLASS( XE_API, Mat3x3f );
DECL_META_CLASS( XE_API, Mat3x4f );
DECL_META_CLASS( XE_API, Mat4x2f );
DECL_META_CLASS( XE_API, Mat4x3f );
DECL_META_CLASS( XE_API, Mat4x4f );

DECL_META_CLASS( XE_API, Mat2x2d );
DECL_META_CLASS( XE_API, Mat2x3d );
DECL_META_CLASS( XE_API, Mat2x4d );
DECL_META_CLASS( XE_API, Mat3x2d );
DECL_META_CLASS( XE_API, Mat3x3d );
DECL_META_CLASS( XE_API, Mat3x4d );
DECL_META_CLASS( XE_API, Mat4x2d );
DECL_META_CLASS( XE_API, Mat4x3d );
DECL_META_CLASS( XE_API, Mat4x4d );

END_XE_NAMESPACE


template<> const XE::Mat< XE::float32, 2, 2 > XE::Mat< XE::float32, 2, 2 >::Zero = {
	0, 0,
	0, 0 };
template<> const XE::Mat< XE::float32, 2, 2 > XE::Mat< XE::float32, 2, 2 >::Identity = {
	1, 0,
	0, 1 };
template<> const XE::Mat< XE::float32, 2, 3 > XE::Mat< XE::float32, 2, 3 >::Zero = {
	0, 0, 0,
	0, 0, 0 };
template<> const XE::Mat< XE::float32, 2, 3 > XE::Mat< XE::float32, 2, 3 >::Identity = {
	1, 0, 0,
	0, 1, 0 };
template<> const XE::Mat< XE::float32, 2, 4 > XE::Mat< XE::float32, 2, 4 >::Zero = {
	0, 0, 0, 0,
	0, 0, 0, 0 };
template<> const XE::Mat< XE::float32, 2, 4 > XE::Mat< XE::float32, 2, 4 >::Identity = {
	1, 0, 0, 0,
	0, 1, 0, 0 };
template<> const XE::Mat< XE::float32, 3, 2 > XE::Mat< XE::float32, 3, 2 >::Zero = {
	0, 0,
	0, 0,
	0, 0 };
template<> const XE::Mat< XE::float32, 3, 2 > XE::Mat< XE::float32, 3, 2 >::Identity = {
	1, 0,
	0, 1,
	0, 0 };
template<> const XE::Mat< XE::float32, 3, 3 > XE::Mat< XE::float32, 3, 3 >::Zero = {
	0, 0, 0,
	0, 0, 0,
	0, 0, 0 };
template<> const XE::Mat< XE::float32, 3, 3 > XE::Mat< XE::float32, 3, 3 >::Identity = {
	1, 0, 0,
	0, 1, 0,
	0, 0, 1 };
template<> const XE::Mat< XE::float32, 3, 4 > XE::Mat< XE::float32, 3, 4 >::Zero = {
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0 };
template<> const XE::Mat< XE::float32, 3, 4 > XE::Mat< XE::float32, 3, 4 >::Identity = {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0 };
template<> const XE::Mat< XE::float32, 4, 2 > XE::Mat< XE::float32, 4, 2 >::Zero = {
	0, 0,
	0, 0,
	0, 0,
	0, 0 };
template<> const XE::Mat< XE::float32, 4, 2 > XE::Mat< XE::float32, 4, 2 >::Identity = {
	1, 0,
	0, 1,
	0, 0,
	0, 0 };
template<> const XE::Mat< XE::float32, 4, 3 > XE::Mat< XE::float32, 4, 3 >::Zero = {
	0, 0, 0,
	0, 0, 0,
	0, 0, 0,
	0, 0, 0 };
template<> const XE::Mat< XE::float32, 4, 3 > XE::Mat< XE::float32, 4, 3 >::Identity = {
	1, 0, 0,
	0, 1, 0,
	0, 0, 1,
	0, 0, 0 };
template<> const XE::Mat< XE::float32, 4, 4 > XE::Mat< XE::float32, 4, 4 >::Zero = {
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0 };
template<> const XE::Mat< XE::float32, 4, 4 > XE::Mat< XE::float32, 4, 4 >::Identity = {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1 };


template<> const XE::Mat< XE::float64, 2, 2 > XE::Mat< XE::float64, 2, 2 >::Zero = {
	0, 0,
	0, 0 };
template<> const XE::Mat< XE::float64, 2, 2 > XE::Mat< XE::float64, 2, 2 >::Identity = {
	1, 0,
	0, 1 };
template<> const XE::Mat< XE::float64, 2, 3 > XE::Mat< XE::float64, 2, 3 >::Zero = {
	0, 0, 0,
	0, 0, 0 };
template<> const XE::Mat< XE::float64, 2, 3 > XE::Mat< XE::float64, 2, 3 >::Identity = {
	1, 0, 0,
	0, 1, 0 };
template<> const XE::Mat< XE::float64, 2, 4 > XE::Mat< XE::float64, 2, 4 >::Zero = {
	0, 0, 0, 0,
	0, 0, 0, 0 };
template<> const XE::Mat< XE::float64, 2, 4 > XE::Mat< XE::float64, 2, 4 >::Identity = {
	1, 0, 0, 0,
	0, 1, 0, 0 };
template<> const XE::Mat< XE::float64, 3, 2 > XE::Mat< XE::float64, 3, 2 >::Zero = {
	0, 0,
	0, 0,
	0, 0 };
template<> const XE::Mat< XE::float64, 3, 2 > XE::Mat< XE::float64, 3, 2 >::Identity = {
	1, 0,
	0, 1,
	0, 0 };
template<> const XE::Mat< XE::float64, 3, 3 > XE::Mat< XE::float64, 3, 3 >::Zero = {
	0, 0, 0,
	0, 0, 0,
	0, 0, 0 };
template<> const XE::Mat< XE::float64, 3, 3 > XE::Mat< XE::float64, 3, 3 >::Identity = {
	1, 0, 0,
	0, 1, 0,
	0, 0, 1 };
template<> const XE::Mat< XE::float64, 3, 4 > XE::Mat< XE::float64, 3, 4 >::Zero = {
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0 };
template<> const XE::Mat< XE::float64, 3, 4 > XE::Mat< XE::float64, 3, 4 >::Identity = {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0 };
template<> const XE::Mat< XE::float64, 4, 2 > XE::Mat< XE::float64, 4, 2 >::Zero = {
	0, 0,
	0, 0,
	0, 0,
	0, 0 };
template<> const XE::Mat< XE::float64, 4, 2 > XE::Mat< XE::float64, 4, 2 >::Identity = {
	1, 0,
	0, 1,
	0, 0,
	0, 0 };
template<> const XE::Mat< XE::float64, 4, 3 > XE::Mat< XE::float64, 4, 3 >::Zero = {
	0, 0, 0,
	0, 0, 0,
	0, 0, 0,
	0, 0, 0 };
template<> const XE::Mat< XE::float64, 4, 3 > XE::Mat< XE::float64, 4, 3 >::Identity = {
	1, 0, 0,
	0, 1, 0,
	0, 0, 1,
	0, 0, 0 };
template<> const XE::Mat< XE::float64, 4, 4 > XE::Mat< XE::float64, 4, 4 >::Zero = {
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0 };
template<> const XE::Mat< XE::float64, 4, 4 > XE::Mat< XE::float64, 4, 4 >::Identity = {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1 };

#endif // __MAT_H__265D4806_2D3D_4557_B44F_80A8A7ACE9F4
