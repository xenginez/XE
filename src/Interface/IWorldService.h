/*!
 * \file   IWorldService.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __IWORLDSERVICE_H__1CE0128D_8AE2_434B_BF15_97B410BA145D
#define __IWORLDSERVICE_H__1CE0128D_8AE2_434B_BF15_97B410BA145D

#include <future>

#include "Math/Math.h"

#include "IService.h"

BEG_XE_NAMESPACE

DECL_PTR( World );

class XE_API IWorldService : public IService
{
	OBJECT( IWorldService, IService )

public:
	IWorldService();

	~IWorldService() override;

public:
	virtual XE::WorldPtr GetWorld() const = 0;

    virtual void ActiveWorld( const XE::WorldPtr & val ) = 0;
};

END_XE_NAMESPACE

#endif // __IWORLDSERVICE_H__1CE0128D_8AE2_434B_BF15_97B410BA145D
