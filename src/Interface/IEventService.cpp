#include "IEventService.h"

#include "Type.h"

USING_XE

BEG_META( Event )
type->Property( "accept", &Event::accept, IMetaProperty::NoClone | IMetaProperty::NoDesign | IMetaProperty::NoSerialize );
type->Property( "id", &Event::id );
type->Property( "parameter", &Event::parameter );
END_META()

XE::Event::Event()
	:accept( false ), id( 0 )
{

}

XE::Event::Event( XE::uint64 id, const Variant & parameter /*= Variant() */ )
	: accept( false ), id( id ), parameter( parameter )
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
