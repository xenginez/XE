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

#include "AnimationCondition.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API AnimationState : public XE::Object
{
	OBJECT( AnimationState, Object )

	friend class AnimationLayer;

public:
	AnimationState();

	~AnimationState() override;

public:
	XE::AnimationStateHandle GetHandle() const;

public:
	const XE::String & GetName() const;

	void SetName( const XE::String & val );

	XE::AnimationStateStatus GetStatus() const;

	void SetStatus( XE::AnimationStateStatus val );

	XE::AnimationLayerPtr GetAnimationLayer() const;

	void SetAnimationLayer( XE::AnimationLayerPtr val );

	const XE::Array< XE::AnimationCondition > & GetAnimationConditions() const;

	void SetAnimationConditions( const XE::Array< XE::AnimationCondition > & val );

public:
	virtual void Startup();

	virtual void Enter();

	virtual void Update( XE::float32 dt );

	virtual void Quit();

	virtual void Clearup();

protected:
	virtual void OnStartup() = 0;

	virtual void OnEnter() = 0;

	virtual void OnUpdate( XE::float32 dt ) = 0;

	virtual void OnQuit() = 0;

	virtual void OnClearup() = 0;

private:
	XE::String _Name;
	XE::AnimationStateHandle _Handle;
	XE::Array< XE::AnimationCondition > _AnimationConditions;

	XE::AnimationStateStatus _Status;
	XE::AnimationLayerWPtr _AnimationLayer;
};

END_XE_NAMESPACE

#endif // ANIMATIONSTATE_H__C48F9826_7C1E_44A2_B4A1_1F579B74E9A8
