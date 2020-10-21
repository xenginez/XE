/*!
 * \file	AnimationState.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/19
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATIONSTATE_H__C48F9826_7C1E_44A2_B4A1_1F579B74E9A8
#define ANIMATIONSTATE_H__C48F9826_7C1E_44A2_B4A1_1F579B74E9A8

#include "AI/State.h"

#include "AnimationEvent.h"

BEG_XE_NAMESPACE

class XE_API AnimationState : public XE::State
{
	OBJECT( AnimationState, State )

public:
	AnimationState();

	~AnimationState() override;

public:
	bool GetLoop() const;

	void SetLoop( bool val );

	XE::float32 GetTime() const;

	void SetTime( XE::float32 val );

	XE::float32 GetSpeed() const;

	void SetSpeed( XE::float32 val );

public:
	void AddAnimationEvent( const XE::AnimationEvent & val );

	void RemoveAnimationEvent( XE::float32 val );

	const XE::Array< XE::AnimationEvent > & GetAnimationEvents() const;

public:
	void OnStartup() override;

	void OnUpdate( XE::float32 dt ) override;

	void OnClearup() override;

private:
	bool _Loop = false;
	XE::float32 _Time = 0.0f;
	XE::float32 _Speed = 1.0f;
	XE::Array< XE::AnimationEvent > _Events;
};

END_XE_NAMESPACE

#endif // ANIMATIONSTATE_H__C48F9826_7C1E_44A2_B4A1_1F579B74E9A8
