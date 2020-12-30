/*!
 * \file	ClipState.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/28
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef CLIPSTATE_H__CEFADAC7_C235_4A92_9205_1662769EC882
#define CLIPSTATE_H__CEFADAC7_C235_4A92_9205_1662769EC882

#include "State.h"
#include "Sampler.h"
#include "SkeletonAnimation.h"

BEG_ANIMATION_NAMESPACE

class ANIMATION_API ClipState : public Animation::State
{
	OBJECT( ClipState, State )

public:
	ClipState();

	~ClipState() override;

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

	const XE::AssetPtr< Animation::SkeletonAnimation > & GetSkeletonAnimation() const;

	void SetSkeletonAnimation( const XE::AssetPtr< Animation::SkeletonAnimation > & val );

private:
	bool _Loop;
	XE::float32 _Speed;
	XE::float32 _EndTime;
	XE::float32 _StartTime;
	Sampler _Sampler;
	XE::AssetPtr< Animation::SkeletonAnimation > _SkeletonAnimation;

	XE::float32 _CurrentTime;
};

END_ANIMATION_NAMESPACE

#endif // CLIPSTATE_H__CEFADAC7_C235_4A92_9205_1662769EC882
