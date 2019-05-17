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

	~TimerService() override;

public:
	bool Startup() override;

	void Update() override;

	void Clearup() override;

public:
	void Pause() override;

	void Continue() override;

	bool IsPause() const override;

public:
	XE::uint64 GetFrameCount() const override;

public:
	float GetTimeScale() const override;

	void SetTimeScale( float val ) override;

public:
	float GetTime() const override;

	float GetDeltaTime() const override;

	float GetFixedDeltaTime() const override;

	float GetUnscaleDeltaTime() const override;

	float GetUnscaleFixedDeltaTime() const override;

private:
	Private * _p;
};

END_XE_NAMESAPCE

#endif // __TIMERSERVICE_H__FF5BCF4F_FC59_4972_B484_868299AAFEC5
