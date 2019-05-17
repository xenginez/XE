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

class INTERFACE_API INavigationService : public IService
{
	OBJECT( INavigationService, IService )

public:
	INavigationService();

	~INavigationService() override;
};

END_XE_NAMESAPCE

#endif // __INAVIGATIONSERVICE_H__D91CFCA9_BDF3_4CDF_B51C_77FAC3CEDAD3
