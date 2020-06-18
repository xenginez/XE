#include "Event.h"

#include "Object.h"



IMPLEMENT_META( XE::EventHandle );

BEG_META( XE::Event )
type->Property( "accept", &Event::accept, IMetaProperty::NoClone | IMetaProperty::NoDesign | IMetaProperty::NoSerialize );
type->Property( "handle", &Event::handle, IMetaProperty::NoDesign | IMetaProperty::NoSerialize );
type->Property( "parameter", &Event::parameter, IMetaProperty::NoDesign | IMetaProperty::NoSerialize );
END_META()

XE::Event::Event()
	:accept( false )
{

}

XE::Event::Event( XE::EventHandle id, XE::ObjectPtr sender, XE::ObjectPtr recver, const XE::Variant & parameter /*= Variant() */ )
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

XE::Event & XE::Event::operator=( const Event & val )
{
	accept = val.accept;
	handle = val.handle;
	sender = val.sender;
	recver = val.recver;
	parameter = val.parameter;

	return *this;
}
