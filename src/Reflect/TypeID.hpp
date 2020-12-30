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

template< typename T > struct XE_EnumID
{
	static XE::IMetaEnumPtr Get( const T * val = nullptr )
	{
		return nullptr;
	}
};

template< typename T > struct XE_ClassID
{
	static XE::IMetaClassPtr Get( const T * val = nullptr )
	{
		if( val )
		{
			return val->GetMetaClass();
		}

		return T::GetMetaClassStatic();
	}
};

template< typename T > struct ::XE_ClassID< XE::SharedPtr< T > >
{
	static XE::IMetaClassPtr Get( const XE::SharedPtr< T > & val = nullptr )
	{
		if( val )
		{
			return val->GetMetaClass();
		}

		return T::GetMetaClassStatic();
	}
};

template< typename T > struct XE_TypeID
{
	static XE::IMetaTypePtr Get( const T * val = nullptr )
	{
		using raw_t = typename XE::TypeTraits<T>::raw_t;

		return SP_CAST< XE::IMetaType >( std::conditional_t< std::is_enum<raw_t>::value, XE_EnumID<raw_t>, ::XE_ClassID<raw_t>>::Get( val ) );
	}
};

template< typename T > struct XE_TypeID< XE::SharedPtr< T > >
{
	static XE::IMetaTypePtr Get( const XE::SharedPtr<T> * val = nullptr )
	{
		if( val != nullptr )
		{
			return XE_TypeID<T>::Get( val->get() );
		}

		return XE_TypeID<T>::Get();
	}

};

#endif // TYPEID_HPP__1C7147FB_7591_47E2_B804_CD182F01438A
