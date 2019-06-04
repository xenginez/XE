/*!
 * \file   ParameterType.hpp
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __PARAMETERTYPE_HPP__DD6460A4_04AB_4F79_8A04_4C4CF356BDC4
#define __PARAMETERTYPE_HPP__DD6460A4_04AB_4F79_8A04_4C4CF356BDC4

#include "IMetaInfo.h"

BEG_XE_NAMESPACE

using ParameterType = Array< IMetaInfoPtr >;

template< typename ... Types > struct TypeList;

template< typename T, typename ... Types > struct TypeList<T, Types...>
{
	static void Make( ParameterType * args )
	{
		args->push_back( MetaID<typename TypeTraits<T>::raw_t>::Get() );

		TypeList<Types...>::Make( args );
	}
};

template< typename T > struct TypeList<T>
{
	static void Make( ParameterType * args )
	{
		args->push_back( MetaID<typename TypeTraits<T>::raw_t>::Get() );
	}
};

template<> struct TypeList<>
{
	static void Make( ParameterType * args )
	{
	}
};

template< typename ... Types >ParameterType MakeParameterType()
{
	ParameterType ret;
	TypeList<Types...>::Make( &ret );
	return ret;
}

END_XE_NAMESPACE

#endif // __PARAMETERTYPE_HPP__DD6460A4_04AB_4F79_8A04_4C4CF356BDC4
