/*!
 * \file	AnimationLayer.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/26
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATIONLAYER_H__D1AB3E0B_84D8_4D85_A51F_0C4AB1E28D86
#define ANIMATIONLAYER_H__D1AB3E0B_84D8_4D85_A51F_0C4AB1E28D86

#include "Math/Mat4.h"
#include "Utils/Layer.h"
#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API AnimationLayer : XE::Object
{
	OBJECT( AnimationLayer, Object )

	friend class AnimationState;
	friend class AnimationController;

public:
	AnimationLayer();

	~AnimationLayer() override;

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

	XE::AnimationBlendMode GetBlendMode() const;

	void SetBlendMode( XE::AnimationBlendMode val );

	XE::AnimationStateHandle GetRootState() const;

	void SetRootState( XE::AnimationStateHandle val );

	XE::AnimationControllerPtr GetAnimationController() const;

	void SetAnimationController( XE::AnimationControllerPtr val );

	const XE::Array< XE::AnimationStatePtr > & GetAnimationStates() const;

	void SetAnimationStates( const XE::Array< XE::AnimationStatePtr > & val );

private:
	void * GetLocalTransform() const;

private:
	XE::String _Name;
	XE::float32 _Weight;
	XE::Layer _SkeletonMask;
	XE::AnimationBlendMode _BlendMode;
	XE::AnimationStateHandle _RootState;
	XE::Array< XE::AnimationStatePtr > _States;
	XE::AnimationControllerWPtr _AnimationController;

	void * _LocalTransform;
	XE::AnimationStateHandle _CurrentState;
};

END_XE_NAMESPACE

#endif // ANIMATIONLAYER_H__D1AB3E0B_84D8_4D85_A51F_0C4AB1E28D86
