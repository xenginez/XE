/*!
 * \file   InvokeStack.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __INVOKESTACK_H__81F7580A_298D_4FB3_96F1_FCB02A73A54B
#define __INVOKESTACK_H__81F7580A_298D_4FB3_96F1_FCB02A73A54B

#include "Variant.h"

BEG_XE_NAMESPACE

class REFLECT_API InvokeStack
{
public:
	InvokeStack();

	~InvokeStack();

public:
	template< typename T, typename ...Types > void Push( T&& val, Types&&...args )
	{
		_Stack.push_back( std::forward<T>( val ) );

		Push( args... );
	}

	template< typename T > void Push( T&& val )
	{
		_Stack.push_back( std::forward<T>( val ) );
	}

	void Push( InvokeStack * val );

	void Push( const InvokeStack * val );

	void Push( InvokeStack & val );

	void Push( const InvokeStack & val );

public:
	template< typename T > T Pop()
	{
#if COMPILER == COMPILER_MSVC
		Variant var = _Stack.back();
		_Stack.pop_back();
#else
		Variant var = _Stack.front();
		_Stack.pop_front();
#endif

		return var.Value<T>();
	}

private:
	VariantDeque _Stack;
};

END_XE_NAMESPACE

#endif // __INVOKESTACK_H__81F7580A_298D_4FB3_96F1_FCB02A73A54B
