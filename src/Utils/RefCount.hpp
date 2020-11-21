/*!
 * \file	RefCount.hpp
 *
 * \author	ZhengYuanQing
 * \date	2020/11/21
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef REFCOUNT_HPP__DD17061B_54B3_48B1_9C2D_F31556C00ADE
#define REFCOUNT_HPP__DD17061B_54B3_48B1_9C2D_F31556C00ADE

#include "Type.h"

BEG_XE_NAMESPACE

template< typename T > class RefCount
{
public:
	using value_type = T;
	using inc_function_type = std::function< void( T * ) >;
	using dec_function_type = std::function< void( T * ) >;

public:
	RefCount()
		:_Inc( nullptr ), _Inc( nullptr ), _Dec( nullptr )
	{
	}

	RefCount( std::nullptr_t )
		:_Inc( nullptr ), _Inc( nullptr ), _Dec( nullptr )
	{
	}

	RefCount( value_type * val, const inc_function_type & inc, const dec_function_type & dec )
		:_Value( val ), _Inc( inc ), _Dec( dec )
	{
		_Inc( _Value );
	}

	RefCount( const RefCount & val )
		:_Value( val._Value ), _Inc( val._Inc ), _Dec( val._Dec )
	{
		_Inc( _Value );
	}

	~RefCount()
	{
		_Dec( _Value );
	}

public:
	RefCount & operator=( std::nullptr_t )
	{
		if( _Value )
		{
			_Dec( _Value );
		}

		_Inc = nullptr;
		_Dec = nullptr;
		_Value = nullptr;
	}

	RefCount & operator=( const RefCount & val )
	{
		if( _Value != nullptr )
		{
			_Dec( _Value );
		}

		_Value = val._Value;
		_Inc = val._Inc;
		_Dec = val._Dec;

		if( _Value )
		{
			_Inc( _Value );
		}

		return *this;
	}

	value_type & operator*()
	{
		return *get();
	}

	const value_type & operator*() const
	{
		return *get();
	}

	operator value_type & ()
	{
		return *get();
	}

	operator const value_type & () const
	{
		return *get();
	}

	value_type * operator->()
	{
		return get();
	}

	const value_type * operator->() const
	{
		return get();
	}

public:
	value_type * get()
	{
		return _Value;
	}

	const value_type * get() const
	{
		return _Value;
	}

private:
	value_type * _Value;
	inc_function_type _Inc;
	dec_function_type _Dec;
};

END_XE_NAMESPACE

#endif // REFCOUNT_HPP__DD17061B_54B3_48B1_9C2D_F31556C00ADE
