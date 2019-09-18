/*!
 * \file	AnimationState.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/16
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATIONSTATE_H__DE89A48E_E19F_4BE9_9D74_144BFB0D3029
#define ANIMATIONSTATE_H__DE89A48E_E19F_4BE9_9D74_144BFB0D3029

#include "Type.h"

BEG_XE_NAMESPACE

class ANIMATION_API AnimationState : public XE::Object
{
	OBJECT( AnimationState, Object )

public:
	AnimationState();

	~AnimationState() override;

public:
	virtual void Startup();

	virtual void Entry();

	virtual void Update( XE::float32 val );

	virtual void Exit();

	virtual void Clearup();

public:
	virtual void OnEntry();

	virtual void OnUpdate( XE::float32 val );

	virtual void OnExit();

public:
	bool GetLooped() const;

	void SetLooped( bool val );

	bool GetPlaying() const;

	void SetPlaying( bool val );

	bool GetWaitOut() const;

	void SetWaitOut( bool val );

public:
	const Array<XE::uint32> & GetTransitions() const;

	void SetTransitions( const Array<XE::uint32> & val );

	const Array<AnimationTriggerPtr> & GetTriggers() const;

	void SetTriggers( const Array<AnimationTriggerPtr> & val );

public:
	AnimationControllerPtr GetAnimationController() const;

	void SetAnimationController( const AnimationControllerPtr & val );

private:
	bool _Looped;
	bool _Playing;
	bool _WaitOut;
	XE::float32 _Time;
	XE::float32 _MaxTime;
	Array<XE::uint32> _Transitions;
	AnimationControllerWPtr _Controller;
	Array<AnimationTriggerPtr> _Triggers;
};

class ANIMATION_API AnimationStateAny : public AnimationState
{
	OBJECT( AnimationStateAny, AnimationState )

public:
	AnimationStateAny();

	~AnimationStateAny() override;
};

END_XE_NAMESPACE

#endif // ANIMATIONSTATE_H__DE89A48E_E19F_4BE9_9D74_144BFB0D3029
