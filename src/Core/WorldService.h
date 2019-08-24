/*!
 * \file	WorldService.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/24
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef WORLDSERVICE_H__A0A97835_27B7_486A_AE30_9848F23C0B8C
#define WORLDSERVICE_H__A0A97835_27B7_486A_AE30_9848F23C0B8C

#include "Type.h"

BEG_XE_NAMESPACE

class CORE_API WorldService : public XE::IWorldService
{
	OBJECT( WorldService, IWorldService )

public:
	WorldService();

	~WorldService() override;

public:
	void Prepare()override;

	bool Startup() override;

	void Update() override;

	void Clearup() override;

};

END_XE_NAMESPACE

#endif // WORLDSERVICE_H__A0A97835_27B7_486A_AE30_9848F23C0B8C
