#include "State.h"

#include "Layer.h"
#include "Controller.h"

BEG_META( Animation::State )
type->Property( "Name", &Animation::State::_Name );
type->Property( "Handle", &Animation::State::_Handle, XE::IMetaProperty::NoDesign );
type->Property( "AnimationConditions", &Animation::State::_AnimationConditions, XE::IMetaProperty::NoDesign );
END_META()

Animation::State::State()
	:_Status( Animation::StateStatus::NONE )
{

}

Animation::State::~State()
{

}

Animation::StateHandle Animation::State::GetHandle() const
{
	return _Handle;
}

const XE::String & Animation::State::GetName() const
{
	return _Name;
}

void Animation::State::SetName( const XE::String & val )
{
	_Name = val;
}

Animation::StateStatus Animation::State::GetStatus() const
{
	return _Status;
}

void Animation::State::SetStatus( Animation::StateStatus val )
{
	_Status = val;
}

Animation::LayerPtr Animation::State::GetAnimationLayer() const
{
	return _AnimationLayer.lock();
}

void Animation::State::SetAnimationLayer( Animation::LayerPtr val )
{
	_AnimationLayer = val;
}

const XE::Array< Animation::ConditionPtr > & Animation::State::GetAnimationConditions() const
{
	return _AnimationConditions;
}

void Animation::State::SetAnimationConditions( const XE::Array< Animation::ConditionPtr > & val )
{
	_AnimationConditions = val;
}

void Animation::State::Startup()
{
	OnStartup();

	_Status = Animation::StateStatus::NONE;
}

void Animation::State::Enter()
{
	OnEnter();

	_Status = Animation::StateStatus::RUNNING;
}

void Animation::State::Update( XE::float32 dt )
{
	OnUpdate( dt );
}

void Animation::State::Quit()
{
	OnQuit();

	_Status = Animation::StateStatus::NONE;
}

void Animation::State::Clearup()
{
	OnClearup();
}

void Animation::State::OnStartup()
{

}

void Animation::State::OnEnter()
{

}

void Animation::State::OnUpdate( XE::float32 dt )
{

}

void Animation::State::OnQuit()
{

}

void Animation::State::OnClearup()
{

}

void * Animation::State::GetLocalTransform() const
{
	return GetAnimationLayer()->GetLocalTransform();
}
