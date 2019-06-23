/*!
 * \file   ITimerService.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __ITIMERSERVICE_H__3C3C2A0C_0074_4AD2_A126_56D63B98A5AD
#define __ITIMERSERVICE_H__3C3C2A0C_0074_4AD2_A126_56D63B98A5AD

#include "IService.h"

BEG_XE_NAMESPACE

class INTERFACE_API ITimerService : public IService
{
	OBJECT( ITimerService, IService )

public:
	ITimerService();

	~ITimerService() override;

public:
	virtual void Pause() = 0;

	virtual void Continue() = 0;

	virtual bool IsPause() const = 0;

public:
	virtual XE::uint64 GetFrameCount() const = 0;

public:
	virtual XE::real GetTimeScale() const = 0;

	virtual void SetTimeScale( XE::real val ) = 0;

public:
	virtual XE::real GetTime() const = 0;

	virtual XE::real GetDeltaTime() const = 0;

	virtual XE::real GetFixedDeltaTime() const = 0;

	virtual XE::real GetUnscaleDeltaTime() const = 0;

	virtual XE::real GetUnscaleFixedDeltaTime() const = 0;

};

END_XE_NAMESPACE

#endif // __ITIMERSERVICE_H__3C3C2A0C_0074_4AD2_A126_56D63B98A5AD
