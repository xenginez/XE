/*!
 * \file   IEventService.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __IEVENTSERVICE_H__9F87BB9F_F399_497E_AECE_12A1C3D02ACE
#define __IEVENTSERVICE_H__9F87BB9F_F399_497E_AECE_12A1C3D02ACE

#include "IService.h"

BEG_XE_NAMESPACE

class INTERFACE_API Event
{
	OBJECT( Event )

public:
	Event();

	Event( uint64 id, const Variant& parameter = Variant() );

public:
	uint64 id;
	bool ignore;
	Variant parameter;
};
DECL_META_CLASS( INTERFACE_API, Event );

class INTERFACE_API IEventService : public IService
{
	OBJECT( IEventService, IService )

public:
	typedef std::function<void( EventPtr )> ListenerType;

public:
	IEventService();

	~IEventService() override;

public:
	virtual void PostEvent( EventPtr val ) = 0;

	virtual void PostEvent( XE::uint64 frame, EventPtr val ) = 0;

	virtual void PostEvent( XE::float32 dt, EventPtr val ) = 0;

public:
	virtual XE::uint64 RegisterListener( uint32 event, ListenerType listener ) = 0;

	virtual void UnregisterListener( uint32 event, XE::uint64 index ) = 0;

};

END_XE_NAMESPACE

#endif // __IEVENTSERVICE_H__9F87BB9F_F399_497E_AECE_12A1C3D02ACE
