#include "AnimationState.h"

#include "AnimationLayer.h"
#include "AnimationController.h"

BEG_META( XE::AnimationState )
type->Property( "Name", &XE::AnimationState::_Name );
type->Property( "Handle", &XE::AnimationState::_Handle, XE::IMetaProperty::NoDesign );
type->Property( "AnimationConditions", &XE::AnimationState::_AnimationConditions, XE::IMetaProperty::NoDesign );
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

XE::AnimationLayerPtr XE::AnimationState::GetAnimationLayer() const
{
	return _AnimationLayer.lock();
}

void XE::AnimationState::SetAnimationLayer( XE::AnimationLayerPtr val )
{
	_AnimationLayer = val;
}

const XE::Array< XE::AnimationCondition > & XE::AnimationState::GetAnimationConditions() const
{
	return _AnimationConditions;
}

void XE::AnimationState::SetAnimationConditions( const XE::Array< XE::AnimationCondition > & val )
{
	_AnimationConditions = val;
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

	_Status = XE::AnimationStateStatus::NONE;
}

void XE::AnimationState::Clearup()
{
	OnClearup();
}

void XE::AnimationState::OnStartup()
{

}

void XE::AnimationState::OnEnter()
{

}

void XE::AnimationState::OnUpdate( XE::float32 dt )
{

}

void XE::AnimationState::OnQuit()
{

}

void XE::AnimationState::OnClearup()
{

}

void * XE::AnimationState::GetLocalTransform() const
{
	return GetAnimationLayer()->GetLocalTransform();
}
