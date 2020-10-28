#include "AnimationClipState.h"

#include <ozz/base/maths/vec_float.h>
#include <ozz/base/containers/vector.h>
#include <ozz/base/maths/soa_transform.h>
#include <ozz/animation/runtime/skeleton.h>
#include <ozz/animation/runtime/animation.h>
#include <ozz/animation/runtime/sampling_job.h>

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

	_Cache = new ozz::animation::SamplingCache();
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

	XE::Array<ozz::math::SoaTransform> locals( XE::MemoryResource::GetStackMemoryResource() );
	ozz::animation::SamplingCache * cache = reinterpret_cast< ozz::animation::SamplingCache * >( _Cache );

	auto animation = reinterpret_cast< ozz::animation::Animation * >( GetSkeletonAnimation()->GetHandle().GetValue() );
	auto skeleton = reinterpret_cast< ozz::animation::Skeleton * >( GetAnimationLayer()->GetAnimationController()->GetSkeleton()->GetHandle().GetValue() );

	locals.resize( skeleton->num_joints() );

	ozz::animation::SamplingJob sampling_job;
	sampling_job.animation = animation;
	sampling_job.cache = cache;
	sampling_job.ratio = _CurrentTime;
	sampling_job.output = ozz::make_span( locals );

	if( !sampling_job.Run() )
	{
		XE_LOG( LoggerLevel::Error, "%1 state sampling job runing error", GetName() );
		SetStatus( XE::AnimationStateStatus::FAILED );
		return;
	}

	XE::Array< XE::Mat4 > transform( XE::MemoryResource::GetStackMemoryResource() );
	// TODO: 
	GetAnimationLayer()->SetLocalTransform( transform );

	if( _CurrentTime >= _EndTime )
	{
		SetStatus( XE::AnimationStateStatus::SUCCESS );
	}
}

void XE::AnimationClipState::OnClearup()
{
	Super::OnClearup();

	delete _Cache;
	_Cache = nullptr;
	_SkeletonAnimation = nullptr;
}

void XE::AnimationClipState::AssetLoad()
{
	Super::AssetLoad();

	_SkeletonAnimation->AssetLoad();
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
