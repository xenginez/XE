#include "AnimationTrigger.h"

USING_XE

BEG_META( AnimationTrigger )
type->Property( "Time", &AnimationTrigger::_Time );
type->Property( "Data", &AnimationTrigger::_Data );
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

const XE::Variant & AnimationTrigger::GetData() const
{
	return _Data;
}
