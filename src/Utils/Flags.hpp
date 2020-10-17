/*!
 * \file	Flags.hpp
 *
 * \author	ZhengYuanQing
 * \date	2020/04/04
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef FLAGS_HPP__C8E5511D_71B9_46C1_A4BF_35B5E8ADBDF3
#define FLAGS_HPP__C8E5511D_71B9_46C1_A4BF_35B5E8ADBDF3

#include "Type.h"

BEG_XE_NAMESPACE

template< typename T, typename V = XE::uint64 > class Flags
{
public:
	using enum_type = T;
	using value_type = V;

public:
	Flags()
		:_Value( 0 )
	{

	}

	Flags( enum_type val )
		:_Value( static_cast< value_type >( val ) )
	{

	}

	Flags( value_type val )
		:_Value( val )
	{

	}

	Flags( const Flags & val )
		:_Value( val._Value )
	{

	}

public:
	Flags operator |( enum_type val ) const
	{
		return _Value | static_cast< value_type >( val );
	}

	Flags operator |( const Flags & val ) const
	{
		return _Value | val._Value;
	}

	Flags operator &( enum_type val ) const
	{
		return _Value & static_cast< value_type >( val );
	}

	Flags operator &( const Flags & val ) const
	{
		return _Value & val._Value;
	}

	Flags operator << ( enum_type val ) const
	{
		return _Value << static_cast< value_type >( val );
	}

	Flags operator << ( const Flags & val ) const
	{
		return _Value << val._Value;
	}

	Flags operator >> ( enum_type val ) const
	{
		return _Value >> static_cast< value_type >( val );
	}

	Flags operator >> ( const Flags & val ) const
	{
		return _Value >> val._Value;
	}

public:
	Flags & operator =( enum_type val )
	{
		_Value = static_cast< value_type >( val );

		return *this;
	}

	Flags & operator =( const Flags & val )
	{
		_Value = val._Value;

		return *this;
	}

	Flags & operator |=( enum_type val )
	{
		_Value |= static_cast< value_type >( val );

		return *this;
	}

	Flags & operator |=( const Flags & val )
	{
		_Value |= val._Value;

		return *this;
	}

	Flags & operator &=( enum_type val )
	{
		_Value &= static_cast< value_type >( val );

		return *this;
	}

	Flags & operator &=( const Flags & val )
	{
		_Value &= val._Value;

		return *this;
	}

public:
	bool operator ||( enum_type val ) const
	{
		return ( _Value | static_cast< value_type >( val ) ) != 0;
	}

	bool operator ||( const Flags & val ) const
	{
		return ( _Value | val._Value ) != 0;
	}

	bool operator &&( enum_type val ) const
	{
		return ( _Value & static_cast< value_type >( val ) ) != 0;
	}

	bool operator &&( const Flags & val ) const
	{
		return ( _Value & val._Value ) != 0;
	}

	bool operator ==( enum_type val ) const
	{
		return _Value == static_cast< value_type >( val );
	}

	bool operator ==( const Flags & val ) const
	{
		return _Value == val._Value;
	}

	bool operator !=( enum_type val ) const
	{
		return _Value != static_cast< value_type >( val );
	}

	bool operator !=( const Flags & val ) const
	{
		return _Value != val._Value;
	}

public:
	value_type GetValue() const
	{
		return _Value;
	}

private:
	value_type _Value;
};

template< typename T > XE::Flags< T > MakeFlags( T arg0 )
{
	XE::Flags< T > flags( arg0 );

	return flags;
}

template< typename T > XE::Flags< T > MakeFlags( T arg0, T arg1 )
{
	XE::Flags< T > flags( arg0 );

	return flags | arg1;
}

template< typename T > XE::Flags< T > MakeFlags( T arg0, T arg1, T arg2 )
{
	XE::Flags< T > flags( arg0 );

	return flags | arg1 | arg2;
}

template< typename T > XE::Flags< T > MakeFlags( T arg0, T arg1, T arg2, T arg3 )
{
	XE::Flags< T > flags( arg0 );

	return flags | arg1 | arg2 | arg3;
}

template< typename T > XE::Flags< T > MakeFlags( T arg0, T arg1, T arg2, T arg3, T arg4 )
{
	XE::Flags< T > flags( arg0 );

	return flags | arg1 | arg2 | arg3 | arg4;
}

template< typename T > XE::Flags< T > MakeFlags( T arg0, T arg1, T arg2, T arg3, T arg4, T arg5 )
{
	XE::Flags< T > flags( arg0 );

	return flags | arg1 | arg2 | arg3 | arg4 | arg5;
}

template< typename T > XE::Flags< T > MakeFlags( T arg0, T arg1, T arg2, T arg3, T arg4, T arg5, T arg6 )
{
	XE::Flags< T > flags( arg0 );

	return flags | arg1 | arg2 | arg3 | arg4 | arg5 | arg6;
}

template< typename T > XE::Flags< T > MakeFlags( T arg0, T arg1, T arg2, T arg3, T arg4, T arg5, T arg6, T arg7 )
{
	XE::Flags< T > flags( arg0 );

	return flags | arg1 | arg2 | arg3 | arg4 | arg5 | arg6 | arg7;
}

template< typename T > XE::Flags< T > MakeFlags( T arg0, T arg1, T arg2, T arg3, T arg4, T arg5, T arg6, T arg7, T arg8 )
{
	XE::Flags< T > flags( arg0 );

	return flags | arg1 | arg2 | arg3 | arg4 | arg5 | arg6 | arg7 | arg8;
}

template< typename T > XE::Flags< T > MakeFlags( T arg0, T arg1, T arg2, T arg3, T arg4, T arg5, T arg6, T arg7, T arg8, T arg9 )
{
	XE::Flags< T > flags( arg0 );

	return flags | arg1 | arg2 | arg3 | arg4 | arg5 | arg6 | arg7 | arg8 | arg9;
}

END_XE_NAMESPACE

template< typename T > bool operator ||( T left, XE::Flags< T > right )
{
	return XE::MakeFlags( left ) || right;
}

template< typename T > bool operator &&( T left, XE::Flags< T > right )
{
	return XE::MakeFlags( left ) && right;
}

template< typename T > bool operator ==( T left, XE::Flags< T > right )
{
	return XE::MakeFlags( left ) == right;
}

template< typename T > bool operator !=( T left, XE::Flags< T > right )
{
	return XE::MakeFlags( left ) != right;
}

#define DECL_META_FLAGS( EXPORT, TYPE, NAME ) DECL_META_ENUM( EXPORT, TYPE ); using NAME = XE::Flags< TYPE >

#endif // FLAGS_HPP__C8E5511D_71B9_46C1_A4BF_35B5E8ADBDF3
