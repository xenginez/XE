/*!
 * \file   Singleton.hpp
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __SINGLETON_HPP__4F8FE7B0_3EA0_4004_BB97_87DD466307DD
#define __SINGLETON_HPP__4F8FE7B0_3EA0_4004_BB97_87DD466307DD

#include "NonCopyable.hpp"

BEG_XE_NAMESPACE

template< typename T > class Singleton : public NonCopyable
{
protected:
	static T * This()
	{
		static T value;
		return &value;
	}
};

END_XE_NAMESPACE

#endif // __SINGLETON_HPP__4F8FE7B0_3EA0_4004_BB97_87DD466307DD
