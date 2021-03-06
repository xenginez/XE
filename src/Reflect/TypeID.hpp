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

template< typename U > struct HasMemberGetMetaClass
{
private:
	template < typename Ty, const XE::IMetaClassPtr( Ty:: * )() const = &Ty::GetMetaClass > static constexpr auto check( Ty * )
	{
		return true;
	};

	static constexpr bool check( ... )
	{
		return false;
	};

public:
	static constexpr bool value = check( static_cast< U * >( nullptr ) );
};

template< typename T > struct XE_ClassID
{
	static XE::IMetaClassPtr Get( const T * val = nullptr )
	{
		if constexpr ( HasMemberGetMetaClass< T >::value )
		{
			if( val )
			{
				return val->GetMetaClass();
			}
		}

		return T::GetMetaClassStatic();
	}
};

template< typename T > struct ::XE_ClassID< XE::SharedPtr< T > >
{
	static XE::IMetaClassPtr Get( const XE::SharedPtr< T > & val = nullptr )
	{
		if constexpr( HasMemberGetMetaClass< T >::value )
		{
			if( val )
			{
				return val->GetMetaClass();
			}
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

template< typename T > XE_INLINE std::string ToString( T _Val )
{
	if constexpr( std::is_enum_v< T > )
	{
		if( auto e = XE_EnumID< T >::Get()->FindName( _Val ) )
		{
			return e.std_str() + "(" + XE::ToString( ( XE::uint64 )_Val ) + ")";
		}
		else
		{
			return XE::ToString( ( XE::uint64 )_Val );
		}
	}
	else
	{
		return XE_ClassID< T >::Get( &_Val )->GetFullName();
	}
}

#endif // TYPEID_HPP__1C7147FB_7591_47E2_B804_CD182F01438A
