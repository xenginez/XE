/*!
 * \file   EventService.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/04
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __EVENTSERVICE_H__DBDF5D9A_0DF3_4FAA_8A61_54560543A0FA
#define __EVENTSERVICE_H__DBDF5D9A_0DF3_4FAA_8A61_54560543A0FA

#include "Type.h"

BEG_XE_NAMESPACE

class CORE_API EventService : public IEventService
{
	OBJECT( EventService, IEventService )

private:
	struct Private;

public:
	EventService();

	~EventService();

public:
	virtual bool Startup() override;

	virtual void Update() override;

	virtual void Clearup() override;

public:
	virtual void PostEvent( EventPtr val ) override;

	virtual void PostEvent( XE::uint64 frame, EventPtr val ) override;

	virtual void PostEvent( float dt, EventPtr val ) override;

public:
	virtual XE::uint64 RegisterListener( uint32 event, ListenerType listener ) override;

	virtual void UnregisterListener( uint32 event, XE::uint64 index ) override;

private:
	void ProcessTimeEvent();

	void ProcessFrameEvent();

private:
	Private * _p;
};

END_XE_NAMESAPCE

#endif // __EVENTSERVICE_H__DBDF5D9A_0DF3_4FAA_8A61_54560543A0FA
