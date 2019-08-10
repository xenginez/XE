/*!
 * \file	XSMetaOperator.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/08
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef XSMETAOPERATOR_H__E5E36EAE_541F_462A_8A5A_5E69799D11EB
#define XSMETAOPERATOR_H__E5E36EAE_541F_462A_8A5A_5E69799D11EB

#include "Type.h"

BEG_XE_NAMESPACE

class XSMetaOperator : public IMetaOperator
{
public:
	XSMetaOperator( const String & Name, IMetaInfoPtr Result, IMetaInfoPtr Parameter, IMetaClassPtr Owner, const String & ModuleName );

	~XSMetaOperator();

public:
	Variant Invoke( InvokeStack * params ) const override;

};

END_XE_NAMESPACE

#endif // XSMETAOPERATOR_H__E5E36EAE_541F_462A_8A5A_5E69799D11EB
