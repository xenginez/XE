#include "AudioSourceComponent.h"

#include <AL/al.h>

#include <Audio/Audio.h>

USING_XE

BEG_META( AudioSourceComponent )
type->Method( "Play", &AudioSourceComponent::Play );
type->Method( "Stop", &AudioSourceComponent::Stop );
type->Method( "Pause", &AudioSourceComponent::Pause );
type->Property( "Loop", &AudioSourceComponent::_Loop );
type->Property( "Volume", &AudioSourceComponent::_Volume );
type->Property( "Pitch", &AudioSourceComponent::_Pitch );
type->Property( "Sound", &AudioSourceComponent::_SoundPath );
END_META()

XE::AudioSourceComponent::AudioSourceComponent()
{

}

XE::AudioSourceComponent::~AudioSourceComponent()
{

}

bool XE::AudioSourceComponent::GetLoop() const
{
	return _Loop;
}

void XE::AudioSourceComponent::SetLoop( bool val )
{
	_Loop = val;
}

XE::float32 XE::AudioSourceComponent::GetVolume() const
{
	return _Volume;
}

void XE::AudioSourceComponent::SetVolume( XE::float32 val )
{
	_Volume = val;
}

XE::float32 XE::AudioSourceComponent::GetPitch() const
{
	return _Pitch;
}

void XE::AudioSourceComponent::SetPitch( XE::float32 val )
{
	_Pitch = val;
}

const XE::String& XE::AudioSourceComponent::GetSound() const
{
	return _SoundPath;
}

void XE::AudioSourceComponent::SetSound( const String& val )
{
	_SoundPath = val;
}

void XE::AudioSourceComponent::Play()
{
	if ( !_Play && _Sound )
	{
		AL_CHECK( alSourcePlay( _SourceHandle ) );

		_Play = true;
		_Pause = false;
	}
}

void XE::AudioSourceComponent::Stop()
{
	if ( !_Play && !_Pause && _Sound )
	{
		AL_CHECK( alSourceStop( _SourceHandle ) );

		_Play = false;
		_Pause = false;
		_SoundPlayDt = 0;
	}
}

void XE::AudioSourceComponent::Pause()
{
	if ( _Play && _Sound )
	{
		AL_CHECK( alSourcePause( _SourceHandle ) );

		_Pause = true;
		_Play = false;
	}
}

bool XE::AudioSourceComponent::IsPlay() const
{
	return _Play;
}

bool XE::AudioSourceComponent::IsStop() const
{
	return !_Play && !_Pause;
}

bool XE::AudioSourceComponent::IsPause() const
{
	return _Pause;
}

void XE::AudioSourceComponent::OnStartup()
{
	Super::OnStartup();

	// TODO: Sound Asset Load
	if ( _Sound )
	{
		AL_CHECK( alGenSources( 1, &_SourceHandle ) );
		AL_CHECK( alSourcei( _SourceHandle, AL_BUFFER, _Sound->GetBufferHandle() ) );
	}
}

void XE::AudioSourceComponent::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	if ( _Loop && _Sound )
	{
		_SoundPlayDt += dt;

		if ( _SoundPlayDt >= _Sound->GetDuration() )
		{
			_SoundPlayDt = 0;
			Play();
		}
	}
}

void XE::AudioSourceComponent::OnClearup()
{
	AL_CHECK( alDeleteSources( 1, &_SourceHandle ) );

	Super::OnClearup();
}
