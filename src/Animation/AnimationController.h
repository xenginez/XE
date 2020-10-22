/*!
 * \file	AnimationController.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/22
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATIONCONTROLLER_H__791BB598_7A96_4DEC_B252_90E6EF8ACCAC
#define ANIMATIONCONTROLLER_H__791BB598_7A96_4DEC_B252_90E6EF8ACCAC

#include "Math/Mat4.h"
#include "Utils/Asset.h"
#include "AI/StateMachine.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API AnimationController : public XE::StateMachine
{
	OBJECT( AnimationController, StateMachine )

public:
	AnimationController();

	~AnimationController() override;

public:
	void Startup() override;

	void Clearup() override;

	void AssetLoad() override;

public:
	const XE::AssetPtr<XE::Skeleton> & GetSkeleton() const;

	void SetSkeleton( const XE::AssetPtr<XE::Skeleton> & val );

private:
	XE::AssetPtr<XE::Skeleton> _Skeleton;
};

END_XE_NAMESPACE

#endif // ANIMATIONCONTROLLER_H__791BB598_7A96_4DEC_B252_90E6EF8ACCAC
