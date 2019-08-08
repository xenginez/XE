#include "XScriptComponent.h"

USING_XE

BEG_META( XScriptComponent )
type->Property( "Script", &XScriptComponent::_Script );
END_META()

XE::XScriptComponent::XScriptComponent()
{

}

XE::XScriptComponent::~XScriptComponent()
{

}

void XE::XScriptComponent::OnStartup()
{
	if( _Class = SP_CAST<IMetaClass>( _Script.GetMeta() ) )
	{
		_OnStartup = _Class->FindMethod( "OnStartup" );
		_OnUpdate = _Class->FindMethod( "OnUpdate" );
		_OnClearup = _Class->FindMethod( "OnClearup" );
	}

	_OnStartup->Invoke( _Script );
}

void XE::XScriptComponent::OnUpdate( XE::real dt )
{
	_OnUpdate->Invoke( _Script );
}

void XE::XScriptComponent::OnClearup()
{
	_OnClearup->Invoke( _Script );
}
