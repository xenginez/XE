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

#include "IService.h"

BEG_XE_NAMESPACE

class XE_API INavigationService : public IService
{
	OBJECT( INavigationService, IService )

public:
	INavigationService();

	~INavigationService() override;

public:

public:
	virtual XE::uint64 AddObstacle( const XE::OBB & geometry, const XE::Vec3 & position ) = 0;

	virtual XE::uint64 AddObstacle( const XE::AABB & geometry, const XE::Vec3 & position ) = 0;

	virtual XE::uint64 AddObstacle( const XE::Capsule & geometry, const XE::Vec3 & position ) = 0;

	virtual void UpdateObstacle( XE::uint64 handle, const XE::Vec3 & position ) = 0;

	virtual void RemoveObstacle( XE::uint64 handle ) = 0;
};

END_XE_NAMESPACE

#endif // __INAVIGATIONSERVICE_H__D91CFCA9_BDF3_4CDF_B51C_77FAC3CEDAD3
