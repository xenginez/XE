#include "AudioService.h"

#include <AL/al.h>
#include <AL/alc.h>

USING_XE

BEGIN_META( AudioService )
END_META()

XE::AudioService::AudioService()
{

}

XE::AudioService::~AudioService()
{

}

bool XE::AudioService::Startup()
{
	auto device = alcOpenDevice( nullptr );
	auto context = alcCreateContext( device, nullptr );

	alcMakeContextCurrent( context );

	alDistanceModel( AL_INVERSE_DISTANCE );

	alDopplerFactor( 1 );
	alDopplerVelocity( 343 );

	return true;
}

void XE::AudioService::Update()
{

}

void XE::AudioService::Clearup()
{
	auto context = alcGetCurrentContext();
	auto device = alcGetContextsDevice( context );

	alcMakeContextCurrent( 0 );

	alcDestroyContext( context );
	alcCloseDevice( device );
}
