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

#include "Utils/Asset.h"

#include "AIElementPort.h"

BEG_XE_NAMESPACE

class XE_API AIElement : public XE::Object
{
	OBJECT( AIElement, Object )

	friend class Blueprint;

public:
	AIElement();

	~AIElement() override;

public:
	XE::AIElementType GetType() const;

	BlueprintPtr GetBlueprint() const;

	XE::AIElementHandle GetHandle() const;

public:
	const XE::String & GetName() const;

	void SetName( const XE::String & val );

	const XE::Array< XE::AISlot > & GetSlots() const;

	void SetSlots( const XE::Array< XE::AISlot > & val );

protected:
	void SetType( XE::AIElementType val );

private:
	void SetBlueprint( BlueprintPtr val );

	void SetHandle( XE::AIElementHandle val );

protected:
	const XE::AIInputPortPtr & GetInputPort() const;

	void SetInputPort( const XE::AIInputPortPtr & val );

	const XE::AIOutputPortPtr & GetOutputPort() const;

	void SetOutputPort( const XE::AIOutputPortPtr & val );

public:
	void Startup();

	void Execute();
	
	void Clearup();

protected:
	virtual void OnStartup();

	virtual void OnExecute();

	virtual void OnClearup();

private:
	XE::String _Name;
	XE::AIElementType _Type;
	XE::AIElementHandle _Handle;
	XE::AIInputPortPtr _InputPort;
	XE::AIOutputPortPtr _OutputPort;
	XE::Array< XE::AISlot > _Slots;

	XE::BlueprintWPtr _Blueprint;
};

class XE_API DataElement : public XE::AIElement
{
	OBJECT( DataElement, AIElement )

public:
	DataElement();

	~DataElement() override;

protected:
	void OnStartup() override;
};

class XE_API CalcElement : public XE::AIElement
{
	OBJECT( CalcElement, AIElement )

public:
	CalcElement();

	~CalcElement() override;

};

class XE_API NotCalcElement : public XE::CalcElement
{
	OBJECT( NotCalcElement, CalcElement )

public:
	NotCalcElement();

	~NotCalcElement() override;

protected:
	void OnExecute() override;

};

class XE_API RevCalcElement : public XE::CalcElement
{
	OBJECT( RevCalcElement, CalcElement )

public:
	RevCalcElement();

	~RevCalcElement() override;

protected:
	void OnExecute() override;

};

class XE_API IncCalcElement : public XE::CalcElement
{
	OBJECT( IncCalcElement, CalcElement )

public:
	IncCalcElement();

	~IncCalcElement() override;

protected:
	void OnExecute() override;

};

class XE_API DecCalcElement : public XE::CalcElement
{
	OBJECT( DecCalcElement, CalcElement )

public:
	DecCalcElement();

	~DecCalcElement() override;

protected:
	void OnExecute() override;

};

class XE_API NegCalcElement : public XE::CalcElement
{
	OBJECT( NegCalcElement, CalcElement )

public:
	NegCalcElement();

	~NegCalcElement() override;

protected:
	void OnExecute() override;

};

class XE_API AddCalcElement : public XE::CalcElement
{
	OBJECT( AddCalcElement, CalcElement )

public:
	AddCalcElement();

	~AddCalcElement() override;

protected:
	void OnExecute() override;

};

class XE_API SubCalcElement : public XE::CalcElement
{
	OBJECT( SubCalcElement, CalcElement )

public:
	SubCalcElement();

	~SubCalcElement() override;

protected:
	void OnExecute() override;

};

class XE_API MulCalcElement : public XE::CalcElement
{
	OBJECT( MulCalcElement, CalcElement )

public:
	MulCalcElement();

	~MulCalcElement() override;

protected:
	void OnExecute() override;

};

class XE_API DivCalcElement : public XE::CalcElement
{
	OBJECT( DivCalcElement, CalcElement )

public:
	DivCalcElement();

	~DivCalcElement() override;

protected:
	void OnExecute() override;

};

class XE_API ModCalcElement : public XE::CalcElement
{
	OBJECT( AddCalcElement, CalcElement )

public:
	ModCalcElement();

	~ModCalcElement() override;

protected:
	void OnExecute() override;

};

class XE_API XorCalcElement : public XE::CalcElement
{
	OBJECT( AddCalcElement, CalcElement )

public:
	XorCalcElement();

	~XorCalcElement() override;

protected:
	void OnExecute() override;

};

class XE_API AndCalcElement : public XE::CalcElement
{
	OBJECT( AndCalcElement, CalcElement )

public:
	AndCalcElement();

	~AndCalcElement() override;

protected:
	void OnExecute() override;

};

class XE_API OrCalcElement : public XE::CalcElement
{
	OBJECT( OrCalcElement, CalcElement )

public:
	OrCalcElement();

	~OrCalcElement() override;

protected:
	void OnExecute() override;

};

class XE_API GreaterCalcElement : public XE::CalcElement
{
	OBJECT( GreaterCalcElement, CalcElement )

public:
	GreaterCalcElement();

	~GreaterCalcElement() override;

protected:
	void OnExecute() override;

};

class XE_API LessCalcElement : public XE::CalcElement
{
	OBJECT( LessCalcElement, CalcElement )

public:
	LessCalcElement();

	~LessCalcElement() override;

protected:
	void OnExecute() override;

};

class XE_API GreaterEqualCalcElement : public XE::CalcElement
{
	OBJECT( GreaterEqualCalcElement, CalcElement )

public:
	GreaterEqualCalcElement();

	~GreaterEqualCalcElement() override;

protected:
	void OnExecute() override;

};

class XE_API LessEqualCalcElement : public XE::CalcElement
{
	OBJECT( LessEqualCalcElement, CalcElement )

public:
	LessEqualCalcElement();

	~LessEqualCalcElement() override;

protected:
	void OnExecute() override;

};

class XE_API EqualCalcElement : public XE::CalcElement
{
	OBJECT( EqualCalcElement, CalcElement )

public:
	EqualCalcElement();

	~EqualCalcElement() override;

protected:
	void OnExecute() override;

};

class XE_API NotEqualCalcElement : public XE::CalcElement
{
	OBJECT( NotEqualCalcElement, CalcElement )

public:
	NotEqualCalcElement();

	~NotEqualCalcElement() override;

protected:
	void OnExecute() override;

};

class XE_API LogicElement : public XE::AIElement
{
	OBJECT( LogicElement, AIElement )

public:
	LogicElement();

	~LogicElement() override;

};

class XE_API IfLogicElement : public XE::LogicElement
{
	OBJECT( IfLogicElement, LogicElement )

public:
	IfLogicElement();

	~IfLogicElement() override;

protected:
	void OnExecute() override;

private:
	XE::AIOutput _IfOutput;
	XE::AIOutput _ElseOutput;
};

class XE_API ForLogicElement : public XE::LogicElement
{
	OBJECT( ForLogicElement, LogicElement )

public:
	ForLogicElement();

	~ForLogicElement() override;

protected:
	void OnExecute() override;

private:
	XE::AIOutput _LoopOutput;
	XE::AIOutput _CompletedOutput;
};

class XE_API SwitchLogicElement : public XE::LogicElement
{
	OBJECT( SwitchLogicElement, LogicElement )

public:
	SwitchLogicElement();

	~SwitchLogicElement() override;

protected:
	void OnExecute() override;

private:
	XE::AIOutput _CaseOutput0;
	XE::AIOutput _CaseOutput1;
	XE::AIOutput _CaseOutput2;
	XE::AIOutput _CaseOutput3;
	XE::AIOutput _CaseOutput4;
	XE::AIOutput _CaseOutput5;
	XE::AIOutput _CaseOutput6;
	XE::AIOutput _CaseOutput7;
	XE::AIOutput _CaseOutput8;
	XE::AIOutput _CaseOutput9;
	XE::AIOutput _DefaultOutput;
};

class XE_API SequenceLogicElement : public XE::LogicElement
{
	OBJECT( SequenceLogicElement, LogicElement )

public:
	SequenceLogicElement();

	~SequenceLogicElement() override;

protected:
	void OnExecute() override;

private:
	XE::AIOutput _Output0;
	XE::AIOutput _Output1;
	XE::AIOutput _Output2;
	XE::AIOutput _Output3;
	XE::AIOutput _Output4;
	XE::AIOutput _Output5;
	XE::AIOutput _Output6;
	XE::AIOutput _Output7;
	XE::AIOutput _Output8;
	XE::AIOutput _Output9;
};

class XE_API EventElement : public XE::AIElement
{
	OBJECT( EventElement, AIElement )

public:
	EventElement();

	~EventElement() override;

public:
	XE::EventHandle GetListenerEvent() const;

	void SetListenerEvent( XE::EventHandle val );

protected:
	void OnExecute() override;

private:
	XE::AIOutput _Output;
	XE::EventHandle _ListenerEvent;
};

class XE_API ActionElement : public XE::AIElement
{
	OBJECT( ActionElement, AIElement )

public:
	ActionElement();

	~ActionElement() override;

public:
	const XE::String & GetMethodFullName() const;

	void SetMethodFullName( const XE::String & val );

protected:
	void OnStartup() override;

	void OnExecute() override;

private:
	XE::AIOutput _Output;
	XE::String _MethodFullName;
};

class XE_API VariableElement : public XE::AIElement
{
	OBJECT( VariableElement, AIElement )

public:
	VariableElement();

	~VariableElement() override;
};

class XE_API SetVariableElement : public XE::VariableElement
{
	OBJECT( SetVariableElement, VariableElement )

public:
	SetVariableElement();

	~SetVariableElement() override;

public:
	const XE::AIOutput & GetOutput() const;

	void SetOutput( const XE::AIOutput & val );

	const XE::String & GetPropertyFullName() const;

	void SetPropertyFullName( const XE::String & val );

protected:
	void OnExecute() override;

private:
	XE::AIOutput _Output;
	XE::String _PropertyFullName;
};

class XE_API GetVariableElement : public XE::VariableElement
{
	OBJECT( GetVariableElement, VariableElement )

public:
	GetVariableElement();

	~GetVariableElement() override;

public:
	const XE::String & GetPropertyFullName() const;

	void SetPropertyFullName( const XE::String & val );

protected:
	void OnExecute() override;

private:
	XE::String _PropertyFullName;
};

class XE_API SetBlackboardKeyElement : public XE::VariableElement
{
	OBJECT( SetBlackboardKeyElement, VariableElement )

public:
	SetBlackboardKeyElement();

	~SetBlackboardKeyElement() override;

public:
	const XE::AIOutput & GetOutput() const;

	void SetOutput( const XE::AIOutput & val );

	const XE::BlackboardKey & GetBlackboardKey() const;

	void SetBlackboardKey( const XE::BlackboardKey & val );

protected:
	void OnExecute() override;

private:
	XE::AIOutput _Output;
	XE::BlackboardKey _BlackboardKey;
};

class XE_API GetBlackboardKeyElement : public XE::VariableElement
{
	OBJECT( GetBlackboardKeyElement, VariableElement )

public:
	GetBlackboardKeyElement();

	~GetBlackboardKeyElement() override;

public:
	const XE::BlackboardKey & GetBlackboardKey() const;

	void SetBlackboardKey( const XE::BlackboardKey & val );

protected:
	void OnExecute() override;

private:
	XE::BlackboardKey _BlackboardKey;
};

END_XE_NAMESPACE

#endif // AIELEMENT_H__7AD331C3_9C5F_41AE_8D41_DE75C3114690
