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

class XE_API ITimerService : public IService
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
	virtual XE::float32 GetTimeScale() const = 0;

	virtual void SetTimeScale( XE::float32 val ) = 0;

	virtual XE::float32 GetMinDeltaTime() const = 0;

	virtual void SetMinDeltaTime( XE::float32 val ) = 0;

	virtual XE::float32 GetMaxDeltaTime() const = 0;

	virtual void SetMaxDeltaTime( XE::float32 val ) = 0;

public:
	virtual XE::float32 GetTime() const = 0;

	virtual XE::float32 GetDeltaTime() const = 0;

	virtual XE::float32 GetFixedDeltaTime() const = 0;

	virtual XE::float32 GetUnscaleDeltaTime() const = 0;

	virtual XE::float32 GetUnscaleFixedDeltaTime() const = 0;

};

END_XE_NAMESPACE

#endif // __ITIMERSERVICE_H__3C3C2A0C_0074_4AD2_A126_56D63B98A5AD
