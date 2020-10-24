/*!
 * \file	BlendingState.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/19
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef BLENDINGSTATE_H__DF2F9BCE_F9FA_425C_88E2_4F68301C9192
#define BLENDINGSTATE_H__DF2F9BCE_F9FA_425C_88E2_4F68301C9192

#include "AnimationState.h"
#include "BlendingLayer.h"

BEG_XE_NAMESPACE

class XE_API BlendingState : public XE::AnimationState
{
	OBJECT( BlendingState, AnimationState )

private:
	struct Private;

public:
	BlendingState();

	~BlendingState() override;

public:
	bool GetLoop() const;

	void SetLoop( bool val );

	XE::float32 GetTime() const;

	void SetTime( XE::float32 val );

	XE::float32 GetSpeed() const;

	void SetSpeed( XE::float32 val );

	XE::float32 GetThreshold() const;

	void SetThreshold( XE::float32 val );

	const XE::Array< XE::BlendingLayerPtr > & GetLayers() const;

	void SetLayers( const XE::Array< XE::BlendingLayerPtr > & val );

public:
	void OnStartup() override;

	void OnUpdate( XE::float32 dt ) override;

	void OnClearup() override;

	void AssetLoad() override;

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // BLENDINGSTATE_H__DF2F9BCE_F9FA_425C_88E2_4F68301C9192
