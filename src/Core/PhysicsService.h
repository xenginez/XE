/*!
 * \file	PhysicsService.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/24
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef PHYSICSSERVICE_H__ED954415_C9C0_4412_8F6C_A8BF2C7836EA
#define PHYSICSSERVICE_H__ED954415_C9C0_4412_8F6C_A8BF2C7836EA

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API PhysicsService : public XE::IPhysicsService
{
	OBJECT( PhysicsService, IPhysicsService )

private:
	struct Private;

public:
	PhysicsService();

	~PhysicsService() override;

public:
	void Prepare()override;

	bool Startup() override;

	void Update() override;

	void Clearup() override;

public:
	XE::PhysicsSceneHandle CreateScene() override;

	void ReleaseScene( XE::PhysicsSceneHandle handle ) override;

	void * FindScene( XE::PhysicsSceneHandle handle ) override;

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // PHYSICSSERVICE_H__ED954415_C9C0_4412_8F6C_A8BF2C7836EA
