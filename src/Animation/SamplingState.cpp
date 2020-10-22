#include "SamplingState.h"

#include <ozz/base/maths/vec_float.h>
#include <ozz/base/maths/soa_transform.h>
#include <ozz/base/containers/vector.h>
#include <ozz/animation/runtime/skeleton.h>
#include <ozz/animation/runtime/animation.h>
#include <ozz/animation/runtime/sampling_job.h>
#include <ozz/animation/runtime/local_to_model_job.h>

#include "Skeleton.h"
#include "AnimationController.h"

BEG_META( XE::SamplingState )
type->Property( "SkeletonAnimation", &XE::SamplingState::GetSkeletonAnimation, &XE::SamplingState::SetSkeletonAnimation );
END_META()

struct XE::SamplingState::Private
{
	ozz::animation::SamplingCache _Cache;
	ozz::vector<ozz::math::Float4x4> _Models;
	ozz::vector<ozz::math::SoaTransform> _Locals;
	XE::AssetPtr< XE::SkeletonAnimation > _Animation;
};

XE::SamplingState::SamplingState()
	:_p( new Private )
{

}

XE::SamplingState::~SamplingState()
{
	delete _p;
}

const XE::AssetPtr< XE::SkeletonAnimation > & XE::SamplingState::GetSkeletonAnimation() const
{
	return _p->_Animation;
}

void XE::SamplingState::SetSkeletonAnimation( const XE::AssetPtr< XE::SkeletonAnimation > & val )
{
	_p->_Animation = val;
}

void XE::SamplingState::OnUpdate( XE::float32 dt )
{
	ozz::animation::SamplingJob sampling_job;
	sampling_job.animation = reinterpret_cast< ozz::animation::Animation * >( _p->_Animation->GetHandle().GetValue() );
	sampling_job.cache = &_p->_Cache;
	sampling_job.ratio = GetTime();
	sampling_job.output = ozz::make_span( _p->_Locals );
	
	if( !sampling_job.Run() )
	{
		return;
	}

	ozz::animation::LocalToModelJob ltm_job;
	ltm_job.skeleton = reinterpret_cast< ozz::animation::Skeleton * >( GetAnimationController()->GetSkeleton()->GetHandle().GetValue() );
	ltm_job.input = ozz::make_span( _p->_Locals );
	ltm_job.output = ozz::make_span( _p->_Models );
	if( !ltm_job.Run() )
	{
		return;
	}

	// TODO: �������ݵ�������
}
