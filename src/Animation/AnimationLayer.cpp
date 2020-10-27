#include "AnimationLayer.h"

#include "AnimationState.h"

BEG_META( XE::AnimationLayer )
type->Property( "Name", &XE::AnimationLayer::_Name );
type->Property( "Weight", &XE::AnimationLayer::_Weight );
type->Property( "BlendMode", &XE::AnimationLayer::_BlendMode );
type->Property( "SkeletonMask", &XE::AnimationLayer::_SkeletonMask );
type->Property( "States", &XE::AnimationLayer::_States, XE::IMetaProperty::NoDesign );
type->Property( "RootState", &XE::AnimationLayer::_RootState, XE::IMetaProperty::NoDesign );
END_META()

XE::AnimationLayer::AnimationLayer()
{

}

XE::AnimationLayer::~AnimationLayer()
{

}

void XE::AnimationLayer::Startup()
{
	for( auto & state : _States )
	{
		state->SetAnimationLayer( XE_THIS( XE::AnimationLayer ) );
		state->Startup();
	}

	_CurrentState = _RootState;
}

void XE::AnimationLayer::Update( XE::float32 dt )
{
	auto & state = _States[_CurrentState.GetValue()];

	switch( state->GetStatus() )
	{
	case XE::AnimationStateStatus::NONE:
		state->Enter();
		break;
	case XE::AnimationStateStatus::RUNNING:
		state->Update( dt );
		break;
	case XE::AnimationStateStatus::SUCCESS:
		state->Quit();
	default:
		break;
	}

	const auto & conds = state->GetAnimationConditions();
	for( const auto & cond : conds )
	{
		if( cond.Judgment() )
		{
			if( state->GetStatus() == XE::AnimationStateStatus::RUNNING )
			{
				state->Quit();
			}

			_CurrentState = cond.GetNextStateHandle();
		}
	}
}

void XE::AnimationLayer::Clearup()
{
	for( auto & state : _States )
	{
		if( state->GetStatus() == XE::AnimationStateStatus::RUNNING || state->GetStatus() == XE::AnimationStateStatus::SUCCESS )
		{
			state->Quit();
		}

		state->Clearup();
	}
}

void XE::AnimationLayer::AssetLoad()
{
	for( auto & state : _States )
	{
		state->AssetLoad();
	}
}

XE::float32 XE::AnimationLayer::GetWeight() const
{
	return _Weight;
}

void XE::AnimationLayer::SetWeight( XE::float32 val )
{
	_Weight = val;
}

const XE::String & XE::AnimationLayer::GetName() const
{
	return _Name;
}

void XE::AnimationLayer::SetName( const XE::String & val )
{
	_Name = val;
}

const XE::Layer & XE::AnimationLayer::GetSkeletonMask() const
{
	return _SkeletonMask;
}

void XE::AnimationLayer::SetSkeletonMask( const XE::Layer & val )
{
	_SkeletonMask = val;
}

XE::AnimationBlendMode XE::AnimationLayer::GetBlendMode() const
{
	return _BlendMode;
}

void XE::AnimationLayer::SetBlendMode( XE::AnimationBlendMode val )
{
	_BlendMode = val;
}

XE::AnimationStateHandle XE::AnimationLayer::GetRootState() const
{
	return _RootState;
}

void XE::AnimationLayer::SetRootState( XE::AnimationStateHandle val )
{
	_RootState = val;
}

const XE::Array< XE::Mat4 > & XE::AnimationLayer::GetLocalTransform() const
{
	return _LocalTransform;
}

void XE::AnimationLayer::SetLocalTransform( const XE::Array< XE::Mat4 > & val )
{
	_LocalTransform = val;
}

XE::AnimationControllerPtr XE::AnimationLayer::GetAnimationController() const
{
	return _AnimationController.lock();
}

void XE::AnimationLayer::SetAnimationController( XE::AnimationControllerPtr val )
{
	_AnimationController = val;
}

const XE::Array< XE::AnimationStatePtr > & XE::AnimationLayer::GetAnimationStates() const
{
	return _States;
}

void XE::AnimationLayer::SetAnimationStates( const XE::Array< XE::AnimationStatePtr > & val )
{
	_States = val;
}
