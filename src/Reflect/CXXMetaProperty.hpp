/*!
 * \file   CXXMetaProperty.hpp
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __CXXMETAPROPERTY_HPP__3B024B46_FC59_464C_8819_339019E204F5
#define __CXXMETAPROPERTY_HPP__3B024B46_FC59_464C_8819_339019E204F5

#include "IMetaProperty.h"

BEG_XE_NAMESPACE

template< typename ... T > class CXXMetaProperty;

template< typename ValueType > class CXXMetaProperty<ValueType> : public IMetaProperty
{
public:
	using PropertyType = ValueType;

public:
	CXXMetaProperty( const String& Name, PropertyType * Value, XE::uint8 Flag, IMetaClassPtr Owner, IMetaModulePtr Module )
		:IMetaProperty( Name, Flag, true, std::is_const_v<ValueType>, !std::is_pointer_v<ValueType> && !std::is_reference_v<ValueType> && !std::is_weak_ptr_v<ValueType> && !std::is_shared_ptr_v<ValueType>, std::is_pointer_v<ValueType>, std::is_shared_ptr_v<ValueType> || std::is_weak_ptr_v<ValueType>, std::is_reference_v<ValueType>, ::XE_TypeID<typename TypeTraits<ValueType>::raw_t>::Get(), Owner, Module ), _Value( Value )
	{

	}

public:
	virtual Variant Get( const Variant& obj ) const override
	{
		return *_Value;
	}

	virtual void Set( const Variant& obj, const Variant& val ) const override
	{
		if constexpr ( !std::is_const_v<ValueType> )
		{
			*_Value = val.Value<ValueType>();
		}
		else
		{
			throw MetaException( shared_from_this(), "is const value" );
		}
	}

private:
	PropertyType * _Value;
};

template< typename ClassType, typename ValueType > class CXXMetaProperty<ValueType( ClassType::* )> : public IMetaProperty
{
public:
	using PropertyType = ValueType( ClassType::* );

public:
	CXXMetaProperty( const String& Name, PropertyType Value, XE::uint8 Flag, IMetaClassPtr Owner, IMetaModulePtr Module )
		:IMetaProperty( Name, Flag, false, std::is_const_v<ValueType>, !std::is_pointer_v<ValueType> && !std::is_reference_v<ValueType> && !std::is_weak_ptr_v<ValueType> && !std::is_shared_ptr_v<ValueType>, std::is_pointer_v<ValueType>, std::is_shared_ptr_v<ValueType> || std::is_weak_ptr_v<ValueType>, std::is_reference_v<ValueType>, ::XE_TypeID<typename XE::TypeTraits<ValueType>::raw_t>::Get(), Owner, Module ), _Value( Value )
	{

	}

public:
	virtual Variant Get( const Variant& obj ) const override
	{
		return obj.Value<ClassType*>()->*( _Value );
	}

	virtual void Set( const Variant& obj, const Variant& val ) const override
	{
		if constexpr ( !std::is_const_v<ValueType> )
		{
			obj.Value<ClassType*>()->*( _Value ) = val.Value<ValueType>();
		}
		else
		{
			throw MetaException( shared_from_this(), "is const value" );
		}
	}

private:
	PropertyType _Value;
};

template< typename _GetType, typename _SetType > class CXXMetaProperty<_GetType( *)( ), void( *)( _SetType )> : public IMetaProperty
{
public:
	using ValueType = _GetType;
	using GetFuncType = _GetType( *)( );
	using SetFuncType = void( *)( _SetType );

public:
	CXXMetaProperty( const String& Name, GetFuncType get, SetFuncType set, XE::uint8 Flag, IMetaClassPtr Owner, IMetaModulePtr Module )
		:IMetaProperty( Name, Flag, false, false, !std::is_pointer_v<ValueType> && !std::is_reference_v<ValueType> && !std::is_weak_ptr_v<ValueType> && !std::is_shared_ptr_v<ValueType>, std::is_pointer_v<ValueType>, std::is_shared_ptr_v<ValueType> || std::is_weak_ptr_v<ValueType>, std::is_reference_v<ValueType>, ::XE_TypeID<typename XE::TypeTraits<ValueType>::raw_t>::Get(), Owner, Module ), _GetFunc( get ), _SetFunc( set )
	{

	}

public:
	virtual Variant Get( const Variant& obj ) const override
	{
		return _GetFunc();
	}

	virtual void Set( const Variant& obj, const Variant& val ) const override
	{
		_SetFunc( val.Value<_SetType>() );
	}

private:
	GetFuncType _GetFunc;
	SetFuncType _SetFunc;
};

template< typename ClassType, typename _GetType, typename _SetType > class CXXMetaProperty<_GetType( ClassType::* )( ), void( ClassType::* )( _SetType )> : public IMetaProperty
{
public:
	using ValueType = _GetType;
	using GetFuncType = _GetType( ClassType::* )( );
	using SetFuncType = void( ClassType::* )( _SetType );

public:
	CXXMetaProperty( const String& Name, GetFuncType get, SetFuncType set, XE::uint8 Flag, IMetaClassPtr Owner, IMetaModulePtr Module )
		:IMetaProperty( Name, Flag, false, false, !std::is_pointer_v<ValueType> && !std::is_reference_v<ValueType> && !std::is_weak_ptr_v<ValueType> && !std::is_shared_ptr_v<ValueType>, std::is_pointer_v<ValueType>, std::is_shared_ptr_v<ValueType> || std::is_weak_ptr_v<ValueType>, std::is_reference_v<ValueType>, ::XE_TypeID<typename XE::TypeTraits<ValueType>::raw_t>::Get(), Owner, Module ), _GetFunc( get ), _SetFunc( set )
	{

	}

public:
	virtual Variant Get( const Variant& obj ) const override
	{
		return ( obj.Value<ClassType*>()->*_GetFunc )( );
	}

	virtual void Set( const Variant& obj, const Variant& val ) const override
	{
		( obj.Value<ClassType*>()->*_SetFunc )( val.Value<_SetType>() );
	}

private:
	GetFuncType _GetFunc;
	SetFuncType _SetFunc;
};

template< typename ClassType, typename _GetType, typename _SetType > class CXXMetaProperty<_GetType( ClassType::* )( ) const, void( ClassType::* )( _SetType )> : public IMetaProperty
{
public:
	using ValueType = _GetType;
	using GetFuncType = _GetType( ClassType::* )( ) const;
	using SetFuncType = void( ClassType::* )( _SetType );

public:
	CXXMetaProperty( const String& Name, GetFuncType get, SetFuncType set, XE::uint8 Flag, IMetaClassPtr Owner, IMetaModulePtr Module )
		:IMetaProperty( Name, Flag, false, false, !std::is_pointer_v<ValueType> && !std::is_reference_v<ValueType> && !std::is_weak_ptr_v<ValueType> && !std::is_shared_ptr_v<ValueType>, std::is_pointer_v<ValueType>, std::is_shared_ptr_v<ValueType> || std::is_weak_ptr_v<ValueType>, std::is_reference_v<ValueType>, ::XE_TypeID<typename XE::TypeTraits<ValueType>::raw_t>::Get(), Owner, Module ), _GetFunc( get ), _SetFunc( set )
	{

	}

public:
	virtual Variant Get( const Variant& obj ) const override
	{
		return ( obj.Value<ClassType*>()->*_GetFunc )( );
	}

	virtual void Set( const Variant& obj, const Variant& val ) const override
	{
		( obj.Value<ClassType*>()->*_SetFunc )( val.Value<_SetType>() );
	}

private:
	GetFuncType _GetFunc;
	SetFuncType _SetFunc;
};

template< typename _GetType > class CXXMetaProperty<_GetType( * )( )> : public IMetaProperty
{
public:
	using ValueType = _GetType;
	using GetFuncType = _GetType( * )( );

public:
	CXXMetaProperty( const String & Name, GetFuncType get, XE::uint8 Flag, IMetaClassPtr Owner, IMetaModulePtr Module )
		:IMetaProperty( Name, Flag | IMetaProperty::NoWirte, false, false, !std::is_pointer_v<ValueType> && !std::is_reference_v<ValueType> && !std::is_weak_ptr_v<ValueType> && !std::is_shared_ptr_v<ValueType>, std::is_pointer_v<ValueType>, std::is_shared_ptr_v<ValueType> || std::is_weak_ptr_v<ValueType>, std::is_reference_v<ValueType>, ::XE_TypeID<typename XE::TypeTraits<ValueType>::raw_t>::Get(), Owner, Module ), _GetFunc( get )
	{

	}

public:
	virtual Variant Get( const Variant & obj ) const override
	{
		return _GetFunc();
	}

	virtual void Set( const Variant & obj, const Variant & val ) const override
	{
		XE_ASSERT( false && "is read only!" );
	}

private:
	GetFuncType _GetFunc;
};

template< typename ClassType, typename _GetType > class CXXMetaProperty<_GetType( ClassType:: * )( )> : public IMetaProperty
{
public:
	using ValueType = _GetType;
	using GetFuncType = _GetType( ClassType:: * )( );

public:
	CXXMetaProperty( const String & Name, GetFuncType get, XE::uint8 Flag, IMetaClassPtr Owner, IMetaModulePtr Module )
		:IMetaProperty( Name, Flag | IMetaProperty::NoWirte, false, false, !std::is_pointer_v<ValueType> && !std::is_reference_v<ValueType> && !std::is_weak_ptr_v<ValueType> && !std::is_shared_ptr_v<ValueType>, std::is_pointer_v<ValueType>, std::is_shared_ptr_v<ValueType> || std::is_weak_ptr_v<ValueType>, std::is_reference_v<ValueType>, ::XE_TypeID<typename XE::TypeTraits<ValueType>::raw_t>::Get(), Owner, Module ), _GetFunc( get )
	{

	}

public:
	virtual Variant Get( const Variant & obj ) const override
	{
		return ( obj.Value<ClassType *>()->*_GetFunc )( );
	}

	virtual void Set( const Variant & obj, const Variant & val ) const override
	{
		XE_ASSERT( false && "is read only!" );
	}

private:
	GetFuncType _GetFunc;
};

template< typename ClassType, typename _GetType > class CXXMetaProperty<_GetType( ClassType:: * )( ) const> : public IMetaProperty
{
public:
	using ValueType = _GetType;
	using GetFuncType = _GetType( ClassType:: * )( ) const;

public:
	CXXMetaProperty( const String & Name, GetFuncType get, XE::uint8 Flag, IMetaClassPtr Owner, IMetaModulePtr Module )
		:IMetaProperty( Name, Flag | IMetaProperty::NoWirte, false, false, !std::is_pointer_v<ValueType> && !std::is_reference_v<ValueType> && !std::is_weak_ptr_v<ValueType> && !std::is_shared_ptr_v<ValueType>, std::is_pointer_v<ValueType>, std::is_shared_ptr_v<ValueType> || std::is_weak_ptr_v<ValueType>, std::is_reference_v<ValueType>, ::XE_TypeID<typename XE::TypeTraits<ValueType>::raw_t>::Get(), Owner, Module ), _GetFunc( get )
	{

	}

public:
	virtual Variant Get( const Variant & obj ) const override
	{
		return ( obj.Value<ClassType *>()->*_GetFunc )( );
	}

	virtual void Set( const Variant & obj, const Variant & val ) const override
	{
		XE_ASSERT( false && "is read only!" );
	}

private:
	GetFuncType _GetFunc;
};

template< typename _SetType > class CXXMetaProperty<void( * )( _SetType )> : public IMetaProperty
{
public:
	using ValueType = _SetType;
	using SetFuncType = void( * )( _SetType );

public:
	CXXMetaProperty( const String & Name, SetFuncType set, XE::uint8 Flag, IMetaClassPtr Owner, IMetaModulePtr Module )
		:IMetaProperty( Name, Flag | IMetaProperty::NoRead, false, false, !std::is_pointer_v<ValueType> && !std::is_reference_v<ValueType> && !std::is_weak_ptr_v<ValueType> && !std::is_shared_ptr_v<ValueType>, std::is_pointer_v<ValueType>, std::is_shared_ptr_v<ValueType> || std::is_weak_ptr_v<ValueType>, std::is_reference_v<ValueType>, ::XE_TypeID<typename XE::TypeTraits<ValueType>::raw_t>::Get(), Owner, Module ), _GetFunc( get ), _SetFunc( set )
	{

	}

public:
	virtual Variant Get( const Variant & obj ) const override
	{
		XE_ASSERT( false && "is only wirte!" );
		return Variant();
	}

	virtual void Set( const Variant & obj, const Variant & val ) const override
	{
		_SetFunc( val.Value<_SetType>() );
	}

private:
	SetFuncType _SetFunc;
};

template< typename ClassType, typename _SetType > class CXXMetaProperty<void( ClassType:: * )( _SetType )> : public IMetaProperty
{
public:
	using ValueType = _SetType;
	using SetFuncType = void( ClassType:: * )( _SetType );

public:
	CXXMetaProperty( const String & Name, SetFuncType set, XE::uint8 Flag, IMetaClassPtr Owner, IMetaModulePtr Module )
		:IMetaProperty( Name, Flag | IMetaProperty::NoRead, false, false, !std::is_pointer_v<ValueType> && !std::is_reference_v<ValueType> && !std::is_weak_ptr_v<ValueType> && !std::is_shared_ptr_v<ValueType>, std::is_pointer_v<ValueType>, std::is_shared_ptr_v<ValueType> || std::is_weak_ptr_v<ValueType>, std::is_reference_v<ValueType>, ::XE_TypeID<typename XE::TypeTraits<ValueType>::raw_t>::Get(), Owner, Module ), _GetFunc( get ), _SetFunc( set )
	{

	}

public:
	virtual Variant Get( const Variant & obj ) const override
	{
		XE_ASSERT( false && "is only wirte!" );
		return Variant();
	}

	virtual void Set( const Variant & obj, const Variant & val ) const override
	{
		( obj.Value<ClassType *>()->*_SetFunc )( val.Value<_SetType>() );
	}

private:
	SetFuncType _SetFunc;
};

END_XE_NAMESPACE

#endif // __CXXMETAPROPERTY_HPP__3B024B46_FC59_464C_8819_339019E204F5
