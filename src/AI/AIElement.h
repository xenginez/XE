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

	XE::AIElementHandle GetNextHandle() const;

	void SetNextHandle( XE::AIElementHandle val );

protected:
	void SetType( XE::AIElementType val );

private:
	void SetBlueprint( BlueprintPtr val );

	void SetHandle( XE::AIElementHandle val );

private:
	XE::String _Name;
	XE::AIElementType _Type;
	XE::AIElementHandle _Handle;
	XE::AIElementHandle _NextHandle;

	XE::BlueprintWPtr _Blueprint;
};


/*
事件单元（events）：决定“当……发生时”的各种unit，通常都会显示为绿色，被用在一个Flow Graph的起点
命令单元（actions）：决定“做什么”的各种unit
数据单元（data）：输入各种数据的unit，比如各种以“Literal”结尾的unit。这些单元可以无需调用变量而获得一个Unity数据，比如浮点数（float）、字符串（string）、光线（ray）、层遮罩（layer mask）等
计算单元（calculation）：用来处理数据、计算数据的各种unit，比如加减乘除，各种数学函数等
变量单元（variable）：用来调用或修改变量的unit，主要是Set Variable和Get Variable两个
逻辑单元（logic）：用来控制Graph的运行逻辑走向的单元，比如Branch（相当于“if... else...”条件语句）和Loop（相当于“for...”循环语句）等等
*/

class XE_API SubElement : public XE::AIElement
{
	OBJECT( SubElement, AIElement )

public:
	SubElement();

	~SubElement() override;

public:
	void Startup();

	void Enter();

	void Execute();

	void Quit();

	void Clearup();

public:
	void AssetLoad() override;

private:
	XE::AssetInstance< XE::AIModule > _AIModule;
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

private:
	XE::Variant _Value;
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

	XE::EventHandle GetListenerEvent() const;

	void SetListenerEvent( XE::EventHandle val );

public:
	void Execute();

private:
	XE::Variant _Value;
	XE::EventHandle _ListenerEvent;
};

class XE_API ActionElement : public XE::AIElement
{
	OBJECT( ActionElement, AIElement )

public:
	ActionElement();

	~ActionElement() override;
};

class XE_API VariableElement : public XE::AIElement
{
	OBJECT( VariableElement, AIElement )

public:
	VariableElement();

	~VariableElement() override;
};

END_XE_NAMESPACE

#endif // AIELEMENT_H__7AD331C3_9C5F_41AE_8D41_DE75C3114690
