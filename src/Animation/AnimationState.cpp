#include "AnimationState.h"

#include "AnimationLayer.h"
#include "AnimationController.h"

BEG_META( XE::AnimationState )
END_META()

XE::AnimationState::AnimationState()
	:_Status( XE::AnimationStateStatus::NONE )
{

}

XE::AnimationState::~AnimationState()
{

}

XE::AnimationStateHandle XE::AnimationState::GetHandle() const
{
	return _Handle;
}

XE::AnimationLayerPtr XE::AnimationState::GetAnimationLayer() const
{
	return _AnimationLayer.lock();
}

XE::AnimationControllerPtr XE::AnimationState::GetAnimationController() const
{
	return _AnimationController.lock();
}

const XE::String & XE::AnimationState::GetName() const
{
	return _Name;
}

void XE::AnimationState::SetName( const XE::String & val )
{
	_Name = val;
}

XE::AnimationStateStatus XE::AnimationState::GetStatus() const
{
	return _Status;
}

void XE::AnimationState::SetStatus( XE::AnimationStateStatus val )
{
	_Status = val;
}

void XE::AnimationState::Startup()
{
	OnStartup();

	_Status = XE::AnimationStateStatus::NONE;
}

void XE::AnimationState::Enter()
{
	OnEnter();

	_Status = XE::AnimationStateStatus::RUNNING;
}

void XE::AnimationState::Update( XE::float32 dt )
{
	OnUpdate( dt );
}

void XE::AnimationState::Quit()
{
	OnQuit();

	_Status = XE::AnimationStateStatus::SUCCESS;
}

void XE::AnimationState::Clearup()
{
	OnClearup();
}
