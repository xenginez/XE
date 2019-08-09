/*!
 * \file	XSMetaEnum.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/08
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef XSMETAENUM_H__C6FF03D9_A2F9_4B95_A496_B81B5FB94F7A
#define XSMETAENUM_H__C6FF03D9_A2F9_4B95_A496_B81B5FB94F7A

#include "Type.h"

BEG_XE_NAMESPACE

class XSCRIPT_API XSMetaEnum : XE::IMetaEnum
{
public:
	XSMetaEnum( const String & Name, IMetaInfoPtr Owner, const String & ModuleName );

	~XSMetaEnum();

public:
	void Value( const std::string & name, XE::int64 val );
};

END_XE_NAMESPACE

#endif // XSMETAENUM_H__C6FF03D9_A2F9_4B95_A496_B81B5FB94F7A
