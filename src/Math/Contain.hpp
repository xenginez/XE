/*!
 * \file   Contain.hpp
 *
 * \author ZhengYuanQing
 * \date   2019/02/27
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __CONTAIN_HPP__C5672E74_223D_4040_8F5C_48E9BF64A822
#define __CONTAIN_HPP__C5672E74_223D_4040_8F5C_48E9BF64A822

#include "Type.h"

BEG_XE_NAMESPACE

template< typename _Ty, typename _Ty2 > class Contain
{
public:
	template< typename _Other, typename _Other2 >
	struct rebind
	{
		using other = Contain<_Other, _Other2>;
	};

public:
	bool operator()( const _Ty& val1, const _Ty2& val2 ) const
	{
		return false;
	}
};

END_XE_NAMESAPCE

#endif // __CONTAIN_HPP__C5672E74_223D_4040_8F5C_48E9BF64A822
