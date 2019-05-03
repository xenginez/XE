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

#include "IMetaInfo.h"
#include "Variant.h"

BEG_XE_NAMESPACE

class Archive;

class REFLECT_API IMetaType : public IMetaInfo
{
public:
	IMetaType( const String& Name, MetaType Type, XE::uint64 Size, IMetaInfoPtr Owner );

	~IMetaType();

public:
	XE::uint64 GetSize() const;

public:
	virtual void Serialize( Archive * arc, Variant& val ) const = 0;

private:
	XE::uint64 _Size;
};

END_XE_NAMESAPCE

#endif // __IMETATYPE_H__8929D439_3C4B_4410_85AD_5D3F570075E6
