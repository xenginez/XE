#include "AudioListenerComponent.h"

#include <AL/al.h>

#include <Audio/Audio.h>

USING_XE

BEG_META( AudioListenerComponent )
END_META()

XE::AudioListenerComponent::AudioListenerComponent()
{
	SetUpdate( true );
}

XE::AudioListenerComponent::~AudioListenerComponent()
{

}

void XE::AudioListenerComponent::OnUpdate( XE::real dt )
{
	Super::OnUpdate( dt );

	AL_CHECK( alListener3f( AL_VELOCITY, 0.0f, 0.0f, 0.0f ) );

	Vec3 pos = GetTransform()->GetWorldPosition();
	AL_CHECK( alListener3f( AL_POSITION, (ALfloat )pos.x, (ALfloat )pos.y, (ALfloat )pos.z ) );

	Vec3 forward = GetTransform()->GetWorldForward();
	Vec3 up = GetTransform()->GetWorldUp();
	ALfloat buf[6] = { (ALfloat )forward.x, (ALfloat )forward.y, (ALfloat )forward.z, (ALfloat )up.x, (ALfloat )up.y, (ALfloat )up.z };
	AL_CHECK( alListenerfv( AL_ORIENTATION, buf ) );
}