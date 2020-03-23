/*!
 * \file   IMetaEnum.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __IMETAENUM_H__08B9D60C_CE48_4913_BE61_A217F8BFF289
#define __IMETAENUM_H__08B9D60C_CE48_4913_BE61_A217F8BFF289

#include "Variant.h"
#include "IMetaType.h"

BEG_XE_NAMESPACE

class Archive;

class XE_API IMetaEnum : public IMetaType
{
public:
	IMetaEnum( const String& Name, XE::uint64 Size, IMetaInfoPtr Owner, const String & ModuleName = "XE" );

	~IMetaEnum();

public:
	XE::uint64 GetEnumCount() const;

	String FindName( XE::Variant val ) const;

	XE::Variant FindValue( const String& val ) const;

	void Visit( const std::function<void( String, XE::Variant )> & val ) const;

protected:
	void _RegisterValue( const String& Name, XE::Variant Val );

private:
	Array< Pair<String, XE::Variant> > _Values;
};

END_XE_NAMESPACE

#endif // __IMETAENUM_H__08B9D60C_CE48_4913_BE61_A217F8BFF289
