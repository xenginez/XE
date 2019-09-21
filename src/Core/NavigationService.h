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

public:
	NavigationService();

	~NavigationService() override;

public:
	void Prepare()override;

	bool Startup() override;

	void Update() override;

	void Clearup() override;

};

END_XE_NAMESPACE

#endif // NAVIGATIONSERVICE_H__017851C4_27D6_424E_9E6A_F2E950E8D568
