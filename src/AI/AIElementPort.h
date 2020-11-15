/*!
 * \file	AIElementPort.h
 *
 * \author	ZhengYuanQing
 * \date	2020/11/15
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef AIELEMENTPORT_H__F61060C8_B876_4765_BA29_CC7D0AFB0400
#define AIELEMENTPORT_H__F61060C8_B876_4765_BA29_CC7D0AFB0400

#include "BlackboardKey.h"

BEG_XE_NAMESPACE

class XE_API AISlot
{
public:
	XE::String InputPortName;
	XE::String OutputPortName;
	XE::AIElementHandle OutputHandle;
};
DECL_META_CLASS( XE_API, AISlot );

class XE_API AIOutput
{
public:
	XE::AIElementHandle Handle;
};
DECL_META_CLASS( XE_API, AIOutput );

class XE_API AIInputPort : public XE::Object
{
	OBJECT( AIInputPort, Object )

public:
	AIInputPort() = default;

	~AIInputPort() override = default;
};

class XE_API AIOutputPort : public XE::Object
{
	OBJECT( AIOutputPort, Object )

public:
	AIOutputPort() = default;

	~AIOutputPort() override = default;
};

class XE_API VariantInputPort : public XE::AIInputPort
{
	OBJECT( VariantInputPort, AIInputPort )

public:
	VariantInputPort() = default;

	~VariantInputPort() override = default;

public:
	XE::Variant Value;
};

class XE_API VariantOutputPort : public XE::AIOutputPort
{
	OBJECT( VariantOutputPort, AIOutputPort )

public:
	VariantOutputPort() = default;

	~VariantOutputPort() override = default;

public:
	XE::Variant Result;
};

class XE_API VariantPairInputPort : public XE::AIInputPort
{
	OBJECT( VariantPairInputPort, AIInputPort )

public:
	VariantPairInputPort() = default;

	~VariantPairInputPort() override = default;

public:
	XE::Variant First;
	XE::Variant Second;
};

class XE_API VariantPairOutputPort : public XE::AIOutputPort
{
	OBJECT( VariantPairOutputPort, AIOutputPort )

public:
	VariantPairOutputPort() = default;

	~VariantPairOutputPort() override = default;

public:
	XE::Variant First;
	XE::Variant Second;
};

class XE_API BoolInputPort : public XE::AIInputPort
{
	OBJECT( BoolInputPort, AIInputPort )

public:
	BoolInputPort() = default;

	~BoolInputPort() override = default;

public:
	bool Value;
};

class XE_API BoolOutputPort : public XE::AIOutputPort
{
	OBJECT( BoolOutputPort, AIOutputPort )

public:
	BoolOutputPort() = default;

	~BoolOutputPort() override = default;

public:
	bool Result;
};

class XE_API IntegerInputPort : public XE::AIInputPort
{
	OBJECT( IntegerInputPort, AIInputPort )

public:
	IntegerInputPort() = default;

	~IntegerInputPort() override = default;

public:
	XE::int64 Value;
};

class XE_API IntegerOutputPort : public XE::AIOutputPort
{
	OBJECT( IntegerOutputPort, AIOutputPort )

public:
	IntegerOutputPort() = default;

	~IntegerOutputPort() override = default;

public:
	XE::int64 Result;
};

class XE_API IntegerPairInputPort : public XE::AIInputPort
{
	OBJECT( IntegerInputPort, AIInputPort )

public:
	IntegerInputPort() = default;

	~IntegerInputPort() override = default;

public:
	XE::int64 First;
	XE::int64 Second;
};

class XE_API IntegerPairOutputPort : public XE::AIOutputPort
{
	OBJECT( IntegerPairOutputPort, AIOutputPort )

public:
	IntegerPairOutputPort() = default;

	~IntegerPairOutputPort() override = default;

public:
	XE::int64 First;
	XE::int64 Second;
};

class XE_API InvokeInputPort : public XE::AIInputPort
{
	template< typename InvokeInputPort > friend struct XE::MetaDataCollector;

public:
	typedef AIInputPort Super;
	
	static XE::IMetaClassPtr GetMetaClassStatic();

	virtual XE::IMetaClassPtr GetMetaClass() const;

public:
	InvokeInputPort() = default;

	~InvokeInputPort() override = default;

public:
	void Init( const XE::IMetaMethodPtr & method );

public:
	XE::Map< XE::String, XE::Variant > Parameter;

private:
	XE::IMetaClassPtr _Meta;
};

class XE_API SetVariableInputPort : public XE::AIInputPort
{
	OBJECT( SetVariableInputPort, AIInputPort )

public:
	SetVariableInputPort() = default;

	~SetVariableInputPort() override = default;

public:
	XE::Variant This;
	XE::Variant Value;
};

class XE_API GetVariableInputPort : public XE::AIInputPort
{
	OBJECT( GetVariableInputPort, AIInputPort )

public:
	GetVariableInputPort() = default;

	~GetVariableInputPort() override = default;

public:
	XE::Variant This;
};

END_XE_NAMESPACE

#endif // AIELEMENTPORT_H__F61060C8_B876_4765_BA29_CC7D0AFB0400
