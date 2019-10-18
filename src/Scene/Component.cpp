#include "Component.h"

#include "GameObject.h"

USING_XE

BEG_META( Component )
type->Property( "Name", &Component::_Name );
type->Property( "Handle", &Component::_Handle, IMetaProperty::NoDesign | IMetaProperty::NoClone );
type->Property( "Enabled", &Component::_Enabled );
END_META()

XE::Component::Component()
	:_Update( false ), _Enabled( true ), _Destroy( false ), _Name( GetMetaClass()->GetName() )
{

}

XE::Component::~Component()
{

}

const XE::String& XE::Component::GetName() const
{
	return _Name;
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

bool XE::Component::GetDestroy() const
{
	return _Destroy;
}

void XE::Component::SetDestroy( bool val )
{
	_Destroy = val;
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
