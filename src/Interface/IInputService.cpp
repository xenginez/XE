#include "IInputService.h"

BEG_META( XE::IInputService )
END_META()

XE::IInputService::IInputService()
{

}

XE::IInputService::~IInputService()
{

}

XE::float32 XE::IInputService::GetAxis( XE::KeyCode val ) const
{
	return GetAxis( ::XE_EnumID< XE::KeyCode >::Get()->FindName( val ) );
}

XE::float32 XE::IInputService::GetAxis( const XE::String & val ) const
{
	return GetValue( val ).ToFloat32();
}

bool XE::IInputService::GetButton( XE::KeyCode val ) const
{
	return GetButton( ::XE_EnumID< XE::KeyCode >::Get()->FindName( val ) );
}

bool XE::IInputService::GetButton( const XE::String & val ) const
{
	return GetValue( val ).ToInt32() > 0;
}

bool XE::IInputService::GetButtonPressed( XE::KeyCode val ) const
{
	return GetButtonPressed( ::XE_EnumID< XE::KeyCode >::Get()->FindName( val ) );
}

bool XE::IInputService::GetButtonPressed( const XE::String & val ) const
{
	return GetValue( val ).ToInt32() > 0;
}

bool XE::IInputService::GetButtonRelease( XE::KeyCode val ) const
{
	return GetButtonRelease( ::XE_EnumID< XE::KeyCode >::Get()->FindName( val ) );
}

bool XE::IInputService::GetButtonRelease( const XE::String & val ) const
{
	return GetValue( val ).ToInt32() == 0;
}

XE::float32 XE::IInputService::GetMouseWheel() const
{
	return GetValue( ::XE_EnumID< XE::KeyCode >::Get()->FindName( XE::KeyCode::MouseWheel ) ).ToFloat32();
}

XE::Vec2i XE::IInputService::GetMousePosition() const
{
	return GetValue( ::XE_EnumID< XE::KeyCode >::Get()->FindName( XE::KeyCode::MousePosition ) ).Value< XE::Vec2i >();
}
