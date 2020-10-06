#include "Component.h"

#include "GameObject.h"

BEG_META( XE::Component )
type->Property( "Name", &Component::_Name );
type->Property( "Handle", &Component::_Handle, IMetaProperty::NoDesign | IMetaProperty::NoClone );
type->Property( "Enabled", &Component::_Enabled );
END_META()

XE::Component::Component()
	:_Update( false ), _Enabled( true ), _Name( GetMetaClass()->GetName() )
{

}

XE::Component::~Component()
{

}

XE::ComponentHandle XE::Component::GetHandle() const
{
	return _Handle;
}

XE::GameObjectPtr XE::Component::GetGameObject() const
{
	return _GameObject.lock();
}

bool XE::Component::GetUpdate() const
{
	return _Update;
}

void XE::Component::SetUpdate( bool val )
{
	_Update = val;
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
	if ( _Enabled == false || _Update == false )
	{
		return;
	}

	OnUpdate( dt );
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

void XE::Component::OnClearup()
{

}
