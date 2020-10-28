#include "AnimationSampler.h"

#include <ozz/base/maths/vec_float.h>
#include <ozz/base/containers/vector.h>
#include <ozz/base/maths/soa_transform.h>
#include <ozz/animation/runtime/skeleton.h>
#include <ozz/animation/runtime/animation.h>
#include <ozz/animation/runtime/sampling_job.h>

#include "Skeleton.h"
#include "SkeletonAnimation.h"

XE::AnimationSampler::AnimationSampler()
	:_Local( nullptr ), _Cache( nullptr )
{

}

XE::AnimationSampler::~AnimationSampler()
{

}

void XE::AnimationSampler::Startup( XE::SkeletonPtr skeleton, XE::SkeletonAnimationPtr animation )
{
	_Skeleton = skeleton;
	_Animation = animation;

	auto skeleton = reinterpret_cast< ozz::animation::Skeleton * >( _Skeleton->GetHandle().GetValue() );

	_Cache = new ozz::animation::SamplingCache( skeleton->num_joints() );
	_Local = new XE::Array< ozz::math::SoaTransform >( skeleton->num_soa_joints() );
}

void XE::AnimationSampler::Update( XE::float32 time )
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

void XE::AnimationSampler::Clearup()
{
	auto cache = reinterpret_cast< ozz::animation::SamplingCache >( _Cache );
	delete cache;
	_Cache = nullptr;
	auto local = reinterpret_cast< XE::Array< ozz::math::SoaTransform > >( _Local );
	delete local;
	_Local = nullptr;

	_Skeleton = nullptr;
	_Animation = nullptr;
}

void * XE::AnimationSampler::GetLocal() const
{
	return _Local;
}
