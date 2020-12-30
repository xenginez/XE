/*!
 * \file   IMetaInfo.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __IMETA_H__7FB7B1B8_7091_4DBE_82E4_E95126647F93
#define __IMETA_H__7FB7B1B8_7091_4DBE_82E4_E95126647F93

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API IMetaInfo : public std::enable_shared_from_this< IMetaInfo >
{
public:
	IMetaInfo( const String & Name, MetaType Type, IMetaInfoPtr Owner, IMetaModulePtr Module );

	virtual ~IMetaInfo();

public:
	const MetaType GetType() const;

	const String & GetName() const;

	const String & GetFullName() const;

public:
	IMetaInfoPtr GetOwner() const;

	IMetaModulePtr GetModule() const;

private:
	MetaType _Type;
	String _Name;
	String _FullName;
	IMetaInfoWPtr _Owner;
	IMetaModuleWPtr _Module;
};

END_XE_NAMESPACE

#endif // __IMETA_H__7FB7B1B8_7091_4DBE_82E4_E95126647F93
