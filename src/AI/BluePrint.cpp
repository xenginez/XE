#include "BluePrint.h"

#include "AIElement.h"

BEG_META( XE::BluePrint )
type->Property( "Root", &XE::BluePrint::_Root, XE::IMetaProperty::NoDesign );
type->Property("Elements", &XE::BluePrint::_Elements, XE::IMetaProperty::NoDesign );
END_META()

XE::BluePrint::BluePrint()
{

}

XE::BluePrint::~BluePrint()
{

}

void XE::BluePrint::Startup()
{
	Super::Startup();

	for( auto elem : _Elements )
	{
		elem->SetBluePrint( XE_THIS( BluePrint ) );
	}
}

void XE::BluePrint::Update( XE::float32 dt )
{
	Super::Update( dt );

	if( _Root == AIElementHandle::Invalid )
	{
		return;
	}

	XE::AIElementHandle handle = _Root;
	while( handle )
	{
		XE::AIElementPtr elem = _Elements[handle.GetValue()];

		elem->Update( dt );

		const XE::Map< XE::AIElementHandle, XE::Pair< XE::String, XE::String > > & outs = elem->GetOutParameter();
		for( const auto & out : outs )
		{
			XE::AIElementPtr out_elem = _Elements[out.first.GetValue()];
			out_elem->SetProperty( out.second.first, elem->GetProperty( out.second.second ) );
		}

		handle = elem->GetNextElement();
	}
}

void XE::BluePrint::Clearup()
{
	for( auto elem : _Elements )
	{
		elem->Clearup();
	}

	Super::Clearup();
}

XE::AIElementHandle XE::BluePrint::GetRoot() const
{
	return _Root;
}

void XE::BluePrint::SetRoot( XE::AIElementHandle val )
{
	_Root = val;
}

XE::AIElementPtr XE::BluePrint::GetElement( XE::AIElementHandle val ) const
{
	return _Elements[val.GetValue()];
}

const XE::Array< XE::AIElementPtr > & XE::BluePrint::GetElements() const
{
	return _Elements;
}

void XE::BluePrint::SetElements( const XE::Array< XE::AIElementPtr > & val )
{
	_Elements = val;
}
