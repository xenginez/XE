#include "IEventService.h"

#include "Object.h"

USING_XE

BEGIN_META( Event )
type->Property( "id", &Event::id );
type->Property( "ignore", &Event::ignore );
type->Property( "parameter", &Event::parameter );
END_META()

XE::Event::Event()
	:id( 0 ), ignore( false )
{

}

XE::Event::Event( uint64 id, const Variant& parameter /*= Variant() */ )
	: ignore( false ), id( id ), parameter( parameter )
{

}

BEGIN_META( IEventService )
END_META()

XE::IEventService::IEventService()
{

}

XE::IEventService::~IEventService()
{

}
