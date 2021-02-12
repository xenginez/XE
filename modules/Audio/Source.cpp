#include "Source.h"

BEG_META( Audio::Source )
type->Property( "AudioClip", &Audio::Source::_AudioClip );
type->Property( "Loop", &Audio::Source::_Loop );
type->Property( "Gain", &Audio::Source::_Gain );
type->Property( "Pitch", &Audio::Source::_Pitch );
type->Property( "Position", &Audio::Source::_Position );
type->Property( "Velocity", &Audio::Source::_Velocity );
type->Property( "Direction", &Audio::Source::_Direction );
type->Property( "MinDistance", &Audio::Source::_MinDistance );
type->Property( "MaxDistance", &Audio::Source::_MaxDistance );
END_META()

void Audio::Source::Startup()
{
	if( _PlayOnStart )
	{
		Play();
	}
}

void Audio::Source::Update( Audio::float32 dt )
{

}

void Audio::Source::Clearup()
{

}

bool Audio::Source::GetLoop() const
{
	return _Loop;
}

void Audio::Source::SetLoop( bool val )
{
	_Loop = val;
}

bool Audio::Source::GetPlayOnStart() const
{
	return _PlayOnStart;
}

void Audio::Source::SetPlayOnStart( bool val )
{
	_PlayOnStart = val;
}

XE::float32 Audio::Source::GetGain() const
{
	return _Gain;
}

void Audio::Source::SetGain( XE::float32 val )
{
	_Gain = val;
}

XE::float32 Audio::Source::GetPitch() const
{
	return _Pitch;
}

void Audio::Source::SetPitch( XE::float32 val )
{
	_Pitch = val;
}

const XE::Vec3f & Audio::Source::GetPosition() const
{
	return _Position;
}

void Audio::Source::SetPosition( const XE::Vec3f & val )
{
	_Position = val;
}

const XE::Vec3f & Audio::Source::GetVelocity() const
{
	return _Velocity;
}

void Audio::Source::SetVelocity( const XE::Vec3f & val )
{
	_Velocity = val;
}

const XE::Vec3f & Audio::Source::GetDirection() const
{
	return _Direction;
}

void Audio::Source::SetDirection( const XE::Vec3f & val )
{
	_Direction = val;
}

XE::float32 Audio::Source::GetMinDistacne() const
{
	return _MinDistance;
}

void Audio::Source::SetMinDistance( XE::float32 val )
{
	_MinDistance = val;
}

XE::float32 Audio::Source::GetMaxDistance() const
{
	return _MaxDistance;
}

void Audio::Source::SetMaxDistance( XE::float32 val )
{
	_MaxDistance = val;
}

const XE::AudioClipPtr & Audio::Source::GetAudioClip() const
{
	return _AudioClip;
}

void Audio::Source::SetAudioClip( const XE::AudioClipPtr & val )
{
	_AudioClip = val;
}
