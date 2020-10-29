#include "AnimationComponent.h"

#include "Scene/GameObject.h"

BEG_META( XE::AnimationComponent )
type->Property( "AnimationController", &XE::AnimationComponent::_AnimationController );
END_META()

XE::AnimationComponent::AnimationComponent()
{

}

XE::AnimationComponent::~AnimationComponent()
{

}

void XE::AnimationComponent::OnStartup()
{
	Super::OnStartup();
	
	_AnimationController->SetProcessEventCallback( [this]( const XE::EventPtr & val )
												   {
													   GetGameObject()->ProcessEvent( val );
												   } );
	_AnimationController->Startup();
}

void XE::AnimationComponent::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	_AnimationController->Update( dt );
}

void XE::AnimationComponent::OnClearup()
{
	_AnimationController->Clearup();
}
