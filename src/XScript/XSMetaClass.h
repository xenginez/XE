/*!
 * \file	XSMetaClass.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/08
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef XSMETACLASS_H__88B06678_D55E_4C6A_B86F_02EEC0ADBEF2
#define XSMETACLASS_H__88B06678_D55E_4C6A_B86F_02EEC0ADBEF2

#include "Type.h"

BEG_XE_NAMESPACE

class XSCRIPT_API XSMetaClass : public XE::IMetaClass
{
public:
	XSMetaClass( const String & Name, XE::uint64 Size, IMetaClassPtr Super, IMetaInfoPtr Owner, const String & ModuleName );

	~XSMetaClass();

public:
	Variant Construct() const override;

	Variant ConstructPtr() const override;

	void Destruct( Variant & val ) const override;

	void Serialize( Archive * arc, Variant & val ) const override;

};

END_XE_NAMESPACE

#endif // XSMETACLASS_H__88B06678_D55E_4C6A_B86F_02EEC0ADBEF2
