/*!
 * \file	AnimationEvent.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/21
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATIONEVENT_H__10B96503_1325_403B_8970_7497B426C29D
#define ANIMATIONEVENT_H__10B96503_1325_403B_8970_7497B426C29D

#include "Utils/Event.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API AnimationEvent
{
public:
	AnimationEvent();

	~AnimationEvent();

public:
	XE::float32 GetKey() const;

	void SetKey( XE::float32 val );

	const XE::EventPtr & GetEvent() const;

	void SetEvent( const XE::EventPtr & val );

public:
	void Reset();

	void Processed();

	bool IsProcessed() const;

private:
	XE::float32 _Key = 0.0f;
	XE::EventPtr _Event;
	bool _Processed = false;
};
DECL_META_CLASS( XE_API, AnimationEvent );

END_XE_NAMESPACE

#endif // ANIMATIONEVENT_H__10B96503_1325_403B_8970_7497B426C29D
