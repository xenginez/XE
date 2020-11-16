/*!
 * \file	NavigationService.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/24
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef NAVIGATIONSERVICE_H__017851C4_27D6_424E_9E6A_F2E950E8D568
#define NAVIGATIONSERVICE_H__017851C4_27D6_424E_9E6A_F2E950E8D568

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API NavigationService : public XE::INavigationService
{
	OBJECT( NavigationService, INavigationService )

private:
	struct Private;

public:
	NavigationService();

	~NavigationService() override;

public:
	void Prepare()override;

	bool Startup() override;

	void Update() override;

	void Clearup() override;

public:
	XE::Array< XE::Vec3f > FindRoute( const XE::OBB & geometry, const XE::Vec3f & start, const XE::Vec3f & end ) override;

	XE::Array< XE::Vec3f > FindRoute( const XE::AABB & geometry, const XE::Vec3f & start, const XE::Vec3f & end ) override;

	XE::Array< XE::Vec3f > FindRoute( const XE::Capsule & geometry, const XE::Vec3f & start, const XE::Vec3f & end ) override;

public:
	XE::NavMeshHandle AddNavMeshTile( const XE::FileSystem::Path & val ) override;

	void RemvoeNavMesh( XE::NavMeshHandle val ) override;

public:
	XE::NavObstacleHandle AddObstacle( const XE::OBB & geometry ) override;

	XE::NavObstacleHandle AddObstacle( const XE::AABB & geometry ) override;

	void RemoveObstacle( XE::NavObstacleHandle handle ) override;

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // NAVIGATIONSERVICE_H__017851C4_27D6_424E_9E6A_F2E950E8D568
