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

class XE_API AIInputPort
{
};
DECL_META_CLASS( XE_API, AIInputPort );

class XE_API AIOutputPort
{
};
DECL_META_CLASS( XE_API, AIOutputPort );

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

public:
	void Execute();
	
protected:
	virtual void OnExecute();

	virtual XE::Variant GetOutputValue( const XE::String & val );

	virtual void SetInputValue( const XE::String & name, const XE::Variant & val );

private:
	XE::String _Name;
	XE::AIElementType _Type;
	XE::AIElementHandle _Handle;
	XE::Array< XE::AISlot > _Slots;

	XE::BlueprintWPtr _Blueprint;
};

class XE_API DataElement : public XE::AIElement
{
	OBJECT( DataElement, AIElement )

public:
	DataElement();

	~DataElement() override;

public:
	const XE::Variant & GetValue() const;

	void SetValue( const XE::Variant & val );

protected:
	XE::Variant GetOutputValue( const XE::String & val ) override;

	void SetInputValue( const XE::String & name, const XE::Variant & val ) override;

private:
	XE::Variant _Value;
	XE::AIOutputPort _ResultOutputPort;
};

class XE_API CalcElement : public XE::AIElement
{
	OBJECT( CalcElement, AIElement )

public:
	CalcElement();

	~CalcElement() override;

};

class XE_API LogicElement : public XE::AIElement
{
	OBJECT( LogicElement, AIElement )

public:
	LogicElement();

	~LogicElement() override;

public:
	const XE::AIOutput & GetOutput() const;

	void SetOutput( const XE::AIOutput & val );

private:
	XE::AIOutput _Output;
};

class XE_API EventElement : public XE::AIElement
{
	OBJECT( EventElement, AIElement )

public:
	EventElement();

	~EventElement() override;

public:
	const XE::Variant & GetValue() const;

	void SetValue( const XE::Variant & val );

	const XE::AIOutput & GetOutput() const;

	void SetOutput( const XE::AIOutput & val );

	XE::EventHandle GetListenerEvent() const;

	void SetListenerEvent( XE::EventHandle val );

private:
	XE::Variant _Value;
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
	const XE::AIOutput & GetOutput() const;

	void SetOutput( const XE::AIOutput & val );

	const XE::String & GetMethodFullName() const;

	void SetMethodFullName( const XE::String & val );

protected:
	void OnExecute() override;

	XE::Variant GetOutputValue( const XE::String & val ) override;

	void SetInputValue( const XE::String & name, const XE::Variant & val ) override;

private:
	XE::AIOutput _Output;
	XE::String _MethodFullName;

	XE::Variant _This;
	XE::Variant _Result;
	XE::Array< XE::Variant > _Params;
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

	void SetInputValue( const XE::String & name, const XE::Variant & val ) override;

private:
	XE::AIOutput _Output;
	XE::String _PropertyFullName;
	XE::AIInputPort _ThisInputPort;
	XE::AIInputPort _ValueInputPort;

	XE::Variant _This;
	XE::Variant _Value;
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
	XE::Variant GetOutputValue( const XE::String & val ) override;

	void SetInputValue( const XE::String & name, const XE::Variant & val ) override;

private:
	XE::String _PropertyFullName;
	XE::AIInputPort _ThisInputPort;
	XE::AIOutputPort _ResultOutputPort;

	XE::Variant _This;
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
	void SetInputValue( const XE::String & name, const XE::Variant & val ) override;

private:
	XE::AIOutput _Output;
	XE::AIInputPort _ValueInputPort;
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
	XE::Variant GetOutputValue( const XE::String & val ) override;

private:
	XE::BlackboardKey _BlackboardKey;
	XE::AIOutputPort _ResultOutputPort;
};

END_XE_NAMESPACE

#endif // AIELEMENT_H__7AD331C3_9C5F_41AE_8D41_DE75C3114690
