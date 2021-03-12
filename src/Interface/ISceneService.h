/*!
 * \file	ISceneService.h
 *
 * \author	ZhengYuanQing
 * \date	2021/03/12
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ISCENESERVICE_H__BD5B0256_96FC_4D6C_81C3_FF8A74873CD5
#define ISCENESERVICE_H__BD5B0256_96FC_4D6C_81C3_FF8A74873CD5

#include "Math/Math.h"

#include "IService.h"

BEG_XE_NAMESPACE

DECL_PTR( World );

class XE_API ISceneService : public IService
{
	OBJECT( ISceneService, IService )

public:
	ISceneService();

	~ISceneService() override;

public:
	virtual XE::WorldPtr GetWorld() const = 0;

	virtual void ActiveWorld( const XE::WorldPtr & val ) = 0;
};

END_XE_NAMESPACE

#endif // ISCENESERVICE_H__BD5B0256_96FC_4D6C_81C3_FF8A74873CD5
