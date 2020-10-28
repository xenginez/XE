/*!
 * \file	AnimationClipState.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/28
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATIONCLIPSTATE_H__CEFADAC7_C235_4A92_9205_1662769EC882
#define ANIMATIONCLIPSTATE_H__CEFADAC7_C235_4A92_9205_1662769EC882

#include "Utils/Asset.h"

#include "AnimationState.h"
#include "AnimationSampler.h"
#include "SkeletonAnimation.h"

BEG_XE_NAMESPACE

class XE_API AnimationClipState : public XE::AnimationState
{
	OBJECT( AnimationClipState, AnimationState )

public:
	AnimationClipState();

	~AnimationClipState() override;

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

	XE::float32 GetEndTime() const;

	void SetEndTime( XE::float32 val );

	XE::float32 GetStartTime() const;

	void SetStartTime( XE::float32 val );

	const XE::AssetPtr< XE::SkeletonAnimation > & GetSkeletonAnimation() const;

	void SetSkeletonAnimation( const XE::AssetPtr< XE::SkeletonAnimation > & val );

private:
	bool _Loop;
	XE::float32 _Speed;
	XE::float32 _EndTime;
	XE::float32 _StartTime;
	AnimationSampler _Sampler;
	XE::AssetPtr< XE::SkeletonAnimation > _SkeletonAnimation;

	XE::float32 _CurrentTime;
};

END_XE_NAMESPACE

#endif // ANIMATIONCLIPSTATE_H__CEFADAC7_C235_4A92_9205_1662769EC882
