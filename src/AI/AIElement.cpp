#include "AIElement.h"

#include "BluePrint.h"

BEG_META( XE::AIElement )
type->Property( "Name", &AIElement::_Name, XE::IMetaProperty::NoDesign );
type->Property( "Handle", &AIElement::_Handle, XE::IMetaProperty::NoDesign );
type->Property( "NextElement", &AIElement::_NextElement, XE::IMetaProperty::NoDesign );
type->Property( "OutParameter", &AIElement::_OutParameter, XE::IMetaProperty::NoDesign );
END_META()

XE::AIElement::AIElement()
{

}

XE::AIElement::~AIElement()
{

}

const XE::String & XE::AIElement::GetName() const
{
	return _Name;
}

void XE::AIElement::SetName( const XE::String & val )
{
	_Name = val;
}

XE::AIElementHandle XE::AIElement::GetHandle() const
{
	return _Handle;
}

void XE::AIElement::SetHandle( XE::AIElementHandle val )
{
	_Handle = val;
}

XE::AIElementHandle XE::AIElement::GetNextElement() const
{
	return _NextElement;
}

void XE::AIElement::SetNextElement( XE::AIElementHandle val )
{
	_NextElement = val;
}

const XE::Map< XE::AIElementHandle, XE::Pair< XE::String, XE::String > > & XE::AIElement::GetOutParameter() const
{
	return _OutParameter;
}

void XE::AIElement::SetOutParameter( const XE::Map< XE::AIElementHandle, XE::Pair< XE::String, XE::String > > & val )
{
	_OutParameter = val;
}

XE::BluePrintPtr XE::AIElement::GetBluePrint() const
{
	return _BluePrint.lock();
}

void XE::AIElement::SetBluePrint( XE::BluePrintPtr val )
{
	_BluePrint = val;
}

void XE::AIElement::Startup()
{
	OnStartup();
}

void XE::AIElement::Update( XE::float32 dt )
{
	OnUpdate( dt );
}

void XE::AIElement::Clearup()
{
	OnClearup();
}

void XE::AIElement::OnStartup()
{

}

void XE::AIElement::OnUpdate( XE::float32 dt )
{

}

void XE::AIElement::OnClearup()
{

}
