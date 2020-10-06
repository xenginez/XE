/*!
 * \file	AnimationCondition.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/17
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATIONCONDITION_H__7AD122B4_3877_4EE4_85BC_BE29E827F53C
#define ANIMATIONCONDITION_H__7AD122B4_3877_4EE4_85BC_BE29E827F53C

#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API AnimationCondition : public XE::Object
{
	OBJECT( AnimationCondition, Object )

public:
	AnimationCondition();

	~AnimationCondition() override;

public:
	virtual bool Condition() const = 0;

public:
	AnimationControllerPtr GetAnimationController() const;

	void SetAnimationController( const AnimationControllerPtr & val );

private:
	AnimationControllerWPtr _Controller;
};

class XE_API AnimationConditionBool : public AnimationCondition
{
	OBJECT( AnimationConditionBool, AnimationCondition )

public:
	AnimationConditionBool();

	~AnimationConditionBool() override;

public:
	bool Condition() const override;

private:
	bool _DefValue;
	XE::String _KeyValue;
};

class XE_API AnimationConditionInt : public AnimationCondition
{
	OBJECT( AnimationConditionInt, AnimationCondition )

public:
	AnimationConditionInt();

	~AnimationConditionInt() override;

public:
	bool Condition() const override;

private:
	XE::int32 _DefValue;
	XE::String _KeyValue;
	AnimationCompare _Compare;
};

class XE_API AnimationConditionFloat : public AnimationCondition
{
	OBJECT( AnimationConditionFloat, AnimationCondition )

public:
	AnimationConditionFloat();

	~AnimationConditionFloat() override;

public:
	bool Condition() const override;

private:
	XE::String _KeyValue;
	XE::float32 _DefValue;
	AnimationCompare _Compare;
};

class XE_API AnimationConditionString : public AnimationCondition
{
	OBJECT( AnimationConditionString, AnimationCondition )

public:
	AnimationConditionString();

	~AnimationConditionString() override;

public:
	bool Condition() const override;

private:
	XE::String _KeyValue;
	XE::String _DefValue;
};

END_XE_NAMESPACE

#endif // ANIMATIONCONDITION_H__7AD122B4_3877_4EE4_85BC_BE29E827F53C
