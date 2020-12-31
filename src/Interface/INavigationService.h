/*!
 * \file   INavigationService.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __INAVIGATIONSERVICE_H__D91CFCA9_BDF3_4CDF_B51C_77FAC3CEDAD3
#define __INAVIGATIONSERVICE_H__D91CFCA9_BDF3_4CDF_B51C_77FAC3CEDAD3

#include "Math/OBB.h"
#include "Math/AABB.h"
#include "Math/Capsule.h"

#include "IService.h"

BEG_XE_NAMESPACE

class XE_API INavigationService : public IService
{
	OBJECT( INavigationService, IService )

public:
	INavigationService();

	~INavigationService() override;

public:
	virtual XE::Array< XE::Vec3f > FindRoute( const XE::OBB & geometry, const XE::Vec3f & start, const XE::Vec3f & end ) = 0;

	virtual XE::Array< XE::Vec3f > FindRoute( const XE::AABB & geometry, const XE::Vec3f & start, const XE::Vec3f & end ) = 0;

	virtual XE::Array< XE::Vec3f > FindRoute( const XE::Capsule & geometry, const XE::Vec3f & start, const XE::Vec3f & end ) = 0;

public:
	virtual XE::NavMeshHandle AddNavMeshTile( const std::filesystem::path & val ) = 0;

	virtual void RemvoeNavMesh( XE::NavMeshHandle val ) = 0;

public:
	virtual XE::NavObstacleHandle AddObstacle( const XE::OBB & geometry ) = 0;

	virtual XE::NavObstacleHandle AddObstacle( const XE::AABB & geometry ) = 0;

	virtual void RemoveObstacle( XE::NavObstacleHandle handle ) = 0;
};

END_XE_NAMESPACE

#endif // __INAVIGATIONSERVICE_H__D91CFCA9_BDF3_4CDF_B51C_77FAC3CEDAD3
