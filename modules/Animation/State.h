/*!
 * \file	State.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/19
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef STATE_H__C48F9826_7C1E_44A2_B4A1_1F579B74E9A8
#define STATE_H__C48F9826_7C1E_44A2_B4A1_1F579B74E9A8

#include "Condition.h"

BEG_ANIMATION_NAMESPACE

class ANIMATION_API State : public XE::Object
{
	OBJECT( State, Object )

	friend class Layer;

public:
	State();

	~State() override;

public:
	Animation::StateHandle GetHandle() const;

public:
	const XE::String & GetName() const;

	void SetName( const XE::String & val );

	Animation::StateStatus GetStatus() const;

	void SetStatus( Animation::StateStatus val );

	Animation::LayerPtr GetAnimationLayer() const;

	void SetAnimationLayer( Animation::LayerPtr val );

	const XE::Array< Animation::ConditionPtr > & GetAnimationConditions() const;

	void SetAnimationConditions( const XE::Array< Animation::ConditionPtr > & val );

public:
	virtual void Startup();

	virtual void Enter();

	virtual void Update( XE::float32 dt );

	virtual void Quit();

	virtual void Clearup();

protected:
	virtual void OnStartup();

	virtual void OnEnter();

	virtual void OnUpdate( XE::float32 dt );

	virtual void OnQuit();

	virtual void OnClearup();

protected:
	void * GetLocalTransform() const;

private:
	XE::String _Name;
	Animation::StateHandle _Handle;
	XE::Array< Animation::ConditionPtr > _AnimationConditions;

	Animation::StateStatus _Status;
	Animation::LayerWPtr _AnimationLayer;
};

END_ANIMATION_NAMESPACE

#endif // STATE_H__C48F9826_7C1E_44A2_B4A1_1F579B74E9A8
