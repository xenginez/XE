/*!
 * \file	SamplingState.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/19
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef SAMPLINGSTATE_H__B98C338F_4CAF_409B_8A4A_453BF0F0AEDB
#define SAMPLINGSTATE_H__B98C338F_4CAF_409B_8A4A_453BF0F0AEDB

#include "Utils/Asset.h"

#include "AnimationState.h"
#include "SkeletonAnimation.h"

BEG_XE_NAMESPACE

class XE_API SamplingState : public XE::AnimationState
{
	OBJECT( SamplingState, AnimationState )

private:
	struct Private;

public:
	SamplingState();

	~SamplingState() override;

public:
	bool GetLoop() const;

	void SetLoop( bool val );

	XE::float32 GetTime() const;

	void SetTime( XE::float32 val );

	XE::float32 GetSpeed() const;

	void SetSpeed( XE::float32 val );

	const XE::AssetPtr< XE::SkeletonAnimation > & GetSkeletonAnimation() const;

	void SetSkeletonAnimation( const XE::AssetPtr< XE::SkeletonAnimation > & val );

	const XE::Array< XE::Pair<XE::float32, XE::EventPtr> > & GetAnimationEvents() const;

	void SetAnimationEvents( const XE::Array< XE::Pair<XE::float32, XE::EventPtr> > & val );

public:
	void OnStartup() override;

	void OnUpdate( XE::float32 dt ) override;

	void OnClearup() override;

	void AssetLoad() override;

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // SAMPLINGSTATE_H__B98C338F_4CAF_409B_8A4A_453BF0F0AEDB
