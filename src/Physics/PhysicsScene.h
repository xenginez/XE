/*!
 * \file	PhysicsScene.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/11
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef PHYSICSSCENE_H__FB446DFF_5426_40D5_B375_25BB7F184281
#define PHYSICSSCENE_H__FB446DFF_5426_40D5_B375_25BB7F184281

#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API PhysicsScene : public XE::Object
{
	OBJECT( PhysicsScene, Object )

public:
	PhysicsScene();

	~PhysicsScene();

public:
	bool Startup();

	void Clearup();

	XE::PhysicsSceneHandle GetHandle() const;

private:
	XE::PhysicsSceneHandle _Handle;
};

END_XE_NAMESPACE

#endif // PHYSICSSCENE_H__FB446DFF_5426_40D5_B375_25BB7F184281
