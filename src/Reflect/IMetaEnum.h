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

#include "IMetaType.h"

BEG_XE_NAMESPACE

class Archive;

class REFLECT_API IMetaEnum : public IMetaType
{
public:
	IMetaEnum( const String& Name, XE::uint64 Size, IMetaInfoPtr Owner, const String & ModuleName = "XE" );

	~IMetaEnum();

public:
	XE::uint64 GetEnumCount() const;

	String FindName( XE::int64 val ) const;

	XE::int64 FindValue( const String& val ) const;

	void Visit( std::function<void( String, XE::int64 )> val ) const;

protected:
	void _RegisterValue( const String& Name, XE::int64 Val );

private:
	Array< Pair<String, XE::int64> > _Values;
};

END_XE_NAMESPACE

#endif // __IMETAENUM_H__08B9D60C_CE48_4913_BE61_A217F8BFF289
