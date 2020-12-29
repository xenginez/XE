#include "AudioSoundSource.h"

BEG_META( AudioSoundSource )
type->Property( "Sound", &AudioSoundSource::_Sound );
type->Property( "Loop", &AudioSoundSource::_Loop );
type->Property( "Gain", &AudioSoundSource::_Gain );
type->Property( "Pitch", &AudioSoundSource::_Pitch );
type->Property( "Position", &AudioSoundSource::_Position );
type->Property( "Velocity", &AudioSoundSource::_Velocity );
type->Property( "Direction", &AudioSoundSource::_Direction );
type->Property( "MinDistance", &AudioSoundSource::_MinDistance );
type->Property( "MaxDistance", &AudioSoundSource::_MaxDistance );
END_META()

bool XE::AudioSoundSource::GetLoop() const
{
	return _Loop;
}

void XE::AudioSoundSource::SetLoop( bool val )
{
	_Loop = val;
}

XE::float32 XE::AudioSoundSource::GetGain() const
{
	return _Gain;
}

void XE::AudioSoundSource::SetGain( XE::float32 val )
{
	_Gain = val;
}

XE::float32 XE::AudioSoundSource::GetPitch() const
{
	return _Pitch;
}

void XE::AudioSoundSource::SetPitch( XE::float32 val )
{
	_Pitch = val;
}

const XE::Vec3f & XE::AudioSoundSource::GetPosition() const
{
	return _Position;
}

void XE::AudioSoundSource::SetPosition( const XE::Vec3f & val )
{
	_Position = val;
}

const XE::Vec3f & XE::AudioSoundSource::GetVelocity() const
{
	return _Velocity;
}

void XE::AudioSoundSource::SetVelocity( const XE::Vec3f & val )
{
	_Velocity = val;
}

const XE::Vec3f & XE::AudioSoundSource::GetDirection() const
{
	return _Direction;
}

void XE::AudioSoundSource::SetDirection( const XE::Vec3f & val )
{
	_Direction = val;
}

XE::float32 XE::AudioSoundSource::GetMinDistacne() const
{
	return _MinDistance;
}

void XE::AudioSoundSource::SetMinDistance( XE::float32 val )
{
	_MinDistance = val;
}

XE::float32 XE::AudioSoundSource::GetMaxDistance() const
{
	return _MaxDistance;
}

void XE::AudioSoundSource::SetMaxDistance( XE::float32 val )
{
	_MaxDistance = val;
}
