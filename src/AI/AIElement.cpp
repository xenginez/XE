#include "AIElement.h"

#include "Blueprint.h"

BEG_META( XE::AIElement )
type->Property( "Name", &XE::AIElement::_Name );
type->Property( "Handle", &XE::AIElement::_Handle, XE::IMetaProperty::NoDesign );
type->Property( "NextHandle", &XE::AIElement::_NextHandle, XE::IMetaProperty::NoDesign );
END_META()

XE::AIElement::AIElement()
{
	_Name = GetMetaClass()->GetName();
}

XE::AIElement::~AIElement()
{

}

XE::BlueprintPtr XE::AIElement::GetBlueprint() const
{
	return _Blueprint.lock();
}

void XE::AIElement::SetBlueprint( BlueprintPtr val )
{
	_Blueprint = val;
}

const XE::String & XE::AIElement::GetName() const
{
	return _Name;
}

void XE::AIElement::SetName( const XE::String & val )
{
	_Name;
}

XE::AIElementHandle XE::AIElement::GetHandle() const
{
	return _Handle;
}

void XE::AIElement::SetHandle( XE::AIElementHandle val )
{
	_Handle = val;
}

XE::AIElementHandle XE::AIElement::GetNextHandle() const
{
	return _NextHandle;
}

void XE::AIElement::SetNextHandle( XE::AIElementHandle val )
{
	_NextHandle = val;
}

void XE::AIElement::Execute()
{
	OnExecute();
}

void XE::AIElement::OnExecute()
{

}
