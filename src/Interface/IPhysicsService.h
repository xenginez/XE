/*!
 * \file   IPhysicsService.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __IPHYSICSSERVICE_H__54C6EC49_5E04_435C_AAA2_6F83F6277CC2
#define __IPHYSICSSERVICE_H__54C6EC49_5E04_435C_AAA2_6F83F6277CC2

#include "IService.h"

BEG_XE_NAMESPACE

DECL_PTR( PhysicsScene );
using PhysicsSceneHandle = XE::Handle<PhysicsScene>;

class XE_API IPhysicsService : public IService
{
	OBJECT( IPhysicsService, IService )

public:
	IPhysicsService();

	~IPhysicsService() override;

public:
	virtual XE::PhysicsSceneHandle CreateScene();

	virtual void ReleaseScene( XE::PhysicsSceneHandle val );

};

END_XE_NAMESPACE

#endif // __IPHYSICSSERVICE_H__54C6EC49_5E04_435C_AAA2_6F83F6277CC2
