/*!
 * \file   PhysicsComponent.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/14
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __PHYSICSCOMPONENT_H__06889AFB_D509_4C0A_AB26_53F551A07B0B
#define __PHYSICSCOMPONENT_H__06889AFB_D509_4C0A_AB26_53F551A07B0B

#include "Scene/SceneComponent.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API PhysicsComponent : public SceneComponent
{
	OBJECT( PhysicsComponent, SceneComponent )
public:
	PhysicsComponent();

	~PhysicsComponent() override;
};

END_XE_NAMESPACE

#endif // __PHYSICSCOMPONENT_H__06889AFB_D509_4C0A_AB26_53F551A07B0B
