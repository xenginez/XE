/*!
 * \file	Element.h
 *
 * \author	ZhengYuanQing
 * \date	2020/11/10
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ELEMENT_H__7AD331C3_9C5F_41AE_8D41_DE75C3114690
#define ELEMENT_H__7AD331C3_9C5F_41AE_8D41_DE75C3114690

#include "ElementPort.h"

BEG_AI_NAMESPACE

class AI_API Element : public XE::Object
{
	OBJECT( Element, Object )

	friend class Blueprint;

public:
	Element();

	~Element() override;

public:
	AI::AIElementType GetType() const;

	BlueprintPtr GetBlueprint() const;

	AI::ElementHandle GetHandle() const;

public:
	const XE::String & GetName() const;

	void SetName( const XE::String & val );

	const XE::Array< AI::AISlot > & GetSlots() const;

	void SetSlots( const XE::Array< AI::AISlot > & val );

protected:
	void SetType( AI::AIElementType val );

private:
	void SetBlueprint( BlueprintPtr val );

	void SetHandle( AI::ElementHandle val );

protected:
	const AI::InputPortPtr & GetInputPort() const;

	void SetInputPort( const AI::InputPortPtr & val );

	const AI::OutputPortPtr & GetOutputPort() const;

	void SetOutputPort( const AI::OutputPortPtr & val );

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
	AI::AIElementType _Type;
	AI::ElementHandle _Handle;
	AI::InputPortPtr _InputPort;
	AI::OutputPortPtr _OutputPort;
	XE::Array< AI::AISlot > _Slots;

	AI::BlueprintWPtr _Blueprint;
};

class AI_API DataElement : public AI::Element
{
	OBJECT( DataElement, Element )

public:
	DataElement();

	~DataElement() override;

protected:
	void OnStartup() override;
};

class AI_API CalcElement : public AI::Element
{
	OBJECT( CalcElement, Element )

public:
	CalcElement();

	~CalcElement() override;

};

class AI_API NotCalcElement : public AI::CalcElement
{
	OBJECT( NotCalcElement, CalcElement )

public:
	NotCalcElement();

	~NotCalcElement() override;

protected:
	void OnExecute() override;

};

class AI_API RevCalcElement : public AI::CalcElement
{
	OBJECT( RevCalcElement, CalcElement )

public:
	RevCalcElement();

	~RevCalcElement() override;

protected:
	void OnExecute() override;

};

class AI_API IncCalcElement : public AI::CalcElement
{
	OBJECT( IncCalcElement, CalcElement )

public:
	IncCalcElement();

	~IncCalcElement() override;

protected:
	void OnExecute() override;

};

class AI_API DecCalcElement : public AI::CalcElement
{
	OBJECT( DecCalcElement, CalcElement )

public:
	DecCalcElement();

	~DecCalcElement() override;

protected:
	void OnExecute() override;

};

class AI_API NegCalcElement : public AI::CalcElement
{
	OBJECT( NegCalcElement, CalcElement )

public:
	NegCalcElement();

	~NegCalcElement() override;

protected:
	void OnExecute() override;

};

class AI_API AddCalcElement : public AI::CalcElement
{
	OBJECT( AddCalcElement, CalcElement )

public:
	AddCalcElement();

	~AddCalcElement() override;

protected:
	void OnExecute() override;

};

class AI_API SubCalcElement : public AI::CalcElement
{
	OBJECT( SubCalcElement, CalcElement )

public:
	SubCalcElement();

	~SubCalcElement() override;

protected:
	void OnExecute() override;

};

class AI_API MulCalcElement : public AI::CalcElement
{
	OBJECT( MulCalcElement, CalcElement )

public:
	MulCalcElement();

	~MulCalcElement() override;

protected:
	void OnExecute() override;

};

class AI_API DivCalcElement : public AI::CalcElement
{
	OBJECT( DivCalcElement, CalcElement )

public:
	DivCalcElement();

	~DivCalcElement() override;

protected:
	void OnExecute() override;

};

class AI_API ModCalcElement : public AI::CalcElement
{
	OBJECT( AddCalcElement, CalcElement )

public:
	ModCalcElement();

	~ModCalcElement() override;

protected:
	void OnExecute() override;

};

class AI_API XorCalcElement : public AI::CalcElement
{
	OBJECT( AddCalcElement, CalcElement )

public:
	XorCalcElement();

	~XorCalcElement() override;

protected:
	void OnExecute() override;

};

class AI_API AndCalcElement : public AI::CalcElement
{
	OBJECT( AndCalcElement, CalcElement )

public:
	AndCalcElement();

	~AndCalcElement() override;

protected:
	void OnExecute() override;

};

class AI_API OrCalcElement : public AI::CalcElement
{
	OBJECT( OrCalcElement, CalcElement )

public:
	OrCalcElement();

	~OrCalcElement() override;

protected:
	void OnExecute() override;

};

class AI_API GreaterCalcElement : public AI::CalcElement
{
	OBJECT( GreaterCalcElement, CalcElement )

public:
	GreaterCalcElement();

	~GreaterCalcElement() override;

protected:
	void OnExecute() override;

};

class AI_API LessCalcElement : public AI::CalcElement
{
	OBJECT( LessCalcElement, CalcElement )

public:
	LessCalcElement();

	~LessCalcElement() override;

protected:
	void OnExecute() override;

};

class AI_API GreaterEqualCalcElement : public AI::CalcElement
{
	OBJECT( GreaterEqualCalcElement, CalcElement )

public:
	GreaterEqualCalcElement();

	~GreaterEqualCalcElement() override;

protected:
	void OnExecute() override;

};

class AI_API LessEqualCalcElement : public AI::CalcElement
{
	OBJECT( LessEqualCalcElement, CalcElement )

public:
	LessEqualCalcElement();

	~LessEqualCalcElement() override;

protected:
	void OnExecute() override;

};

class AI_API EqualCalcElement : public AI::CalcElement
{
	OBJECT( EqualCalcElement, CalcElement )

public:
	EqualCalcElement();

	~EqualCalcElement() override;

protected:
	void OnExecute() override;

};

class AI_API NotEqualCalcElement : public AI::CalcElement
{
	OBJECT( NotEqualCalcElement, CalcElement )

public:
	NotEqualCalcElement();

	~NotEqualCalcElement() override;

protected:
	void OnExecute() override;

};

class AI_API LogicElement : public AI::Element
{
	OBJECT( LogicElement, Element )

public:
	LogicElement();

	~LogicElement() override;

};

class AI_API IfLogicElement : public AI::LogicElement
{
	OBJECT( IfLogicElement, LogicElement )

public:
	IfLogicElement();

	~IfLogicElement() override;

protected:
	void OnExecute() override;

private:
	AI::AIOutput _IfOutput;
	AI::AIOutput _ElseOutput;
};

class AI_API ForLogicElement : public AI::LogicElement
{
	OBJECT( ForLogicElement, LogicElement )

public:
	ForLogicElement();

	~ForLogicElement() override;

protected:
	void OnExecute() override;

private:
	AI::AIOutput _LoopOutput;
	AI::AIOutput _CompletedOutput;
};

class AI_API SwitchLogicElement : public AI::LogicElement
{
	OBJECT( SwitchLogicElement, LogicElement )

public:
	SwitchLogicElement();

	~SwitchLogicElement() override;

protected:
	void OnExecute() override;

private:
	AI::AIOutput _CaseOutput0;
	AI::AIOutput _CaseOutput1;
	AI::AIOutput _CaseOutput2;
	AI::AIOutput _CaseOutput3;
	AI::AIOutput _CaseOutput4;
	AI::AIOutput _CaseOutput5;
	AI::AIOutput _CaseOutput6;
	AI::AIOutput _CaseOutput7;
	AI::AIOutput _CaseOutput8;
	AI::AIOutput _CaseOutput9;
	AI::AIOutput _DefaultOutput;
};

class AI_API SequenceLogicElement : public AI::LogicElement
{
	OBJECT( SequenceLogicElement, LogicElement )

public:
	SequenceLogicElement();

	~SequenceLogicElement() override;

protected:
	void OnExecute() override;

private:
	AI::AIOutput _Output0;
	AI::AIOutput _Output1;
	AI::AIOutput _Output2;
	AI::AIOutput _Output3;
	AI::AIOutput _Output4;
	AI::AIOutput _Output5;
	AI::AIOutput _Output6;
	AI::AIOutput _Output7;
	AI::AIOutput _Output8;
	AI::AIOutput _Output9;
};

class AI_API EventElement : public AI::Element
{
	OBJECT( EventElement, Element )

public:
	EventElement();

	~EventElement() override;

public:
	XE::EventHandle GetListenerEvent() const;

	void SetListenerEvent( XE::EventHandle val );

protected:
	void OnExecute() override;

private:
	AI::AIOutput _Output;
	XE::EventHandle _ListenerEvent;
};

class AI_API ActionElement : public AI::Element
{
	OBJECT( ActionElement, Element )

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
	AI::AIOutput _Output;
	XE::String _MethodFullName;
};

class AI_API VariableElement : public AI::Element
{
	OBJECT( VariableElement, Element )

public:
	VariableElement();

	~VariableElement() override;
};

class AI_API SetVariableElement : public AI::VariableElement
{
	OBJECT( SetVariableElement, VariableElement )

public:
	SetVariableElement();

	~SetVariableElement() override;

public:
	const AI::AIOutput & GetOutput() const;

	void SetOutput( const AI::AIOutput & val );

	const XE::String & GetPropertyFullName() const;

	void SetPropertyFullName( const XE::String & val );

protected:
	void OnExecute() override;

private:
	AI::AIOutput _Output;
	XE::String _PropertyFullName;
};

class AI_API GetVariableElement : public AI::VariableElement
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

class AI_API SetBlackboardKeyElement : public AI::VariableElement
{
	OBJECT( SetBlackboardKeyElement, VariableElement )

public:
	SetBlackboardKeyElement();

	~SetBlackboardKeyElement() override;

public:
	const AI::AIOutput & GetOutput() const;

	void SetOutput( const AI::AIOutput & val );

	const AI::BlackboardKey & GetBlackboardKey() const;

	void SetBlackboardKey( const AI::BlackboardKey & val );

protected:
	void OnExecute() override;

private:
	AI::AIOutput _Output;
	AI::BlackboardKey _BlackboardKey;
};

class AI_API GetBlackboardKeyElement : public AI::VariableElement
{
	OBJECT( GetBlackboardKeyElement, VariableElement )

public:
	GetBlackboardKeyElement();

	~GetBlackboardKeyElement() override;

public:
	const AI::BlackboardKey & GetBlackboardKey() const;

	void SetBlackboardKey( const AI::BlackboardKey & val );

protected:
	void OnExecute() override;

private:
	AI::BlackboardKey _BlackboardKey;
};

END_AI_NAMESPACE

#endif // ELEMENT_H__7AD331C3_9C5F_41AE_8D41_DE75C3114690
