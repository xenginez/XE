/*!
 * \file	GameZone.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/13
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GAMEZONE_H__FAA0D8C3_281D_4184_B15B_EC2F3D9B63C8
#define GAMEZONE_H__FAA0D8C3_281D_4184_B15B_EC2F3D9B63C8

#include "GameObject.h"

BEG_XE_NAMESPACE

class XE_API GameZone final : public XE::GameEntity
{
	OBJECT( GameZone, GameEntity )

public:
	GameZone();

	~GameZone();

protected:
	void Startup() override;

	void Update( XE::float32 dt ) override;

	void Clearup() override;

protected:
	void OnEnable() override;

	void OnDisable() override;

};

END_XE_NAMESPACE

#endif // GAMEZONE_H__FAA0D8C3_281D_4184_B15B_EC2F3D9B63C8
