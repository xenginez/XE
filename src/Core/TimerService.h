/*!
 * \file   TimerService.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/05
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TIMERSERVICE_H__FF5BCF4F_FC59_4972_B484_868299AAFEC5
#define __TIMERSERVICE_H__FF5BCF4F_FC59_4972_B484_868299AAFEC5

#include "Type.h"

BEG_XE_NAMESPACE

class CORE_API TimerService : public ITimerService
{
	OBJECT( TimerService, ITimerService )

private:
	struct Private;

public:
	TimerService();

	~TimerService();

public:
	virtual bool Startup() override;

	virtual void Update() override;

	virtual void Clearup() override;

public:
	virtual void Pause() override;

	virtual void Continue() override;

	virtual bool IsPause() const override;

public:
	virtual XE::uint64 GetFrameCount() const override;

public:
	virtual float GetTimeScale() const override;

	virtual void SetTimeScale( float val ) override;

public:
	virtual float GetTime() const override;

	virtual float GetDeltaTime() const override;

	virtual float GetFixedDeltaTime() const override;

	virtual float GetUnscaleDeltaTime() const override;

	virtual float GetUnscaleFixedDeltaTime() const override;

private:
	Private * _p;
};

END_XE_NAMESAPCE

#endif // __TIMERSERVICE_H__FF5BCF4F_FC59_4972_B484_868299AAFEC5
