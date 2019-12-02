/*!
 * \file   BBKeyPtr.hpp
 *
 * \author ZhengYuanQing
 * \date   2019/01/12
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __BBKEYPTR_HPP__59D9C01D_02C3_49BC_B48F_C78FCA316AD9
#define __BBKEYPTR_HPP__59D9C01D_02C3_49BC_B48F_C78FCA316AD9

#include "Type.h"

BEG_XE_NAMESPACE

template< typename T > class BBKeyPtr
{
	friend class BlackBoard;

public:
	BBKeyPtr()
		:_var( nullptr )
	{
	}

	BBKeyPtr( std::nullptr_t )
		:_var( nullptr )
	{
	}

	BBKeyPtr( const BBKeyPtr& val )
		:_var( val._var )
	{
		if ( auto meta = _var->GetType() )
		{
			if (meta->GetType() == MetaType::ENUM)
			{
				XE_ASSERT( meta == MetaID<T>::Get() );
			}
			else if ( auto cls = SP_CAST<IMetaClass>( meta ) )
			{
				XE_ASSERT( cls->CanConvert( DP_CAST<IMetaClass>( MetaID<T>::Get() ) ) );
			}
		}
		else
		{
			XE_ASSERT( false );
		}
	}

	template< typename Y > BBKeyPtr( const BBKeyPtr<Y>& val )
		: _var( val._var )
	{
		if ( auto meta = _var->GetType() )
		{
			if ( meta->GetType() == MetaType::ENUM )
			{
				XE_ASSERT( meta == MetaID<T>::Get() );
			}
			else if ( auto cls = SP_CAST<IMetaClass>( meta ) )
			{
				XE_ASSERT( cls->CanConvert( DP_CAST<IMetaClass>( MetaID<T>::Get() ) ) );
			}
		}
		else
		{
			XE_ASSERT( false );
		}
	}

private:
	BBKeyPtr( Variant * val );

public:
	T * operator->() const
	{
		return get();
	}

	T& operator*() const
	{
		return *get();
	}

public:
	T * get() const
	{
		XE_ASSERT( _var );

		return (T *)_var->ToPointer();
	}

private:
	Variant * _var;
};

END_XE_NAMESPACE

#endif // __BBKEYPTR_HPP__59D9C01D_02C3_49BC_B48F_C78FCA316AD9
