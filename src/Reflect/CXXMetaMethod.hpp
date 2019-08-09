/*!
 * \file   CXXMetaMethod.hpp
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __CXXMETAMETHOD_HPP__6B59966B_7814_4B60_BB9C_FE4062B5744A
#define __CXXMETAMETHOD_HPP__6B59966B_7814_4B60_BB9C_FE4062B5744A

#include "IMetaMethod.h"

#include "MetaID.hpp"

BEG_XE_NAMESPACE

template< typename MethodType  > class CXXMetaMethod;

template< typename ... ParameterType  > class CXXMetaMethod<void( *)( ParameterType... )> : public IMetaMethod
{
public:
	using MethodType = void( *)( ParameterType... );

public:
	CXXMetaMethod( const String& Name, MethodType Callback, IMetaClassPtr Owner )
		:IMetaMethod( Name, true, false, nullptr, MakeParameterType<ParameterType...>(), Owner ), _Callback( Callback )
	{
	}

public:
	virtual Variant Invoke( InvokeStack * params ) const override
	{
		_Callback( params->Pop<ParameterType>()... );
		return Variant();
	}

private:
	MethodType _Callback;
};

template< typename ResultType, typename ... ParameterType  > class CXXMetaMethod<ResultType( *)( ParameterType... )> : public IMetaMethod
{
public:
	using MethodType = ResultType( *)( ParameterType... );

public:
	CXXMetaMethod( const String& Name, MethodType Callback, IMetaClassPtr Owner )
		:IMetaMethod( Name, true, false, MetaID<typename TypeTraits< ResultType >::raw_t>::Get(), MakeParameterType<ParameterType...>(), Owner ), _Callback( Callback )
	{
	}

public:
	virtual Variant Invoke( InvokeStack * params ) const override
	{
		return _Callback( params->Pop<ParameterType>()... );
	}

private:
	MethodType _Callback;
};

template< typename ClassType, typename ... ParameterType  > class CXXMetaMethod< void( ClassType::* )( ParameterType... )> : public IMetaMethod
{
public:
	using MethodType = void( ClassType::* )( ParameterType... );

public:
	CXXMetaMethod( const String& Name, MethodType Callback, IMetaClassPtr Owner )
		:IMetaMethod( Name, false, false, nullptr, MakeParameterType<ParameterType...>(), Owner ), _Callback( Callback )
	{
	}

public:
	virtual Variant Invoke( InvokeStack * params ) const override
	{
		( params->Pop<ClassType*>()->*_Callback )( params->Pop<ParameterType>()... );
		return Variant();
	}

private:
	MethodType _Callback;
};

template< typename ClassType, typename ... ParameterType  > class CXXMetaMethod< void( ClassType::* )( ParameterType... ) const> : public IMetaMethod
{
public:
	using MethodType = void( ClassType::* )( ParameterType... ) const;

public:
	CXXMetaMethod( const String& Name, MethodType Callback, IMetaClassPtr Owner )
		:IMetaMethod( Name, false, true, nullptr, MakeParameterType<ParameterType...>(), Owner ), _Callback( Callback )
	{
	}

public:
	virtual Variant Invoke( InvokeStack * params ) const override
	{
		( params->Pop<ClassType*>()->*_Callback )( params->Pop<ParameterType>()... );
		return Variant();
	}

private:
	MethodType _Callback;
};

template< typename ResultType, typename ClassType, typename ... ParameterType  > class CXXMetaMethod< ResultType( ClassType::* )( ParameterType... )> : public IMetaMethod
{
public:
	using MethodType = ResultType( ClassType::* )( ParameterType... );

public:
	CXXMetaMethod( const String& Name, MethodType Callback, IMetaClassPtr Owner )
		:IMetaMethod( Name, false, false, MetaID<typename TypeTraits< ResultType >::raw_t>::Get(), MakeParameterType<ParameterType...>(), Owner ), _Callback( Callback )
	{
	}

public:
	virtual Variant Invoke( InvokeStack * params ) const override
	{
		return ( params->Pop<ClassType*>()->*_Callback )( params->Pop<ParameterType>()... );
	}

private:
	MethodType _Callback;
};

template< typename ResultType, typename ClassType, typename ... ParameterType  > class CXXMetaMethod< ResultType( ClassType::* )( ParameterType... ) const> : public IMetaMethod
{
public:
	using MethodType = ResultType( ClassType::* )( ParameterType... ) const;

public:
	CXXMetaMethod( const String& Name, MethodType Callback, IMetaClassPtr Owner )
		:IMetaMethod( Name, false, true, MetaID<typename TypeTraits< ResultType >::raw_t>::Get(), MakeParameterType<ParameterType...>(), Owner ), _Callback( Callback )
	{
	}

public:
	virtual Variant Invoke( InvokeStack * params ) const override
	{
		return ( params->Pop<ClassType*>()->*_Callback )( params->Pop<ParameterType>()... );
	}

private:
	MethodType _Callback;
};

END_XE_NAMESPACE

#endif // __CXXMETAMETHOD_HPP__6B59966B_7814_4B60_BB9C_FE4062B5744A
