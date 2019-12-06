/*!
 * \file	TypeID.hpp
 *
 * \author	ZhengYuanQing
 * \date	2019/12/06
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef TYPEID_HPP__1C7147FB_7591_47E2_B804_CD182F01438A
#define TYPEID_HPP__1C7147FB_7591_47E2_B804_CD182F01438A

#include "Type.h"

BEG_XE_NAMESPACE

template< typename T > struct EnumID
{
	static IMetaEnumPtr Get( const T * val = nullptr )
	{
		return nullptr;
	}
};

template< typename T > struct ClassID
{
	static IMetaClassPtr Get( const T * val = nullptr )
	{
		if( val )
		{
			return val->GetMetaClass();
		}

		return T::GetMetaClassStatic();
	}
};

template< typename T > struct ClassID< XE::shared_ptr< T > >
{
	static IMetaClassPtr Get( const XE::shared_ptr< T > & val = nullptr )
	{
		if( val )
		{
			return val->GetMetaClass();
		}

		return T::GetMetaClassStatic();
	}
};

template< typename T > struct TypeID
{
	static IMetaTypePtr Get( const T * val = nullptr )
	{
		using raw_t = typename TypeTraits<T>::raw_t;

		return SP_CAST<IMetaType>( std::conditional_t< std::is_enum<raw_t>::value, EnumID<raw_t>, ClassID<raw_t>>::Get( val ) );
	}
};

template< typename T > struct TypeID< XE::shared_ptr< T > >
{
	static IMetaTypePtr Get( const XE::shared_ptr<T> & val = nullptr )
	{
		return TypeID<T>::Get( val.get() );
	}
};

END_XE_NAMESPACE

#endif // TYPEID_HPP__1C7147FB_7591_47E2_B804_CD182F01438A
