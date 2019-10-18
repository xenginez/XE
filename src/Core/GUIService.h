/*!
 * \file	GUIService.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/24
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GUISERVICE_H__5DB19A5B_378C_464E_B5E1_8CDCBCAF68F0
#define GUISERVICE_H__5DB19A5B_378C_464E_B5E1_8CDCBCAF68F0

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API GUIService : public XE::IGUIService
{
	OBJECT( GUIService, IGUIService )

private:
	struct Private;

public:
	GUIService();

	~GUIService() override;

public:
	void Prepare()override;

	bool Startup() override;

	void Update() override;

	void Clearup() override;

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // GUISERVICE_H__5DB19A5B_378C_464E_B5E1_8CDCBCAF68F0
