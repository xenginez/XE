#include "AIElement.h"

#include "Blueprint.h"

BEG_META( XE::AIElement )
type->Property( "Name", &XE::AIElement::_Name );
type->Property( "Handle", &XE::AIElement::_Handle, XE::IMetaProperty::NoDesign );
type->Property( "NextHandle", &XE::AIElement::_NextHandle, XE::IMetaProperty::NoDesign );
type->Property( "In", &XE::AIElement::_In, XE::IMetaProperty::NoDesign );
END_META()

XE::AIElement::AIElement()
{

}

XE::AIElement::~AIElement()
{

}

XE::BlueprintPtr XE::AIElement::GetBlueprint() const
{
	return _Blueprint.lock();
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

const XE::Map< XE::String, XE::Pair< XE::AIElementHandle, XE::String > > & XE::AIElement::GetIn() const
{
	return _In;
}

void XE::AIElement::SetIn( const XE::Map< XE::String, XE::Pair< XE::AIElementHandle, XE::String > > & val )
{
	_In = val;
}

void XE::AIElement::SetBlueprint( BlueprintPtr val )
{
	_Blueprint = val;
}

void XE::AIElement::Execute()
{
	auto blueprint = GetBlueprint();

	for( const auto & i : _In )
	{
		if( auto element = blueprint->GetElement( i.second.first ) )
		{
			_OutParams[i.first] = element->_OutParams[i.second.second];
		}
	}

	OnExecute();
}

void XE::AIElement::OnExecute()
{

}
