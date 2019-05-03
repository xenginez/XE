#include "IInputService.h"

USING_XE

BEGIN_META( IInputControl )
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

BEGIN_META( IInputService )
END_META()

XE::IInputService::IInputService()
{

}

XE::IInputService::~IInputService()
{

}
