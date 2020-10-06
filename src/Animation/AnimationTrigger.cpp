#include "AnimationTrigger.h"

BEG_META( XE::AnimationTrigger )
type->Property( "Time", &AnimationTrigger::_Time );
type->Property( "EventHandle", &AnimationTrigger::_Handle );
type->Property( "EventParameter", &AnimationTrigger::_Parameter );
END_META()

XE::AnimationTrigger::AnimationTrigger()
	:_Time( 0.0f ), _Sended( false )
{

}

XE::AnimationTrigger::~AnimationTrigger()
{

}

XE::float32 XE::AnimationTrigger::GetTime() const
{
	return _Time;
}

XE::EventHandle XE::AnimationTrigger::GetEventHandle() const
{
	return _Handle;
}

const XE::Variant & XE::AnimationTrigger::GetEventParameter() const
{
	return _Parameter;
}
