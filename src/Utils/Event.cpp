#include "Event.h"

#include "Object.h"

USING_XE

IMPLEMENT_META( EventHandle );

BEG_META( Event )
type->Property( "accept", &Event::accept, IMetaProperty::NoClone | IMetaProperty::NoDesign | IMetaProperty::NoSerialize );
type->Property( "handle", &Event::handle, IMetaProperty::NoDesign | IMetaProperty::NoSerialize );
type->Property( "parameter", &Event::parameter, IMetaProperty::NoDesign | IMetaProperty::NoSerialize );
END_META()

XE::Event::Event()
	:accept( false )
{

}

Event::Event( EventHandle id, ObjectPtr sender, ObjectPtr recver, const Variant & parameter /*= Variant() */ )
	: accept( false ), handle( id ), sender( sender ), recver( recver ), parameter( parameter )
	
{

}

XE::Event::Event( const Event & val )
{
	accept = val.accept;
	handle = val.handle;
	sender = val.sender;
	recver = val.recver;
	parameter = val.parameter;
}

XE::Event & Event::operator=( const Event & val )
{
	accept = val.accept;
	handle = val.handle;
	sender = val.sender;
	recver = val.recver;
	parameter = val.parameter;

	return *this;
}
