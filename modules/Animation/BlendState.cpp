#include "BlendState.h"

#include <tbb/parallel_for.h>

#include <ozz/base/maths/soa_transform.h>
#include <ozz/animation/runtime/skeleton.h>
#include <ozz/animation/runtime/blending_job.h>

#include "Skeleton.h"
#include "Layer.h"
#include "Controller.h"

BEG_META( Animation::BlendState )
type->Property( "Loop", &Animation::BlendState::_Loop );
type->Property( "Speed", &Animation::BlendState::_Speed );
type->Property( "Layers", &Animation::BlendState::_Layers );
END_META()

Animation::BlendState::BlendState()
	:_Loop( false ), _Speed( 1.0f )
{

}

Animation::BlendState::~BlendState()
{

}

void Animation::BlendState::OnStartup()
{
	Super::OnStartup();

	for( auto & layer : _Layers )
	{
		_MaxTime = std::max( _MaxTime, layer.GetSkeletonAnimation()->GetDuration() );
		layer.Startup( GetAnimationLayer()->GetAnimationController()->GetSkeleton().GetShared() );
	}
}

void Animation::BlendState::OnEnter()
{
	Super::OnEnter();

	_CurrentTime = 0;
}

void Animation::BlendState::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	_CurrentTime += dt * _Speed;
	if( _CurrentTime >= _MaxTime )
	{
		if( _Loop )
		{
			_CurrentTime = std::max( _CurrentTime - _MaxTime, 0.0f );
		}
		else
		{
			_CurrentTime = _MaxTime;
		}
	}

	XE::Array<ozz::animation::BlendingJob::Layer> layers( _Layers.size(), XE::MemoryResource::GetStackMemoryResource() );
	tbb::parallel_for( XE::uint64( 0 ), XE::uint64( _Layers.size() ), XE::uint64( 1 ), [this, &layers]( XE::uint64 i )
					   {
						   _Layers[i].Update( _CurrentTime );
						   auto local = reinterpret_cast< XE::Array< ozz::math::SoaTransform > * >( _Layers[i].GetAnimationSampler().GetLocal() );

						   layers[i].weight = _Layers[i].GetWeight();
						   layers[i].transform = ozz::make_span( *local );
					   } );

	auto skeleton = reinterpret_cast< ozz::animation::Skeleton * >( GetAnimationLayer()->GetAnimationController()->GetSkeleton()->GetHandle().GetValue() );

	auto local = reinterpret_cast< XE::Array< ozz::math::SoaTransform > * >( GetLocalTransform() );
	ozz::animation::BlendingJob blend_job;
	blend_job.threshold = _Threshold;
	blend_job.layers = { layers.data(), layers.size() };
	blend_job.bind_pose = skeleton->joint_bind_poses();
	blend_job.output = ozz::make_span( *local );
	if( !blend_job.Run() )
	{
		XE_LOG( XE::LoggerLevel::Error, "%1 state blend job runing error", GetName() );
		SetStatus( Animation::StateStatus::FAILED );
		return;
	}

	if( _CurrentTime >= _MaxTime )
	{
		SetStatus( Animation::StateStatus::SUCCESS );
	}
}

void Animation::BlendState::OnClearup()
{
	Super::OnClearup();

	for( auto & layer : _Layers )
	{
		layer.Clearup();
	}
}

void Animation::BlendState::AssetLoad()
{
	Super::AssetLoad();

	for( auto & layer : _Layers )
	{
		layer.AssetLoad();
	}
}

bool Animation::BlendState::GetLoop() const
{
	return _Loop;
}

void Animation::BlendState::SetLoop( bool val )
{
	_Loop = val;
}

XE::float32 Animation::BlendState::GetSpeed() const
{
	return _Speed;
}

void Animation::BlendState::SetSpeed( XE::float32 val )
{
	_Speed = val;
}

XE::float32 Animation::BlendState::GetThreshold() const
{
	return _Threshold;
}

void Animation::BlendState::SetThreshold( XE::float32 val )
{
	_Threshold = val;
}
