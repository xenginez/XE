#include "AnimationTrigger.h"

USING_XE

BEG_META( AnimationTrigger )
type->Property( "Time", &AnimationTrigger::_Time );
type->Property( "EventHandle", &AnimationTrigger::_Handle );
type->Property( "EventParameter", &AnimationTrigger::_Parameter );
END_META()

AnimationTrigger::AnimationTrigger()
	:_Time( 0.0f ), _Sended( false )
{

}

AnimationTrigger::~AnimationTrigger()
{

}

XE::float32 AnimationTrigger::GetTime() const
{
	return _Time;
}

XE::EventHandle AnimationTrigger::GetEventHandle() const
{
	return _Handle;
}

const XE::Variant & AnimationTrigger::GetEventParameter() const
{
	return _Parameter;
}
