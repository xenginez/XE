#include "InputControl.h"

USING_XE

XE::InputControl::InputControl( IFrameworkPtr framework )
	:IPlugin( framework )
{

}

XE::InputControl::~InputControl()
{

}

String XE::InputControl::GetName() const
{
	return "InputControl";
}

void XE::InputControl::Startup()
{

}

void XE::InputControl::Clearup()
{

}

REGISTER_PLUGIN( InputControl );