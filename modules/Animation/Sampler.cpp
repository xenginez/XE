#include "Sampler.h"

#include <ozz/base/maths/vec_float.h>
#include <ozz/base/containers/vector.h>
#include <ozz/base/maths/soa_transform.h>
#include <ozz/animation/runtime/skeleton.h>
#include <ozz/animation/runtime/animation.h>
#include <ozz/animation/runtime/sampling_job.h>

#include "Skeleton.h"
#include "SkeletonAnimation.h"

Animation::Sampler::Sampler()
	:_Local( nullptr ), _Cache( nullptr )
{

}

Animation::Sampler::~Sampler()
{

}

void Animation::Sampler::Startup( Animation::SkeletonPtr skeleton, Animation::SkeletonAnimationPtr animation )
{
	_Skeleton = skeleton;
	_Animation = animation;

	auto skel = reinterpret_cast< ozz::animation::Skeleton * >( _Skeleton->GetHandle().GetValue() );

	_Cache = new ozz::animation::SamplingCache( skel->num_joints() );
	_Local = new XE::Array< ozz::math::SoaTransform >( skel->num_soa_joints() );
}

bool Animation::Sampler::Update( XE::float32 time )
{
	auto cache = reinterpret_cast< ozz::animation::SamplingCache * >( _Cache );
	auto local = reinterpret_cast< XE::Array<ozz::math::SoaTransform> * >( _Local );
	auto skeleton = reinterpret_cast< ozz::animation::Skeleton * >( _Skeleton->GetHandle().GetValue() );
	auto animation = reinterpret_cast< ozz::animation::Animation * >( _Animation->GetHandle().GetValue() );

	ozz::animation::SamplingJob sampling_job;
	sampling_job.animation = animation;
	sampling_job.cache = cache;
	sampling_job.ratio = time;
	sampling_job.output = ozz::make_span( *local );

	if( !sampling_job.Run() )
	{
		return false;
	}

	return true;
}

void Animation::Sampler::Clearup()
{
	auto cache = reinterpret_cast< ozz::animation::SamplingCache * >( _Cache );
	delete cache;
	_Cache = nullptr;
	auto local = reinterpret_cast< XE::Array< ozz::math::SoaTransform > * >( _Local );
	delete local;
	_Local = nullptr;

	_Skeleton = nullptr;
	_Animation = nullptr;
}

void * Animation::Sampler::GetLocal() const
{
	return _Local;
}
