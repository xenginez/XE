#include "AudioSoundSource.h"

#include <AL/al.h>

#include "AudioSound.h"

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
		XE::Array<XE::uint8> buf = _Sound->GetOneFrame();
		if( buf.size() != 0 )
		{
			ALenum format = 0;
			switch( _Sound->GetBits() )
			{
			case 8:
				if( _Sound->GetChannel() == 1 )
				{
					format = AL_FORMAT_MONO8;
				}
				else if( _Sound->GetChannel() == 2 )
				{
					format = AL_FORMAT_STEREO8;
				}
				break;
			case 16:
				if( _Sound->GetChannel() == 1 )
				{
					format = AL_FORMAT_MONO16;
				}
				else if( _Sound->GetChannel() == 2 )
				{
					format = AL_FORMAT_STEREO16;
				}
				break;
			default:
				break;
			}
			ALuint bufferID = 0;
			CHECK_AL( alGenBuffers( 1, &bufferID ) );
			CHECK_AL( alBufferData( bufferID, format, buf.data(), buf.size(), _Sound->GetSampleRate() ) );
			CHECK_AL( alSourceQueueBuffers( _SourceID, 1, &bufferID ) );
		}
		else if( GetLoop() )
		{
			_Sound->Seek( 0 );
		}
		else
		{
			Stop();
		}
	}
}

void XE::AudioSoundSource::Clearup()
{
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

void XE::AudioSoundSource::Back()
{
	CHECK_AL( alSourceRewind( _SourceID ) );
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

const XE::Vec3 & XE::AudioSoundSource::GetPosition() const
{
	return _Position;
}

void XE::AudioSoundSource::SetPosition( const XE::Vec3 & val )
{
	_Position = val;
	_Dirty = true;
}

const XE::Vec3 & XE::AudioSoundSource::GetVelocity() const
{
	return _Velocity;
}

void XE::AudioSoundSource::SetVelocity( const XE::Vec3 & val )
{
	_Velocity = val;
	_Dirty = true;
}

const XE::Vec3 & XE::AudioSoundSource::GetDirection() const
{
	return _Direction;
}

void XE::AudioSoundSource::SetDirection( const XE::Vec3 & val )
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
