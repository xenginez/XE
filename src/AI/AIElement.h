/*!
 * \file	AIElement.h
 *
 * \author	ZhengYuanQing
 * \date	2020/11/10
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef AIELEMENT_H__7AD331C3_9C5F_41AE_8D41_DE75C3114690
#define AIELEMENT_H__7AD331C3_9C5F_41AE_8D41_DE75C3114690

#include "BlackboardKey.h"

BEG_XE_NAMESPACE

class XE_API AIElement : public XE::Object
{
	OBJECT( AIElement, Object )

	friend class Blueprint;

public:
	AIElement();

	~AIElement() override;

public:
	BlueprintPtr GetBlueprint() const;

public:
	const XE::String & GetName() const;

	void SetName( const XE::String & val );

	XE::AIElementHandle GetHandle() const;

	void SetHandle( XE::AIElementHandle val );

	XE::AIElementHandle GetNextHandle() const;

	void SetNextHandle( XE::AIElementHandle val );

	const XE::Map< XE::String, XE::Pair< XE::AIElementHandle, XE::String > > & GetIn() const;

	void SetIn( const XE::Map< XE::String, XE::Pair< XE::AIElementHandle, XE::String > > & val );

private:
	void SetBlueprint( BlueprintPtr val );

public:
	void Execute();

protected:
	virtual void OnExecute();

private:
	XE::String _Name;
	XE::AIElementHandle _Handle;
	XE::AIElementHandle _NextHandle;
	XE::Map< XE::String, XE::Pair< XE::AIElementHandle, XE::String > > _In;

	XE::BlueprintWPtr _Blueprint;

protected:
	XE::Map< XE::String, XE::Variant > _OutParams;
};

END_XE_NAMESPACE

#endif // AIELEMENT_H__7AD331C3_9C5F_41AE_8D41_DE75C3114690
