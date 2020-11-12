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

public:
	void Execute();

protected:
	virtual void OnExecute();

private:
	XE::String _Name;
	XE::AIElementType _Type;
	XE::AIElementHandle _Handle;
	XE::AIElementHandle _NextHandle;

	XE::BlueprintWPtr _Blueprint;
};


/*
�¼���Ԫ��events��������������������ʱ���ĸ���unit��ͨ��������ʾΪ��ɫ��������һ��Flow Graph�����
���Ԫ��actions������������ʲô���ĸ���unit
���ݵ�Ԫ��data��������������ݵ�unit����������ԡ�Literal����β��unit����Щ��Ԫ����������ñ��������һ��Unity���ݣ����縡������float�����ַ�����string�������ߣ�ray���������֣�layer mask����
���㵥Ԫ��calculation���������������ݡ��������ݵĸ���unit������Ӽ��˳���������ѧ������
������Ԫ��variable�����������û��޸ı�����unit����Ҫ��Set Variable��Get Variable����
�߼���Ԫ��logic������������Graph�������߼�����ĵ�Ԫ������Branch���൱�ڡ�if... else...��������䣩��Loop���൱�ڡ�for...��ѭ����䣩�ȵ�
*/

class XE_API DataElement : public XE::AIElement
{
	OBJECT( DataElement, AIElement )

public:
	DataElement();

	~DataElement() override;
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
