/*!
 * \file	Item.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/15
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ITEM_H__06FDB718_96FC_4CE4_94A5_5D05106F608B
#define ITEM_H__06FDB718_96FC_4CE4_94A5_5D05106F608B

#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API Item : public XE::Object
{
	OBJECT( Item, Object )

public:
	Item();

	~Item() override;

public:
	const XE::String & GetName() const;

	void SetName( const XE::String & val );

private:
	XE::String _Name;
};

END_XE_NAMESPACE

#endif // ITEM_H__06FDB718_96FC_4CE4_94A5_5D05106F608B
