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

#include "Utils/Asset.h"

#include "BlackboardKey.h"

BEG_XE_NAMESPACE

class XE_API AIElement : public XE::Object
{
	OBJECT( AIElement, Object )

private:
	friend class BluePrint;

public:
	AIElement();

	~AIElement() override;

public:
	const XE::String & GetName() const;

	void SetName( const XE::String & val );

	XE::AIElementHandle GetHandle() const;

	void SetHandle( XE::AIElementHandle val );

	XE::AIElementHandle GetNextElement() const;

	void SetNextElement( XE::AIElementHandle val );

	const XE::Map< XE::AIElementHandle, XE::Pair< XE::String, XE::String > > & GetOutParameter() const;

	void SetOutParameter( const XE::Map< XE::AIElementHandle, XE::Pair< XE::String, XE::String > > & val );

public:
	XE::BluePrintPtr GetBluePrint() const;

private:
	void SetBluePrint( XE::BluePrintPtr val );

public:
	virtual void Startup();

	virtual void Update( XE::float32 dt );

	virtual void Clearup();

protected:
	virtual void OnStartup();

	virtual void OnUpdate( XE::float32 dt );

	virtual void OnClearup();

private:
	XE::String _Name;
	XE::AIElementHandle _Handle;
	XE::AIElementHandle _NextElement;
	XE::Map< XE::AIElementHandle, XE::Pair< XE::String, XE::String > > _OutParameter;

	XE::BluePrintWPtr _BluePrint;
};

class XE_API SubElement : public XE::AIElement
{
	OBJECT( SubElement, AIElement )

public:
	SubElement();

	~SubElement();

public:
	const XE::AIModulePtr & GetSubAIModule() const;

	void SetSubAIModule( const XE::AIModulePtr & val );

	const XE::Map<XE::BlackboardKey, XE::BlackboardKey> & GetConnectKeys() const;

	void SetConnectKeys( const XE::Map<XE::BlackboardKey, XE::BlackboardKey> & val );

protected:
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::float32 dt ) override;

	virtual void OnClearup() override;

private:
	XE::AIModulePtr _SubAI;
	XE::Map<XE::BlackboardKey, XE::BlackboardKey> _ConnectKeys;
};

END_XE_NAMESPACE

#endif // ITEM_H__06FDB718_96FC_4CE4_94A5_5D05106F608B
