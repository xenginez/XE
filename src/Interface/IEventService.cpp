#include "IEventService.h"

#include "Type.h"

USING_XE

BEG_META( Event )
type->Property( "id", &Event::id );
type->Property( "ignore", &Event::ignore );
type->Property( "parameter", &Event::parameter );
END_META()

XE::Event::Event()
	:id( 0 ), ignore( false )
{

}

XE::Event::Event( XE::uint64 id, const Variant& parameter /*= Variant() */ )
	: ignore( false ), id( id ), parameter( parameter )
{

}

BEG_META( IEventService )
END_META()

XE::IEventService::IEventService()
{

}

XE::IEventService::~IEventService()
{

}
