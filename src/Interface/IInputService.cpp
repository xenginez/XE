#include "IInputService.h"



BEG_META( XE::IInputControl )
END_META()

XE::IInputControl::IInputControl()
{

}

XE::IInputControl::~IInputControl()
{

}

void XE::IInputControl::SetValue( const String& code, const Variant& val )
{
	_InputService->SetValue( code, val );
}

BEG_META( XE::IInputService )
END_META()

XE::IInputService::IInputService()
{

}

XE::IInputService::~IInputService()
{

}
