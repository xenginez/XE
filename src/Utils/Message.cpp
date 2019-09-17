#include "Message.h"

USING_XE

BEG_META( Message )
type->Property( "accept", &Message::accept, IMetaProperty::NoClone | IMetaProperty::NoDesign | IMetaProperty::NoSerialize );
type->Property( "id", &Message::id, IMetaProperty::NoDesign | IMetaProperty::NoSerialize );
type->Property( "sender", &Message::sender, IMetaProperty::NoDesign | IMetaProperty::NoSerialize );
type->Property( "parameter", &Message::parameter, IMetaProperty::NoDesign | IMetaProperty::NoSerialize );
END_META()

XE::Message::Message()
	:accept( false ), id( 0 )
{

}

XE::Message::Message( XE::uint64 id, ObjectPtr sender /*= nullptr*/, const Variant & parameter /*= Variant() */ )
	: accept( false ), id( id ), sender( sender ), parameter( parameter )

{

}

XE::Message::Message( const Message & val )
{
	accept = val.accept;
	id = val.id;
	sender = val.sender;
	parameter = val.parameter;
}
