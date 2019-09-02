#include "Object.h"

USING_XE

BEG_META( Object )
type->Property( "UUID", &Object::_UUID, IMetaProperty::NoDesign | IMetaProperty::NoRuntime );
END_META()

XE::Object::Object()
{

}

XE::Object::~Object()
{

}

const XE::String & XE::Object::GetUUID() const
{
	return _UUID;
}

void XE::Object::OnEvent( EventPtr & val )
{

}
