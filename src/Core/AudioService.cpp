#include "AudioService.h"

#include <AL/al.h>
#include <AL/alc.h>

#include "Utils/Logger.h"

#define CHECK_ALC( X ) \
{ \
	X; \
	switch( alcGetError( device ) ) \
	{ \
	case ALC_INVALID_DEVICE: \
		XE_LOG( XE::LoggerLevel::Error, "invalid device [%1]", #X ); \
		break; \
	case ALC_INVALID_CONTEXT: \
		XE_LOG( XE::LoggerLevel::Error, "invalid context [%1]", #X ); \
		break; \
	case ALC_INVALID_ENUM: \
		XE_LOG( XE::LoggerLevel::Error, "invalid enum [%1]", #X ); \
		break; \
	case ALC_INVALID_VALUE: \
		XE_LOG( XE::LoggerLevel::Error, "invalid value [%1]", #X ); \
		break; \
	case ALC_OUT_OF_MEMORY: \
		XE_LOG( XE::LoggerLevel::Error, "out of memory [%1]", #X ); \
		break; \
	default: \
		break; \
	} \
}

BEG_META( XE::AudioService )
END_META()

XE::AudioService::AudioService()
{

}

XE::AudioService::~AudioService()
{

}

void XE::AudioService::Prepare()
{

}

bool XE::AudioService::Startup()
{
	ALCcontext * context = nullptr;
	ALCdevice * device = nullptr;

	device = alcOpenDevice( nullptr );

	if( device )
	{
		CHECK_ALC( context = alcCreateContext( device, nullptr ) );
		CHECK_ALC( alcMakeContextCurrent( context ) );
	}
	else
	{
		XE_LOG( LoggerLevel::Error, "create openal device failed" );
	}

	return true;
}

void XE::AudioService::Update()
{
	ALfloat orientation[6];
	std::memcpy( orientation, GetListenerOrientation().d, sizeof( ALfloat ) * 3 );
	std::memcpy( orientation + sizeof( ALfloat ) * 3, XE::Vec3f::Up.d, sizeof( ALfloat ) * 3 );

	alListenerfv( AL_ORIENTATION, orientation );
	alListenerfv( AL_POSITION, GetListenerPosition().d );
	alListenerfv( AL_VELOCITY, GetListenerVelocity().d );
}

void XE::AudioService::Clearup()
{
	ALCcontext * context = alcGetCurrentContext();
	ALCdevice * device = alcGetContextsDevice( context );

	if( context )
	{
		CHECK_ALC( alcMakeContextCurrent( NULL ) );
		CHECK_ALC( alcDestroyContext( context ) );

		alcCloseDevice( device );
	}
	else
	{
		XE_LOG( LoggerLevel::Error, "close openal device failed" );
	}
}

void XE::AudioService::Resume()
{
	ALCcontext * context = alcGetCurrentContext();
	ALCdevice * device = alcGetContextsDevice( context );

	CHECK_ALC( alcProcessContext( context ) );
}

void XE::AudioService::Suspend()
{
	ALCcontext * context = alcGetCurrentContext();
	ALCdevice * device = alcGetContextsDevice( context );

	CHECK_ALC( alcSuspendContext( context ) );
}
