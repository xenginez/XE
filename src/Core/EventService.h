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

	~EventService() override;

public:
	void Prepare()override;

	bool Startup() override;

	void Update() override;

	void Clearup() override;

public:
	void PostEvent( EventPtr val ) override;

	void PostEvent( XE::uint64 frame, EventPtr val ) override;

	void PostEvent( XE::real dt, EventPtr val ) override;

public:
	XE::uint64 RegisterListener( XE::uint64 event, ListenerType listener ) override;

	void UnregisterListener( XE::uint64 event, XE::uint64 index ) override;

private:
	void ProcessTimeEvent();

	void ProcessFrameEvent();

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // __EVENTSERVICE_H__DBDF5D9A_0DF3_4FAA_8A61_54560543A0FA
