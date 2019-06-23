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
	XE::real GetTimeScale() const override;

	void SetTimeScale( XE::real val ) override;

public:
	XE::real GetTime() const override;

	XE::real GetDeltaTime() const override;

	XE::real GetFixedDeltaTime() const override;

	XE::real GetUnscaleDeltaTime() const override;

	XE::real GetUnscaleFixedDeltaTime() const override;

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // __TIMERSERVICE_H__FF5BCF4F_FC59_4972_B484_868299AAFEC5
