/*!
 * \file   MetaID.hpp
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __METAID_HPP__4D612830_3D3B_42A0_9441_7CECA63594CB
#define __METAID_HPP__4D612830_3D3B_42A0_9441_7CECA63594CB

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
		if (val)
		{
			return val->GetMetaClass();
		}

		return T::GetMetaClassStatic();
	}
};

template< typename T > struct ClassID< std::shared_ptr< T > >
{
	static IMetaClassPtr Get( const std::shared_ptr< T > & val = nullptr )
	{
		if( val )
		{
			return val->GetMetaClass();
		}

		return T::GetMetaClassStatic();
	}
};

template< typename T > struct MetaID
{
	static IMetaInfoPtr Get( const T * val = nullptr )
	{
		using raw_t = typename TypeTraits<T>::raw_t;

		return SP_CAST<IMetaInfo>( std::conditional_t< std::is_enum<raw_t>::value, EnumID<raw_t>, ClassID<raw_t>>::Get( val ) );
	}
};

template< typename T > struct MetaID< std::shared_ptr< T > >
{
	static IMetaInfoPtr Get( const std::shared_ptr< T > & val = nullptr )
	{
		return MetaID<T>::Get( val.get() );
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

template< typename T > struct TypeID< std::shared_ptr< T > >
{
	static IMetaTypePtr Get( const std::shared_ptr<T> & val = nullptr )
	{
		return TypeID<T>::Get( val.get() );
	}
};

END_XE_NAMESPACE

#endif // __METAID_HPP__4D612830_3D3B_42A0_9441_7CECA63594CB
