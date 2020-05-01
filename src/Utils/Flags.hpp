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

template< typename T > class Flags
{
	static_assert( std::is_enum_v<T> );

public:
	Flags( T val )
		:_Value( reinterpret_cast< XE::int64 >( val ) )
	{

	}

	Flags( const Flags & val )
		:_Value( val._Value )
	{

	}

public:
	Flags operator |( T val ) const
	{
		_Value |= reinterpret_cast< XE::int64 >( val );

		return *this;
	}

	Flags operator |( const Flags & val ) const
	{
		_Value |= val._Value;

		return *this;
	}

	Flags operator &( T val ) const
	{
		_Value &= reinterpret_cast< XE::int64 >( val );

		return *this;
	}

	Flags operator &( const Flags & val ) const
	{
		_Value &= val._Value;

		return *this;
	}

public:
	Flags & operator =( T val )
	{
		_Value = reinterpret_cast< XE::int64 >( val );

		return *this;
	}

	Flags & operator =( const Flags & val )
	{
		_Value = val._Value;

		return *this;
	}

	Flags & operator |=( T val )
	{
		_Value |= reinterpret_cast< XE::int64 >( val );

		return *this;
	}

	Flags & operator |=( const Flags & val )
	{
		_Value |= val._Value;

		return *this;
	}

	Flags & operator &=( T val )
	{
		_Value &= reinterpret_cast< XE::int64 >( val );

		return *this;
	}

	Flags & operator &=( const Flags & val )
	{
		_Value &= val._Value;

		return *this;
	}

public:
	bool operator ||( T val ) const
	{
		return ( _Value | reinterpret_cast< XE::int64 >( val ) ) != 0;
	}

	bool operator ||( const Flags & val ) const
	{
		return ( _Value | val._Value ) != 0;
	}

	bool operator &&( T val ) const
	{
		return ( _Value & reinterpret_cast< XE::int64 >( val ) ) != 0;
	}

	bool operator &&( const Flags & val ) const
	{
		return ( _Value & val._Value ) != 0;
	}

	bool operator ==( T val ) const
	{
		return _Value == reinterpret_cast< XE::int64 >( val );
	}

	bool operator ==( const Flags & val ) const
	{
		return _Value == val._Value;
	}

	bool operator !=( T val ) const
	{
		return _Value != reinterpret_cast< XE::int64 >( val );
	}

	bool operator !=( const Flags & val ) const
	{
		return _Value != val._Value;
	}

private:
	XE::int64 _Value;
};

template< typename T > XE::Flags< T > MakeFlags( T arg0)
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

#endif // FLAGS_HPP__C8E5511D_71B9_46C1_A4BF_35B5E8ADBDF3
