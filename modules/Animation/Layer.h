/*!
 * \file	Layer.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/26
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef LAYER_H__D1AB3E0B_84D8_4D85_A51F_0C4AB1E28D86
#define LAYER_H__D1AB3E0B_84D8_4D85_A51F_0C4AB1E28D86

#include "Type.h"

BEG_ANIMATION_NAMESPACE

class ANIMATION_API Layer : XE::Object
{
	OBJECT( Layer, Object )

	friend class State;
	friend class Controller;

public:
	Layer();

	~Layer() override;

public:
	void Startup();

	void Update( XE::float32 dt );

	void Clearup();

	void AssetLoad() override;

public:
	XE::float32 GetWeight() const;

	void SetWeight( XE::float32 val );

	const XE::String & GetName() const;

	void SetName( const XE::String & val );

	const XE::Layer & GetSkeletonMask() const;

	void SetSkeletonMask( const XE::Layer & val );

	Animation::BlendMode GetBlendMode() const;

	void SetBlendMode( Animation::BlendMode val );

	Animation::StateHandle GetRootState() const;

	void SetRootState( Animation::StateHandle val );

	Animation::ControllerPtr GetAnimationController() const;

	void SetAnimationController( Animation::ControllerPtr val );

	const XE::Array< Animation::StatePtr > & GetAnimationStates() const;

	void SetAnimationStates( const XE::Array< Animation::StatePtr > & val );

private:
	void * GetLocalTransform() const;

private:
	XE::String _Name;
	XE::float32 _Weight;
	XE::Layer _SkeletonMask;
	Animation::BlendMode _BlendMode;
	Animation::StateHandle _RootState;
	XE::Array< Animation::StatePtr > _States;
	Animation::ControllerWPtr _AnimationController;

	void * _LocalTransform;
	Animation::StateHandle _CurrentState;
};

END_ANIMATION_NAMESPACE

#endif // LAYER_H__D1AB3E0B_84D8_4D85_A51F_0C4AB1E28D86
