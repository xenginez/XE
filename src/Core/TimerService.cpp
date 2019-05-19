#include "TimerService.h"

USING_XE

BEG_META( TimerService )
END_META()

struct TimerService::Private
{
	bool _IsPause;
	XE::uint64 _FrameCount;
	float _TimeScale;
	float _DetlaTime;
	float _FixedDetlaTime;
	std::chrono::steady_clock::time_point _StartTime;
	std::chrono::steady_clock::time_point _FrameTime;
};

XE::TimerService::TimerService()
	:_p( new Private )
{

}

XE::TimerService::~TimerService()
{
	delete _p;
}

bool XE::TimerService::Startup()
{
	_p->_IsPause = false;
	_p->_FrameCount = 0;
	_p->_TimeScale = 1.0f;
	_p->_DetlaTime = 0.0f;
	_p->_FixedDetlaTime = 0.0f;
	_p->_StartTime = std::chrono::steady_clock::now();
	_p->_FrameTime = _p->_StartTime;

	return true;
}

void XE::TimerService::Update()
{
	_p->_FrameCount++;

	auto now_time = std::chrono::steady_clock::now();

	_p->_DetlaTime = ( std::chrono::duration_cast<std::chrono::milliseconds>( now_time - _p->_FrameTime ).count() ) / 1000.0f;

	_p->_FrameTime = now_time;
}

void XE::TimerService::Clearup()
{
	_p->_TimeScale = 1.0f;
	_p->_DetlaTime = 0.0f;
	_p->_FixedDetlaTime = 0.0f;
	_p->_StartTime = std::chrono::steady_clock::now();
	_p->_FrameTime = _p->_StartTime;
}

void XE::TimerService::Pause()
{
	_p->_IsPause = true;
}

void XE::TimerService::Continue()
{
	_p->_IsPause = false;
}

bool XE::TimerService::IsPause() const
{
	return _p->_IsPause;
}

XE::uint64 XE::TimerService::GetFrameCount() const
{
	return _p->_FrameCount;
}

float XE::TimerService::GetTimeScale() const
{
	return _p->_TimeScale;
}

void XE::TimerService::SetTimeScale( float val )
{
	_p->_TimeScale = val;
}

float XE::TimerService::GetTime() const
{
	return ( std::chrono::duration_cast<std::chrono::milliseconds>( _p->_FrameTime - _p->_StartTime ).count() ) / 1000.0f;
}

float XE::TimerService::GetDeltaTime() const
{
	return _p->_DetlaTime * _p->_TimeScale;
}

float XE::TimerService::GetFixedDeltaTime() const
{
	return _p->_FixedDetlaTime * _p->_TimeScale;
}

float XE::TimerService::GetUnscaleDeltaTime() const
{
	return _p->_DetlaTime;
}

float XE::TimerService::GetUnscaleFixedDeltaTime() const
{
	return _p->_FixedDetlaTime;
}
