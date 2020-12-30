#include "Layer.h"

#include <ozz/base/maths/soa_transform.h>
#include <ozz/animation/runtime/skeleton.h>

#include "Skeleton.h"
#include "State.h"
#include "Controller.h"

BEG_META( Animation::Layer )
type->Property( "Name", &Animation::Layer::_Name );
type->Property( "Weight", &Animation::Layer::_Weight );
type->Property( "BlendMode", &Animation::Layer::_BlendMode );
type->Property( "SkeletonMask", &Animation::Layer::_SkeletonMask );
type->Property( "States", &Animation::Layer::_States, XE::IMetaProperty::NoDesign );
type->Property( "RootState", &Animation::Layer::_RootState, XE::IMetaProperty::NoDesign );
END_META()

Animation::Layer::Layer()
{

}

Animation::Layer::~Layer()
{

}

void Animation::Layer::Startup()
{
	auto skeleton = reinterpret_cast< ozz::animation::Skeleton * >( GetAnimationController()->GetSkeleton()->GetHandle().GetValue() );
	_LocalTransform = new XE::Array< ozz::math::SoaTransform >( skeleton->num_soa_joints() );

	for( auto & state : _States )
	{
		state->SetAnimationLayer( XE_THIS( Animation::Layer ) );
		state->Startup();
	}

	_CurrentState = _RootState;
}

void Animation::Layer::Update( XE::float32 dt )
{
	auto & state = _States[_CurrentState.GetValue()];

	switch( state->GetStatus() )
	{
	case Animation::StateStatus::NONE:
		state->Enter();
		break;
	case Animation::StateStatus::RUNNING:
		state->Update( dt );
		break;
	case Animation::StateStatus::FAILED:
		state->Quit();
		break;
	case Animation::StateStatus::SUCCESS:
		state->Quit();
		break;
	default:
		break;
	}

	const auto & conds = state->GetAnimationConditions();
	for( const auto & cond : conds )
	{
		if( cond->Judgment() )
		{
			if( state->GetStatus() == Animation::StateStatus::RUNNING )
			{
				state->Quit();
			}

			_CurrentState = cond->GetNextStateHandle();
		}
	}
}

void Animation::Layer::Clearup()
{
	for( auto & state : _States )
	{
		if( state->GetStatus() == Animation::StateStatus::RUNNING
			|| state->GetStatus() == Animation::StateStatus::FAILED
			|| state->GetStatus() == Animation::StateStatus::SUCCESS )
		{
			state->Quit();
		}

		state->Clearup();
	}
}

void Animation::Layer::AssetLoad()
{
	for( auto & state : _States )
	{
		state->AssetLoad();
	}
}

XE::float32 Animation::Layer::GetWeight() const
{
	return _Weight;
}

void Animation::Layer::SetWeight( XE::float32 val )
{
	_Weight = val;
}

const XE::String & Animation::Layer::GetName() const
{
	return _Name;
}

void Animation::Layer::SetName( const XE::String & val )
{
	_Name = val;
}

const XE::Layer & Animation::Layer::GetSkeletonMask() const
{
	return _SkeletonMask;
}

void Animation::Layer::SetSkeletonMask( const XE::Layer & val )
{
	_SkeletonMask = val;
}

Animation::BlendMode Animation::Layer::GetBlendMode() const
{
	return _BlendMode;
}

void Animation::Layer::SetBlendMode( Animation::BlendMode val )
{
	_BlendMode = val;
}

Animation::StateHandle Animation::Layer::GetRootState() const
{
	return _RootState;
}

void Animation::Layer::SetRootState( Animation::StateHandle val )
{
	_RootState = val;
}

Animation::ControllerPtr Animation::Layer::GetAnimationController() const
{
	return _AnimationController.lock();
}

void Animation::Layer::SetAnimationController( Animation::ControllerPtr val )
{
	_AnimationController = val;
}

const XE::Array< Animation::StatePtr > & Animation::Layer::GetAnimationStates() const
{
	return _States;
}

void Animation::Layer::SetAnimationStates( const XE::Array< Animation::StatePtr > & val )
{
	_States = val;
}

void * Animation::Layer::GetLocalTransform() const
{
	return _LocalTransform;
}
