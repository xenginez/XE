#include "AnimationClipState.h"

#include <ozz/base/maths/soa_transform.h>

#include "Utils/Logger.h"

#include "Skeleton.h"
#include "AnimationLayer.h"
#include "AnimationController.h"

BEG_META( XE::AnimationClipState )
type->Property( "Loop", &XE::AnimationClipState::_Loop );
type->Property( "Speed", &XE::AnimationClipState::_Speed );
type->Property( "StartTime", &XE::AnimationClipState::_StartTime );
type->Property( "EndTime", &XE::AnimationClipState::_EndTime );
type->Property( "SkeletonAnimation", &XE::AnimationClipState::_SkeletonAnimation );
END_META()

XE::AnimationClipState::AnimationClipState()
	:_Loop( false ), _Speed( 1.0f ), _StartTime( 0.0f ), _EndTime( 0.0f )
{

}

XE::AnimationClipState::~AnimationClipState()
{

}

void XE::AnimationClipState::OnStartup()
{
	Super::OnStartup();

	_Sampler.Startup( GetAnimationLayer()->GetAnimationController()->GetSkeleton().GetShared(), _SkeletonAnimation.GetShared() );
}

void XE::AnimationClipState::OnEnter()
{
	Super::OnEnter();

	_CurrentTime = _StartTime;
}

void XE::AnimationClipState::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	_CurrentTime += dt * _Speed;
	if( _CurrentTime >= _EndTime )
	{
		if( _Loop )
		{
			_CurrentTime = _CurrentTime - _EndTime + _StartTime;
		}
		else
		{
			_CurrentTime = _EndTime;
		}
	}

	if( !_Sampler.Update( _CurrentTime ) )
	{
		XE_LOG( LoggerLevel::Error, "%1 runing animation error", GetName() );
		SetStatus( XE::AnimationStateStatus::FAILED );
		return;
	}

	auto local1 = reinterpret_cast< XE::Array< ozz::math::SoaTransform > * >( GetLocalTransform() );
	auto local2 = reinterpret_cast< XE::Array< ozz::math::SoaTransform > * >( _Sampler.GetLocal() );
	*local1 = *local2;

	if( _CurrentTime >= _EndTime )
	{
		SetStatus( XE::AnimationStateStatus::SUCCESS );
	}
}

void XE::AnimationClipState::OnClearup()
{
	Super::OnClearup();

	_SkeletonAnimation = nullptr;
}

void XE::AnimationClipState::AssetLoad()
{
	Super::AssetLoad();

	_SkeletonAnimation.AsyncLoad();
}

bool XE::AnimationClipState::GetLoop() const
{
	return _Loop;
}

void XE::AnimationClipState::SetLoop( bool val )
{
	_Loop = val;
}

XE::float32 XE::AnimationClipState::GetSpeed() const
{
	return _Speed;
}

void XE::AnimationClipState::SetSpeed( XE::float32 val )
{
	_Speed = val;
}

XE::float32 XE::AnimationClipState::GetEndTime() const
{
	return _EndTime;
}

void XE::AnimationClipState::SetEndTime( XE::float32 val )
{
	_EndTime = val;
}

XE::float32 XE::AnimationClipState::GetStartTime() const
{
	return _StartTime;
}

void XE::AnimationClipState::SetStartTime( XE::float32 val )
{
	_StartTime = val;
}

const XE::AssetPtr< XE::SkeletonAnimation > & XE::AnimationClipState::GetSkeletonAnimation() const
{
	return _SkeletonAnimation;
}

void XE::AnimationClipState::SetSkeletonAnimation( const XE::AssetPtr< XE::SkeletonAnimation > & val )
{
	_SkeletonAnimation = val;
}
