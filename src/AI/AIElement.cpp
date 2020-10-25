#include "AIElement.h"

#include "Interface/IFramework.h"
#include "Interface/IAssetsService.h"

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

BEG_META( XE::SubElement )
type->Property( "SubAI", &SubElement::_SubAI );
type->Property( "ConnectKeys", &SubElement::_ConnectKeys );
END_META()

XE::SubElement::SubElement()
{

}

XE::SubElement::~SubElement()
{

}

void XE::SubElement::OnStartup()
{
	for( const auto & keys : _ConnectKeys )
	{
		_SubAI->SetKey( keys.second, GetBluePrint()->GetKey( keys.first ) );
	}

	_SubAI->Startup();
}

void XE::SubElement::OnUpdate( XE::float32 dt )
{
	for( const auto & key : _ConnectKeys )
	{
		_SubAI->SetKey( key.second, GetBluePrint()->GetKey( key.first ) );
	}

	_SubAI->Update( dt );

	for( const auto & key : _ConnectKeys )
	{
		GetBluePrint()->SetKey( key.first, _SubAI->GetKey( key.second ) );
	}
}

void XE::SubElement::OnClearup()
{
	_SubAI->Clearup();
}

const XE::AIModulePtr & XE::SubElement::GetSubAIModule() const
{
	return _SubAI;
}

void XE::SubElement::SetSubAIModule( const XE::AIModulePtr & val )
{
	_SubAI = val;
}

const XE::Map<XE::BlackboardKey, XE::BlackboardKey> & XE::SubElement::GetConnectKeys() const
{
	return _ConnectKeys;
}

void XE::SubElement::SetConnectKeys( const XE::Map<XE::BlackboardKey, XE::BlackboardKey> & val )
{
	_ConnectKeys = val;
}
