/*!
 * \file	BlendState.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/28
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef BLENDSTATE_H__F3212467_4377_48FA_908A_AD7FA5CBEABA
#define BLENDSTATE_H__F3212467_4377_48FA_908A_AD7FA5CBEABA

#include "State.h"
#include "BlendLayer.h"

BEG_ANIMATION_NAMESPACE

class ANIMATION_API BlendState : public Animation::State
{
	OBJECT( BlendState, State )

public:
	BlendState();

	~BlendState() override;

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
	XE::Array< Animation::BlendLayer > _Layers;

	XE::float32 _CurrentTime;
	XE::float32 _MaxTime;
};

END_ANIMATION_NAMESPACE

#endif // BLENDSTATE_H__F3212467_4377_48FA_908A_AD7FA5CBEABA
