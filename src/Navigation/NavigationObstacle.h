/*!
 * \file	NavigationObstacle.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/30
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef NAVIGATIONOBSTACLE_H__CD527FA1_B3A9_45B0_98BE_05C1796CF15E
#define NAVIGATIONOBSTACLE_H__CD527FA1_B3A9_45B0_98BE_05C1796CF15E

#include "Math/OBB.h"
#include "Math/Vec3.h"
#include "Math/AABB.h"
#include "Math/Capsule.h"
#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API NavigationObstacle : public XE::Object
{
	OBJECT( NavigationObstacle, Object )

public:
	NavigationObstacle();

	~NavigationObstacle() override;

public:
	XE::NavigationObstacleHandle GetHandle() const;

public:
	const XE::Vec3 & GetPosition() const;

	void SetPosition( const XE::Vec3 & val );

	XE::NavigationObstacleType GetType() const;

public:
	virtual void Startup();

	virtual void Update();

	virtual void Clearup();

protected:
	void SetType( XE::NavigationObstacleType val );

	void SetHandle( XE::NavigationObstacleHandle val );

private:
	XE::Vec3 _Position;
	XE::NavigationObstacleType _Type;
	XE::NavigationObstacleHandle _Handle;
};

class XE_API NavigationOBBObstacle : public XE::NavigationObstacle
{
	OBJECT( NavigationOBBObstacle, NavigationObstacle )

public:
	NavigationOBBObstacle();

	~NavigationOBBObstacle() override;

public:
	const XE::OBB & GetOBB() const;

	void SetOBB( const XE::OBB & val );

public:
	void Startup() override;

private:
	XE::OBB _OBB;
};

class XE_API NavigationAABBObstacle : public XE::NavigationObstacle
{
	OBJECT( NavigationAABBObstacle, NavigationObstacle )

public:
	NavigationAABBObstacle();

	~NavigationAABBObstacle() override;

	const XE::AABB & GetAABB() const;

	void SetAABB( const XE::AABB & val );

public:
	void Startup() override;

private:
	XE::AABB _AABB;
};

class XE_API NavigationCapsuleObstacle : public XE::NavigationObstacle
{
	OBJECT( NavigationCapsuleObstacle, NavigationObstacle )

public:
	NavigationCapsuleObstacle();

	~NavigationCapsuleObstacle() override;

	const XE::Capsule & GetCapsule() const;

	void SetCapsule( const XE::Capsule & val );

public:
	void Startup() override;

private:
	XE::Capsule _Capsule;
};

END_XE_NAMESPACE

#endif // NAVIGATIONOBSTACLE_H__CD527FA1_B3A9_45B0_98BE_05C1796CF15E
