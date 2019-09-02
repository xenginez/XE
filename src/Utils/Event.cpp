#include "Event.h"

#include "Object.h"

USING_XE

BEG_META( Event )
type->Property( "accept", &Event::accept, IMetaProperty::NoClone | IMetaProperty::NoDesign | IMetaProperty::NoSerialize );
type->Property( "id", &Event::id, IMetaProperty::NoDesign | IMetaProperty::NoSerialize );
type->Property( "sender", &Event::sender, IMetaProperty::NoDesign | IMetaProperty::NoSerialize );
type->Property( "recver", &Event::recver, IMetaProperty::NoDesign | IMetaProperty::NoSerialize );
type->Property( "parameter", &Event::parameter, IMetaProperty::NoDesign | IMetaProperty::NoSerialize );
END_META()

XE::Event::Event()
	:accept( false ), id( 0 )
{

}

XE::Event::Event( XE::uint64 id, ObjectPtr sender /*= nullptr*/, ObjectPtr recver /*= nullptr*/, const Variant & parameter /*= Variant() */ )
	: accept( false ), id( id ), sender( sender ), recver( recver ), parameter( parameter )
	
{

}

XE::Event::Event( const Event & val )
{
	accept = val.accept;
	id = val.id;
	sender = val.sender;
	recver = val.recver;
	parameter = val.parameter;
}
