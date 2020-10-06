/*!
 * \file   IMetaType.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/12
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __IMETATYPE_H__8929D439_3C4B_4410_85AD_5D3F570075E6
#define __IMETATYPE_H__8929D439_3C4B_4410_85AD_5D3F570075E6

#include <functional>

#include "IMetaInfo.h"

BEG_XE_NAMESPACE

class XE_API IMetaType : public IMetaInfo
{
public:
	IMetaType( const String& Name, MetaType Type, XE::uint64 Size, IMetaInfoPtr Owner, const String & ModuleName = "XE" );

	~IMetaType();

public:
	XE::uint64 GetSize() const;

private:
	XE::uint64 _Size;
};

END_XE_NAMESPACE

#endif // __IMETATYPE_H__8929D439_3C4B_4410_85AD_5D3F570075E6
