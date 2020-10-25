/*!
 * \file	IKAimState.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/19
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef IKAIMSTATE_H__5543F33F_6E67_468A_825C_7129609CE3D1
#define IKAIMSTATE_H__5543F33F_6E67_468A_825C_7129609CE3D1

#include "Utils/Asset.h"

#include "AnimationState.h"
#include "SkeletonAnimation.h"

BEG_XE_NAMESPACE

class XE_API IKAimState : public XE::AnimationState
{
	OBJECT( IKAimState, AnimationState )

private:
	struct Private;

public:
	IKAimState();

	~IKAimState() override;

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

#endif // IKAIMSTATE_H__5543F33F_6E67_468A_825C_7129609CE3D1
