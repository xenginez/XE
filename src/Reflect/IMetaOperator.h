/*!
 * \file   IMetaOperator.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __IMETAOPERATOR_H__366F2E00_9770_464F_ACA4_8A2E95EA5D21
#define __IMETAOPERATOR_H__366F2E00_9770_464F_ACA4_8A2E95EA5D21

#include "IMetaInfo.h"
#include "InvokeStack.h"

BEG_XE_NAMESPACE

class REFLECT_API IMetaOperator : public IMetaInfo
{
public:
	IMetaOperator( const String& Name, IMetaInfoPtr Result, IMetaInfoPtr Parameter, IMetaClassPtr Owner );

	~IMetaOperator();

public:
	IMetaInfoPtr GetResult() const;

	IMetaInfoPtr GetParameter() const;

public:
	Variant Invoke( const Variant& obj ) const
	{
		InvokeStack stack;

		stack.Push( obj );

		return Invoke( &stack );
	}

	template< typename Types >Variant Invoke( const Variant& obj, Types&& args ) const
	{
		InvokeStack stack;

		stack.Push( obj );
		stack.Push( args );

		return Invoke( &stack );
	}

public:
	virtual Variant Invoke( InvokeStack * params ) const = 0;

private:
	IMetaInfoWPtr _Result;
	IMetaInfoWPtr _Parameter;
};


END_XE_NAMESPACE

#endif // __IMETAOPERATOR_H__366F2E00_9770_464F_ACA4_8A2E95EA5D21
