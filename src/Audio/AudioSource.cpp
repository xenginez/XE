#include "AudioSource.h"

BEG_META( AudioSource )
type->Property( "AudioClip", &XE::AudioSource::_AudioClip );
type->Property( "Loop", &XE::AudioSource::_Loop );
type->Property( "Gain", &XE::AudioSource::_Gain );
type->Property( "Pitch", &XE::AudioSource::_Pitch );
type->Property( "Position", &XE::AudioSource::_Position );
type->Property( "Velocity", &XE::AudioSource::_Velocity );
type->Property( "Direction", &XE::AudioSource::_Direction );
type->Property( "MinDistance", &XE::AudioSource::_MinDistance );
type->Property( "MaxDistance", &XE::AudioSource::_MaxDistance );
END_META()

void XE::AudioSource::Startup()
{
	if( _PlayOnStart )
	{
		Play();
	}
}

void XE::AudioSource::Update( XE::float32 dt )
{

}

void XE::AudioSource::Clearup()
{

}

bool XE::AudioSource::GetLoop() const
{
	return _Loop;
}

void XE::AudioSource::SetLoop( bool val )
{
	_Loop = val;
}

bool XE::AudioSource::GetPlayOnStart() const
{
	return _PlayOnStart;
}

void XE::AudioSource::SetPlayOnStart( bool val )
{
	_PlayOnStart = val;
}

XE::float32 XE::AudioSource::GetGain() const
{
	return _Gain;
}

void XE::AudioSource::SetGain( XE::float32 val )
{
	_Gain = val;
}

XE::float32 XE::AudioSource::GetPitch() const
{
	return _Pitch;
}

void XE::AudioSource::SetPitch( XE::float32 val )
{
	_Pitch = val;
}

const XE::Vec3f & XE::AudioSource::GetPosition() const
{
	return _Position;
}

void XE::AudioSource::SetPosition( const XE::Vec3f & val )
{
	_Position = val;
}

const XE::Vec3f & XE::AudioSource::GetVelocity() const
{
	return _Velocity;
}

void XE::AudioSource::SetVelocity( const XE::Vec3f & val )
{
	_Velocity = val;
}

const XE::Vec3f & XE::AudioSource::GetDirection() const
{
	return _Direction;
}

void XE::AudioSource::SetDirection( const XE::Vec3f & val )
{
	_Direction = val;
}

XE::float32 XE::AudioSource::GetMinDistacne() const
{
	return _MinDistance;
}

void XE::AudioSource::SetMinDistance( XE::float32 val )
{
	_MinDistance = val;
}

XE::float32 XE::AudioSource::GetMaxDistance() const
{
	return _MaxDistance;
}

void XE::AudioSource::SetMaxDistance( XE::float32 val )
{
	_MaxDistance = val;
}

const XE::AudioClipPtr & XE::AudioSource::GetAudioClip() const
{
	return _AudioClip;
}

void XE::AudioSource::SetAudioClip( const XE::AudioClipPtr & val )
{
	_AudioClip = val;
}
