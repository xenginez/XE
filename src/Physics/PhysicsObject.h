/*!
 * \file	PhysicsObject.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/08
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef PHYSICSOBJECT_H__A816A00B_BB82_45C4_B002_56AD2042B2A5
#define PHYSICSOBJECT_H__A816A00B_BB82_45C4_B002_56AD2042B2A5

#include "Type.h"

BEG_XE_NAMESPACE

class PHYSICS_API PhysicsObject : public XE::Object
{
	OBJECT( PhysicsObject, Object )

public:
	PhysicsObject();

	~PhysicsObject() override;

public:
	IPhysicsContextRPtr GetPhysicsContext() const;

	void SetPhysicsContext( IPhysicsContextRPtr val );

private:
	IPhysicsContextRPtr _Context;
};

END_XE_NAMESPACE

#endif // PHYSICSOBJECT_H__A816A00B_BB82_45C4_B002_56AD2042B2A5
