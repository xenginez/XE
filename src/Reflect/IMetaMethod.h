/*!
 * \file   IMetaMethod.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __IMETAMETHOD_H__154D0025_BEE1_4DFB_AC1F_4739AFB4B34F
#define __IMETAMETHOD_H__154D0025_BEE1_4DFB_AC1F_4739AFB4B34F

#include "IMetaInfo.h"
#include "InvokeStack.h"
#include "ParameterType.hpp"

BEG_XE_NAMESPACE

class XE_API IMetaMethod : public IMetaInfo
{
public:
	IMetaMethod( const String& Name, bool IsStatic, bool IsConst, IMetaInfoPtr Result, ParameterType&& Parameter, IMetaClassPtr Owner, const String & ModuleName = "XE" );

	~IMetaMethod();

public:
	bool IsConst() const;

	bool IsStatic() const;

public:
	IMetaInfoPtr GetResult() const;

	const ParameterType& GetParameter() const;

public:
	template< typename ... Types >Variant Invoke( Types&&...args ) const
	{
		InvokeStack stack;

		stack.Push( std::forward<Types>( args )... );

		return Invoke( &stack );
	}

public:
	virtual Variant Invoke( InvokeStack * params ) const = 0;

private:
	bool _IsConst;
	bool _IsStatic;
	IMetaInfoWPtr _Result;
	ParameterType _Parameter;
};

END_XE_NAMESPACE

#endif // __IMETAMETHOD_H__154D0025_BEE1_4DFB_AC1F_4739AFB4B34F
