/*!
 * \file	AnimationTrigger.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/18
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATIONTRIGGER_H__5F6822EE_2525_4899_9028_FE7E463643B0
#define ANIMATIONTRIGGER_H__5F6822EE_2525_4899_9028_FE7E463643B0

#include "Type.h"

BEG_XE_NAMESPACE

class ANIMATION_API AnimationTrigger : public XE::Object
{
	OBJECT( AnimationTrigger, Object )

public:
	friend class AnimationState;

public:
	AnimationTrigger();

	~AnimationTrigger() override;

public:
	XE::float32 GetTime() const;

	const XE::Variant & GetData() const;

private:
	bool _Sended;
	XE::float32 _Time;
	XE::Variant _Data;
};

DECL_EVENT( ANIMATION_TRIGGER, "sender: animation state, parameter: animation trigger", AnimationTrigger );

END_XE_NAMESPACE

#endif // ANIMATIONTRIGGER_H__5F6822EE_2525_4899_9028_FE7E463643B0
