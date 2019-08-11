/*!
 * \file	XSMetaMethod.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/08
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef XSMETAMETHOD_H__1C3BC429_C81B_4D99_B2F9_579DD5F8F325
#define XSMETAMETHOD_H__1C3BC429_C81B_4D99_B2F9_579DD5F8F325

#include "Type.h"

BEG_XE_NAMESPACE

class XSMetaMethod : public XE::IMetaMethod
{
public:
	XSMetaMethod( const String & Name, IMetaInfoPtr Result, ParameterType && Parameter, IMetaClassPtr Owner, const String & ModuleName );

	~XSMetaMethod();

protected:
	Variant Invoke( InvokeStack * params ) const override;

};

END_XE_NAMESPACE

#endif // XSMETAMETHOD_H__1C3BC429_C81B_4D99_B2F9_579DD5F8F325
