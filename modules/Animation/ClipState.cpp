#include "ClipState.h"

#include <ozz/base/maths/soa_transform.h>

#include "Skeleton.h"
#include "Layer.h"
#include "Controller.h"

BEG_META( Animation::ClipState )
type->Property( "Loop", &Animation::ClipState::_Loop );
type->Property( "Speed", &Animation::ClipState::_Speed );
type->Property( "StartTime", &Animation::ClipState::_StartTime );
type->Property( "EndTime", &Animation::ClipState::_EndTime );
type->Property( "SkeletonAnimation", &Animation::ClipState::_SkeletonAnimation );
END_META()

Animation::ClipState::ClipState()
	:_Loop( false ), _Speed( 1.0f ), _StartTime( 0.0f ), _EndTime( 0.0f )
{

}

Animation::ClipState::~ClipState()
{

}

void Animation::ClipState::OnStartup()
{
	Super::OnStartup();

	_Sampler.Startup( GetAnimationLayer()->GetAnimationController()->GetSkeleton().GetShared(), _SkeletonAnimation.GetShared() );
}

void Animation::ClipState::OnEnter()
{
	Super::OnEnter();

	_CurrentTime = _StartTime;
}

void Animation::ClipState::OnUpdate( XE::float32 dt )
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
		XE_LOG( XE::LoggerLevel::Error, "%1 runing animation error", GetName() );
		SetStatus( Animation::StateStatus::FAILED );
		return;
	}

	auto local1 = reinterpret_cast< XE::Array< ozz::math::SoaTransform > * >( GetLocalTransform() );
	auto local2 = reinterpret_cast< XE::Array< ozz::math::SoaTransform > * >( _Sampler.GetLocal() );
	*local1 = *local2;

	if( _CurrentTime >= _EndTime )
	{
		SetStatus( Animation::StateStatus::SUCCESS );
	}
}

void Animation::ClipState::OnClearup()
{
	Super::OnClearup();

	_SkeletonAnimation = nullptr;
}

void Animation::ClipState::AssetLoad()
{
	Super::AssetLoad();

	_SkeletonAnimation.AsyncLoad();
}

bool Animation::ClipState::GetLoop() const
{
	return _Loop;
}

void Animation::ClipState::SetLoop( bool val )
{
	_Loop = val;
}

XE::float32 Animation::ClipState::GetSpeed() const
{
	return _Speed;
}

void Animation::ClipState::SetSpeed( XE::float32 val )
{
	_Speed = val;
}

XE::float32 Animation::ClipState::GetEndTime() const
{
	return _EndTime;
}

void Animation::ClipState::SetEndTime( XE::float32 val )
{
	_EndTime = val;
}

XE::float32 Animation::ClipState::GetStartTime() const
{
	return _StartTime;
}

void Animation::ClipState::SetStartTime( XE::float32 val )
{
	_StartTime = val;
}

const XE::AssetPtr< Animation::SkeletonAnimation > & Animation::ClipState::GetSkeletonAnimation() const
{
	return _SkeletonAnimation;
}

void Animation::ClipState::SetSkeletonAnimation( const XE::AssetPtr< Animation::SkeletonAnimation > & val )
{
	_SkeletonAnimation = val;
}
