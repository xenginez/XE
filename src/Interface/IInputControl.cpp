#include "IInputControl.h"

#include "IInputService.h"

BEG_META( XE::IInputControl )
END_META()

XE::IInputControl::IInputControl()
{

}

XE::IInputControl::~IInputControl()
{

}

void XE::IInputControl::SetValue( const String & code, XE::Variant val )
{
	_InputService->SetValue( code, val );
}

