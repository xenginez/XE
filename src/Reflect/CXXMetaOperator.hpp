/*!
 * \file   CXXMetaOperator.hpp
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __CXXMETAOPERATOR_HPP__00A1DBA0_9AAD_40B9_8F35_A7D2216AAE1E
#define __CXXMETAOPERATOR_HPP__00A1DBA0_9AAD_40B9_8F35_A7D2216AAE1E

#include "IMetaOperator.h"

#include "MetaID.hpp"

BEG_XE_NAMESPACE

template< typename OperatorType > class CXXMetaOperator;

template< typename ResultType, typename ClassType > class CXXMetaOperator<ResultType( *)( ClassType )> : public IMetaOperator
{
public:
	using OperatorType = ResultType( *)( ClassType );

public:
	CXXMetaOperator( const String& Name, OperatorType Oper, IMetaClassPtr Owner )
		:IMetaOperator( Name, MetaID<typename TypeTraits<ResultType>::raw_t>::Get(), nullptr, Owner ), _Oper( Oper )
	{
	}

public:
	virtual Variant Invoke( InvokeStack * params ) const override
	{
		return _Oper( params->Pop<ClassType>() );
	}

private:
	OperatorType _Oper;
};

template< typename ResultType, typename ClassType, typename RightType > class CXXMetaOperator<ResultType( *)( ClassType, RightType )> : public IMetaOperator
{
public:
	using OperatorType = ResultType( *)( RightType );

public:
	CXXMetaOperator( const String& Name, OperatorType Oper, IMetaClassPtr Owner )
		:IMetaOperator( Name, MetaID<typename TypeTraits<ResultType>::raw_t>::Get(), MetaID<typename TypeTraits<RightType>::raw_t>::Get(), Owner ), _Oper( Oper )
	{
	}

public:
	virtual Variant Invoke( InvokeStack * params ) const override
	{
		return _Oper( params->Pop<ClassType>(), params->Pop<RightType>() );
	}

private:
	OperatorType _Oper;
};

template< typename ResultType, typename ClassType > class CXXMetaOperator<ResultType( ClassType::* )( )> : public IMetaOperator
{
public:
	using OperatorType = ResultType( ClassType::* )( );

public:
	CXXMetaOperator( const String& Name, OperatorType Oper, IMetaClassPtr Owner )
		:IMetaOperator( Name, MetaID<typename TypeTraits<ResultType>::raw_t>::Get(), nullptr, Owner ), _Oper( Oper )
	{
	}

public:
	virtual Variant Invoke( InvokeStack * params ) const override
	{
		return ( params->Pop<ClassType*>()->*_Oper )( );
	}

private:
	OperatorType _Oper;
};

template< typename ResultType, typename ClassType > class CXXMetaOperator<ResultType( ClassType::* )( ) const> : public IMetaOperator
{
public:
	using OperatorType = ResultType( ClassType::* )( ) const;

public:
	CXXMetaOperator( const String& Name, OperatorType Oper, IMetaClassPtr Owner )
		:IMetaOperator( Name, MetaID<typename TypeTraits<ResultType>::raw_t>::Get(), nullptr, Owner ), _Oper( Oper )
	{
	}

public:
	virtual Variant Invoke( InvokeStack * params ) const override
	{
		return ( params->Pop<ClassType*>()->*_Oper )( );
	}

private:
	OperatorType _Oper;
};

template< typename ResultType, typename ClassType, typename RightType > class CXXMetaOperator<ResultType( ClassType::* )( RightType )> : public IMetaOperator
{
public:
	using OperatorType = ResultType( ClassType::* )( RightType );

public:
	CXXMetaOperator( const String& Name, OperatorType Oper, IMetaClassPtr Owner )
		:IMetaOperator( Name, MetaID<typename TypeTraits<ResultType>::raw_t>::Get(), MetaID<typename TypeTraits<RightType>::raw_t>::Get(), Owner ), _Oper( Oper )
	{
	}

public:
	virtual Variant Invoke( InvokeStack * params ) const override
	{
		return ( params->Pop<ClassType*>()->*_Oper )( params->Pop<RightType>() );
	}

private:
	OperatorType _Oper;
};

template< typename ResultType, typename ClassType, typename RightType > class CXXMetaOperator<ResultType( ClassType::* )( RightType ) const> : public IMetaOperator
{
public:
	using OperatorType = ResultType( ClassType::* )( RightType ) const;

public:
	CXXMetaOperator( const String& Name, OperatorType Oper, IMetaClassPtr Owner )
		:IMetaOperator( Name, MetaID<typename TypeTraits<ResultType>::raw_t>::Get(), MetaID<typename TypeTraits<RightType>::raw_t>::Get(), Owner ), _Oper( Oper )
	{
	}

public:
	virtual Variant Invoke( InvokeStack * params ) const override
	{
		return ( params->Pop<ClassType*>()->*_Oper )( params->Pop<RightType>() );
	}

private:
	OperatorType _Oper;
};

END_XE_NAMESAPCE

#endif // __CXXMETAOPERATOR_HPP__00A1DBA0_9AAD_40B9_8F35_A7D2216AAE1E
