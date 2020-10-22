#include "AnimationEvent.h"

BEG_META( XE::AnimationEvent )
type->Property( "Key", &AnimationEvent::GetKey, &AnimationEvent::SetKey );
type->Property( "Event", &AnimationEvent::GetEvent, &AnimationEvent::SetEvent );
END_META()

XE::AnimationEvent::AnimationEvent()
{

}

XE::AnimationEvent::~AnimationEvent()
{

}

XE::float32 XE::AnimationEvent::GetKey() const
{
	return _Key;
}

void XE::AnimationEvent::SetKey( XE::float32 val )
{
	_Key = val;
}

const XE::EventPtr & XE::AnimationEvent::GetEvent() const
{
	return _Event;
}

void XE::AnimationEvent::SetEvent( const XE::EventPtr & val )
{
	_Event = val;
}

void XE::AnimationEvent::Reset()
{
	_Event->accept = false;
}

void XE::AnimationEvent::Processed()
{
	_Event->accept = true;
}

bool XE::AnimationEvent::IsProcessed() const
{
	return _Event->accept;
}
