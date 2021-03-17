#include "Component.h"

#include "GameObject.h"

BEG_META( XE::Component )
type->Property( "Name", &XE::Component::_Name );
type->Property( "Enabled", &XE::Component::_Enabled );
type->Property( "Handle", &XE::Component::_Handle, XE::IMetaProperty::NoDesign | XE::IMetaProperty::NoClone );
END_META()

XE::Component::Component()
	:_Enabled( true ), _Name( GetMetaClass()->GetName() )
{

}

XE::Component::~Component()
{

}

XE::ComponentHandle XE::Component::GetHandle() const
{
	return _Handle;
}

XE::WorldPtr XE::Component::GetWorld() const
{
	return _World.lock();
}

XE::GameObjectPtr XE::Component::GetGameObject() const
{
	return _GameObject.lock();
}

bool XE::Component::GetEnabled() const
{
	return _Enabled;
}

void XE::Component::SetEnabled( bool val )
{
	_Enabled = val;
}

const XE::String & XE::Component::GetName() const
{
	return _Name;
}

void XE::Component::SetName( const XE::String & val )
{
	_Name = val;
}

void XE::Component::Startup()
{
	OnStartup();
}

void XE::Component::Update( XE::float32 dt )
{
	if ( _Enabled == false )
	{
		return;
	}

	OnUpdate( dt );
}

void XE::Component::LateUpdate( XE::float32 dt )
{
	if( _Enabled == false )
	{
		return;
	}

	OnLateUpdate( dt );
}

void XE::Component::Clearup()
{
	OnClearup();
}

void XE::Component::OnStartup()
{

}

void XE::Component::OnUpdate( XE::float32 dt )
{

}

void XE::Component::OnLateUpdate( XE::float32 dt )
{

}

void XE::Component::OnClearup()
{

}
