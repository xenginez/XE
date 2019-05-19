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

void XE::AudioListenerComponent::OnUpdate( float dt )
{
	Super::OnUpdate( dt );

	AL_CHECK( alListener3f( AL_VELOCITY, 0.0f, 0.0f, 0.0f ) );

	Vec3 pos = GetTransform()->GetWorldPosition();
	AL_CHECK( alListener3f( AL_POSITION, pos.x, pos.y, pos.z ) );

	Vec3 forward = GetTransform()->GetWorldForward();
	Vec3 up = GetTransform()->GetWorldUp();
	float buf[6] = { forward.x, forward.y, forward.z, up.x, up.y, up.z };
	AL_CHECK( alListenerfv( AL_ORIENTATION, buf ) );
}
