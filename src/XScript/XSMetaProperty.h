/*!
 * \file	XSMetaProperty.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/08
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef XSMETAPROPERTY_H__707EDBF2_2411_4F3A_9ECF_98D44F3F346D
#define XSMETAPROPERTY_H__707EDBF2_2411_4F3A_9ECF_98D44F3F346D

#include "Type.h"

BEG_XE_NAMESPACE

class XSCRIPT_API XSMetaProperty : public XE::IMetaProperty
{
public:
	XSMetaProperty( const String & Name, XE::uint8 Flag, IMetaInfoPtr Value, IMetaClassPtr Owner, const String & ModuleName );

	~XSMetaProperty();

public:
	Variant Get( const Variant & obj ) const override;

	void Set( const Variant & obj, const Variant & val ) const override;

private:
	XE::uint64 _Address;
};

END_XE_NAMESPACE

#endif // XSMETAPROPERTY_H__707EDBF2_2411_4F3A_9ECF_98D44F3F346D
