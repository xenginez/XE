#include "KeyboardInputControl.h"

#include "KeyCode.h"

USING_XE

BEG_META( KeyboardInputControl )
END_META()

XE::KeyboardInputControl::KeyboardInputControl()
{

}

XE::KeyboardInputControl::~KeyboardInputControl()
{

}

bool XE::KeyboardInputControl::Startup()
{
	_UpStub = _InputService->GetFramework()->GetEventService()->RegisterListener( EVENT_KEY_UP, [&]( XE::EventPtr event ) { _UpEvents.push( event ); } );
	_DownStub = _InputService->GetFramework()->GetEventService()->RegisterListener( EVENT_KEY_DOWN, [&]( XE::EventPtr event ) { _DownEvents.push( event ); } );

	return _UpStub != 0 && _DownStub != 0;
}

void XE::KeyboardInputControl::Update()
{
	XE::EventPtr event;

	while( _DownEvents.try_pop( event ) )
	{
		XE::uint32 code = event->parameter.Value<XE::uint32>();

		SetValue( EnumID<KeyCode>::Get()->FindName( ( XE::int64 ) TranslateKey[code] ), 1 );
	}
	while( _UpEvents.try_pop( event ) )
	{
		XE::uint32 code = event->parameter.Value<XE::uint32>();

		SetValue( EnumID<KeyCode>::Get()->FindName( ( XE::int64 )TranslateKey[code] ), 0 );
	}
}

void XE::KeyboardInputControl::Clearup()
{
	_InputService->GetFramework()->GetEventService()->UnregisterListener( EVENT_KEY_UP, _UpStub );
	_InputService->GetFramework()->GetEventService()->UnregisterListener( EVENT_KEY_DOWN, _DownStub );

	_UpStub = 0;
	_DownStub = 0;
}
