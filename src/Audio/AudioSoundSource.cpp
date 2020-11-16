#include "AudioSoundSource.h"

#define MA_NO_WASAPI
#define MA_NO_DSOUND
#define MA_NO_WINMM
#define MA_NO_ALSA
#define MA_NO_PULSEAUDIO
#define MA_NO_JACK
#define MA_NO_COREAUDIO
#define MA_NO_SNDIO
#define MA_NO_AUDIO4
#define MA_NO_OSS
#define MA_NO_AAUDIO
#define MA_NO_OPENSL
#define MA_NO_WEBAUDIO
#define MA_NO_NULL
#define MA_NO_ENCODING
#define MA_NO_DEVICE_IO
#define MA_NO_THREADING
#define MA_NO_DEVICE_IO
#define MA_NO_GENERATION
#define MA_LOG_LEVEL MA_LOG_LEVEL_ERROR


#define STB_VORBIS_HEADER_ONLY
#include <miniaudio/stb_vorbis.c>

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio/miniaudio.h>

#undef STB_VORBIS_HEADER_ONLY
#include <miniaudio/stb_vorbis.c>

#include <AL/al.h>

#include "Utils/Logger.h"

#define AUDIO_FARME_SIZE 640

#define CHECK_AL( X ) \
{ \
	X; \
	switch( alGetError() ) \
	{ \
	case AL_INVALID_NAME: \
		XE_LOG( XE::LoggerLevel::Error, "invalid name [%1]", #X ); \
		break; \
	case AL_INVALID_ENUM: \
		XE_LOG( XE::LoggerLevel::Error, "invalid enum [%1]", #X ); \
		break; \
	case AL_INVALID_VALUE: \
		XE_LOG( XE::LoggerLevel::Error, "invalid value [%1]", #X ); \
		break; \
	case AL_INVALID_OPERATION: \
		XE_LOG( XE::LoggerLevel::Error, "invalid operation [%1]", #X ); \
		break; \
	case AL_OUT_OF_MEMORY: \
		XE_LOG( XE::LoggerLevel::Error, "out of memory [%1]", #X ); \
		break; \
	default: \
		break; \
	} \
}

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

void XE::AudioSoundSource::Startup()
{
	ma_decoder_config config = ma_decoder_config_init( ma_format_s16, 2, 48000 );

	_Decoder = new ma_decoder;
	ma_result result = ma_decoder_init_file( _Sound.u8string().c_str(), &config, _Decoder );
	if( result != MA_SUCCESS )
	{
		delete _Decoder;
		_Decoder = nullptr;
	}

	CHECK_AL( alGenSources( 1, &_SourceID ) );

	CHECK_AL( alSourcef( _SourceID, AL_MIN_GAIN, 0.0f ) );
	CHECK_AL( alSourcef( _SourceID, AL_MAX_GAIN, 1.0f ) );
	CHECK_AL( alSourcef( _SourceID, AL_ROLLOFF_FACTOR, 1.0f ) );
	CHECK_AL( alSourcei( _SourceID, AL_LOOPING, _Loop ? AL_TRUE : AL_FALSE ) );
	CHECK_AL( alSourcef( _SourceID, AL_SOURCE_TYPE, AL_STREAMING ) );

	SetAudioParam();
}

void XE::AudioSoundSource::Update( XE::float32 dt )
{
	if( _Dirty )
	{
		_Dirty = false;
		SetAudioParam();
	}

	ALint state = 0;
	ALint numqueued = 0;
	ALint numprocessed = 0; 

	CHECK_AL( alGetSourcei( _SourceID, AL_SOURCE_STATE, &state ) ); 
	CHECK_AL( alGetSourcei( _SourceID, AL_BUFFERS_QUEUED, &numqueued ) );
	CHECK_AL( alGetSourcei( _SourceID, AL_BUFFERS_PROCESSED, &numprocessed ) );

	for( ; numprocessed > 0; --numprocessed )
	{
		ALuint buff;
		CHECK_AL( alSourceUnqueueBuffers( _SourceID, 1, &buff ) );
		CHECK_AL( alDeleteBuffers( 1, &buff ) );
	}

	if( state == AL_PLAYING && numqueued <= 1 )
	{
		XE::uint8 buf[AUDIO_FARME_SIZE] = {};

		auto sz = ma_decoder_read_pcm_frames( _Decoder, buf, AUDIO_FARME_SIZE );

		if( sz != 0 )
		{
			ALuint bufferID = 0;
			ALenum format = AL_FORMAT_STEREO16;
			CHECK_AL( alGenBuffers( 1, &bufferID ) );
			CHECK_AL( alBufferData( bufferID, format, buf, sz, _Decoder->outputSampleRate ) );
			CHECK_AL( alSourceQueueBuffers( _SourceID, 1, &bufferID ) );
		}
		else if( GetLoop() )
		{
			ma_decoder_seek_to_pcm_frame( _Decoder, 0 );
		}
		else
		{
			Stop();
		}
	}
}

void XE::AudioSoundSource::Clearup()
{
	if( _Decoder )
	{
		ma_decoder_uninit( _Decoder );
		delete _Decoder;
		_Decoder = nullptr;
	}

	ALint numqueued = 0;
	ALint numprocessed = 0;
	CHECK_AL( alGetSourcei( _SourceID, AL_BUFFERS_QUEUED, &numqueued ) );
	CHECK_AL( alGetSourcei( _SourceID, AL_BUFFERS_PROCESSED, &numprocessed ) );

	for( ; numqueued > 0; --numqueued )
	{
		ALuint buff = 0;
		CHECK_AL( alSourceQueueBuffers( _SourceID, 1, &buff ) );
		CHECK_AL( alDeleteBuffers( 1, &buff ) );
	}

	for( ; numprocessed > 0; --numprocessed )
	{
		ALuint buff = 0;
		CHECK_AL( alSourceUnqueueBuffers( _SourceID, 1, &buff ) );
		CHECK_AL( alDeleteBuffers( 1, &buff ) );
	}

	alDeleteSources( 1, &_SourceID );
}

void XE::AudioSoundSource::Play()
{
	CHECK_AL( alSourcePlay( _SourceID ) );
}

void XE::AudioSoundSource::Stop()
{
	CHECK_AL( alSourceStop( _SourceID ) );
}

void XE::AudioSoundSource::Resume()
{
	CHECK_AL( alSourcePlay( _SourceID ) );
}

void XE::AudioSoundSource::Suspend()
{
	CHECK_AL( alSourcePause( _SourceID ) );
}

bool XE::AudioSoundSource::GetLoop() const
{
	return _Loop;
}

void XE::AudioSoundSource::SetLoop( bool val )
{
	_Loop = val;
	_Dirty = true;
}

XE::float32 XE::AudioSoundSource::GetGain() const
{
	return _Gain;
}

void XE::AudioSoundSource::SetGain( XE::float32 val )
{
	_Gain = val;
	_Dirty = true;
}

XE::float32 XE::AudioSoundSource::GetPitch() const
{
	return _Pitch;
}

void XE::AudioSoundSource::SetPitch( XE::float32 val )
{
	_Pitch = val;
	_Dirty = true;
}

const XE::Vec3f & XE::AudioSoundSource::GetPosition() const
{
	return _Position;
}

void XE::AudioSoundSource::SetPosition( const XE::Vec3f & val )
{
	_Position = val;
	_Dirty = true;
}

const XE::Vec3f & XE::AudioSoundSource::GetVelocity() const
{
	return _Velocity;
}

void XE::AudioSoundSource::SetVelocity( const XE::Vec3f & val )
{
	_Velocity = val;
	_Dirty = true;
}

const XE::Vec3f & XE::AudioSoundSource::GetDirection() const
{
	return _Direction;
}

void XE::AudioSoundSource::SetDirection( const XE::Vec3f & val )
{
	_Direction = val;
	_Dirty = true;
}

XE::float32 XE::AudioSoundSource::GetMinDistacne() const
{
	return _MinDistance;
}

void XE::AudioSoundSource::SetMinDistance( XE::float32 val )
{
	_MinDistance = val;
	_Dirty = true;
}

XE::float32 XE::AudioSoundSource::GetMaxDistance() const
{
	return _MaxDistance;
}

void XE::AudioSoundSource::SetMaxDistance( XE::float32 val )
{
	_MaxDistance = val;
	_Dirty = true;
}

void XE::AudioSoundSource::SetAudioParam()
{
	CHECK_AL( alSourcef( _SourceID, AL_GAIN, _Gain ) );
	CHECK_AL( alSourcef( _SourceID, AL_PITCH, _Pitch ) );
	CHECK_AL( alSourcef( _SourceID, AL_MAX_DISTANCE, _MaxDistance ) );
	CHECK_AL( alSourcef( _SourceID, AL_REFERENCE_DISTANCE, _MinDistance ) );

	CHECK_AL( alSourcefv( _SourceID, AL_POSITION, _Position.d ) );
	CHECK_AL( alSourcefv( _SourceID, AL_VELOCITY, _Velocity.d ) );
	CHECK_AL( alSourcefv( _SourceID, AL_DIRECTION, _Direction.d ) );
}