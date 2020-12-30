/*!
 * \file	ElementPort.h
 *
 * \author	ZhengYuanQing
 * \date	2020/11/15
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ELEMENTPORT_H__F61060C8_B876_4765_BA29_CC7D0AFB0400
#define ELEMENTPORT_H__F61060C8_B876_4765_BA29_CC7D0AFB0400

#include "BlackboardKey.h"

BEG_AI_NAMESPACE

class AI_API AISlot
{
public:
	XE::String InputPortName;
	XE::String OutputPortName;
	AI::ElementHandle OutputHandle;
};
DECL_META_CLASS( AI_API, AISlot );

class AI_API AIOutput
{
public:
	AI::ElementHandle Handle;
};
DECL_META_CLASS( AI_API, AIOutput );

class AI_API InputPort : public XE::Object
{
	OBJECT( InputPort, Object )

public:
	InputPort() = default;

	~InputPort() override = default;
};

class AI_API OutputPort : public XE::Object
{
	OBJECT( OutputPort, Object )

public:
	OutputPort() = default;

	~OutputPort() override = default;
};

class AI_API VariantInputPort : public AI::InputPort
{
	OBJECT( VariantInputPort, InputPort )

public:
	VariantInputPort() = default;

	~VariantInputPort() override = default;

public:
	XE::Variant Value;
};

class AI_API VariantOutputPort : public AI::OutputPort
{
	OBJECT( VariantOutputPort, OutputPort )

public:
	VariantOutputPort() = default;

	~VariantOutputPort() override = default;

public:
	XE::Variant Result;
};

class AI_API VariantPairInputPort : public AI::InputPort
{
	OBJECT( VariantPairInputPort, InputPort )

public:
	VariantPairInputPort() = default;

	~VariantPairInputPort() override = default;

public:
	XE::Variant First;
	XE::Variant Second;
};

class AI_API VariantPairOutputPort : public AI::OutputPort
{
	OBJECT( VariantPairOutputPort, OutputPort )

public:
	VariantPairOutputPort() = default;

	~VariantPairOutputPort() override = default;

public:
	XE::Variant First;
	XE::Variant Second;
};

class AI_API BoolInputPort : public AI::InputPort
{
	OBJECT( BoolInputPort, InputPort )

public:
	BoolInputPort() = default;

	~BoolInputPort() override = default;

public:
	bool Value;
};

class AI_API BoolOutputPort : public AI::OutputPort
{
	OBJECT( BoolOutputPort, OutputPort )

public:
	BoolOutputPort() = default;

	~BoolOutputPort() override = default;

public:
	bool Result;
};

class AI_API IntegerInputPort : public AI::InputPort
{
	OBJECT( IntegerInputPort, InputPort )

public:
	IntegerInputPort() = default;

	~IntegerInputPort() override = default;

public:
	XE::int64 Value;
};

class AI_API IntegerOutputPort : public AI::OutputPort
{
	OBJECT( IntegerOutputPort, OutputPort )

public:
	IntegerOutputPort() = default;

	~IntegerOutputPort() override = default;

public:
	XE::int64 Result;
};

class AI_API IntegerPairInputPort : public AI::InputPort
{
	OBJECT( IntegerInputPort, InputPort )

public:
	IntegerPairInputPort() = default;

	~IntegerPairInputPort() override = default;

public:
	XE::int64 First;
	XE::int64 Second;
};

class AI_API IntegerPairOutputPort : public AI::OutputPort
{
	OBJECT( IntegerPairOutputPort, OutputPort )

public:
	IntegerPairOutputPort() = default;

	~IntegerPairOutputPort() override = default;

public:
	XE::int64 First;
	XE::int64 Second;
};

class AI_API InvokeInputPort : public AI::InputPort
{
	template< typename InvokeInputPort > friend struct XE::MetaDataCollector;

public:
	typedef InputPort Super;
	
	static XE::IMetaClassPtr GetMetaClassStatic();

	virtual XE::IMetaClassPtr GetMetaClass() const;

public:
	InvokeInputPort() = default;

	~InvokeInputPort() override = default;

public:
	void Init( const XE::IMetaMethodPtr & method );

public:
	XE::Variant This;
	XE::Variant Arg_0;
	XE::Variant Arg_1;
	XE::Variant Arg_2;
	XE::Variant Arg_3;
	XE::Variant Arg_4;
	XE::Variant Arg_5;
	XE::Variant Arg_6;
	XE::Variant Arg_7;
	XE::Variant Arg_8;
	XE::Variant Arg_9;
private:
	XE::IMetaClassPtr _Meta;
};

class AI_API SetVariableInputPort : public AI::InputPort
{
	OBJECT( SetVariableInputPort, InputPort )

public:
	SetVariableInputPort() = default;

	~SetVariableInputPort() override = default;

public:
	XE::Variant This;
	XE::Variant Value;
};

class AI_API GetVariableInputPort : public AI::InputPort
{
	OBJECT( GetVariableInputPort, InputPort )

public:
	GetVariableInputPort() = default;

	~GetVariableInputPort() override = default;

public:
	XE::Variant This;
};

END_AI_NAMESPACE

#endif // ELEMENTPORT_H__F61060C8_B876_4765_BA29_CC7D0AFB0400
