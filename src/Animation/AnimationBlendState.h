/*!
 * \file	AnimationBlendState.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/28
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATIONBLENDSTATE_H__F3212467_4377_48FA_908A_AD7FA5CBEABA
#define ANIMATIONBLENDSTATE_H__F3212467_4377_48FA_908A_AD7FA5CBEABA

#include "AnimationState.h"
#include "AnimationBlendLayer.h"

BEG_XE_NAMESPACE

class XE_API AnimationBlendState : public XE::AnimationState
{
	OBJECT( AnimationBlendState, AnimationState )

public:
	AnimationBlendState();

	~AnimationBlendState() override;

protected:
	void OnStartup() override;

	void OnEnter() override;

	void OnUpdate( XE::float32 dt ) override;

	void OnClearup() override;

	void AssetLoad() override;

public:
	bool GetLoop() const;

	void SetLoop( bool val );

	XE::float32 GetSpeed() const;

	void SetSpeed( XE::float32 val );

	XE::float32 GetThreshold() const;

	void SetThreshold( XE::float32 val );

private:
	bool _Loop;
	XE::float32 _Speed;
	XE::float32 _Threshold;
	XE::Array< XE::AnimationBlendLayer > _Layers;

	XE::float32 _CurrentTime;
	XE::float32 _MaxTime;
};

END_XE_NAMESPACE

#endif // ANIMATIONBLENDSTATE_H__F3212467_4377_48FA_908A_AD7FA5CBEABA
