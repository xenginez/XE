#include "SamplingState.h"

#include <ozz/base/maths/vec_float.h>
#include <ozz/base/containers/vector.h>
#include <ozz/base/maths/soa_transform.h>
#include <ozz/animation/runtime/skeleton.h>
#include <ozz/animation/runtime/animation.h>
#include <ozz/animation/runtime/sampling_job.h>
#include <ozz/animation/runtime/local_to_model_job.h>

#include "Math/Mathf.h"
#include "Utils/Logger.h"
#include "AI/StateMachine.h"
#include "Scene/GameObject.h"

#include "Skeleton.h"
#include "AnimationController.h"

BEG_META( XE::SamplingState )
type->Property( "Loop", &XE::SamplingState::GetLoop, &XE::SamplingState::SetLoop );
type->Property( "Speed", &XE::SamplingState::GetSpeed, &XE::SamplingState::SetSpeed );
type->Property( "SkeletonAnimation", &XE::SamplingState::GetSkeletonAnimation, &XE::SamplingState::SetSkeletonAnimation );
type->Property( "AnimationEvents", &XE::SamplingState::GetAnimationEvents, &XE::SamplingState::SetAnimationEvents, XE::IMetaProperty::NoDesign );
END_META()

struct XE::SamplingState::Private
{
	bool _Loop = false;
	XE::float32 _Time = 0.0f;
	XE::float32 _Speed = 1.0f;
	XE::Array< XE::Pair<XE::float32, XE::EventPtr> > _Events;

	XE::Array< XE::Mat4 > _Transform;
	XE::EventPtr _UpdateSkeletonTransformEvent;

	XE::SkeletonAnimationPtr _Animation;
	ozz::animation::SamplingCache _Cache;
	ozz::vector<ozz::math::Float4x4> _Models;
	ozz::vector<ozz::math::SoaTransform> _Locals;
};

XE::SamplingState::SamplingState()
	:_p( new Private )
{

}

XE::SamplingState::~SamplingState()
{
	delete _p;
}

bool XE::SamplingState::GetLoop() const
{
	return _p->_Loop;
}

void XE::SamplingState::SetLoop( bool val )
{
	_p->_Loop = val;
}

XE::float32 XE::SamplingState::GetTime() const
{
	return _p->_Time;
}

void XE::SamplingState::SetTime( XE::float32 val )
{
	_p->_Time = val;
}

XE::float32 XE::SamplingState::GetSpeed() const
{
	return _p->_Speed;
}

void XE::SamplingState::SetSpeed( XE::float32 val )
{
	_p->_Speed = val;
}

const XE::SkeletonAnimationPtr & XE::SamplingState::GetSkeletonAnimation() const
{
	return _p->_Animation;
}

void XE::SamplingState::SetSkeletonAnimation( const XE::SkeletonAnimationPtr & val )
{
	_p->_Animation = val;
}

const XE::Array< XE::Pair<XE::float32, XE::EventPtr> > & XE::SamplingState::GetAnimationEvents() const
{
	return _p->_Events;
}

void XE::SamplingState::SetAnimationEvents( const XE::Array< XE::Pair<XE::float32, XE::EventPtr> > & val )
{
	_p->_Events = val;
}

void XE::SamplingState::OnStartup()
{
	Super::OnStartup();

	auto thi = XE_THIS( XE::Object );
	auto obj = GetAnimationController()->GetGameObject();
	auto skel = reinterpret_cast< ozz::animation::Skeleton * >( GetAnimationController()->GetSkeleton()->GetHandle().GetValue() );

	_p->_Models.resize( skel->num_joints() );
	_p->_Locals.resize( skel->num_joints() );
	_p->_Transform.resize( skel->num_joints() );

	_p->_UpdateSkeletonTransformEvent = XE::MakeShared<XE::Event>(  UPDATE_SKELETON_TRANSFORM, thi, obj,
		XE::BasicMemoryView< XE::Mat4 >( _p->_Transform.data(), _p->_Transform.size() ) );

	for( auto & it : _p->_Events )
	{
		it.second->sender = thi;
		it.second->recver = obj;
	}
}

void XE::SamplingState::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	auto anim = reinterpret_cast< ozz::animation::Animation * >( _p->_Animation->GetHandle().GetValue() );
	auto skel = reinterpret_cast< ozz::animation::Skeleton * >( GetAnimationController()->GetSkeleton()->GetHandle().GetValue() );

	if( _p->_Time >= anim->duration() )
	{
		return;
	}
	_p->_Time += dt * _p->_Speed;
	XE::float32 time = std::min( _p->_Time, anim->duration() );
	if( _p->_Time >= anim->duration() && _p->_Loop )
	{
		_p->_Time = 0;
		for( auto & it : _p->_Events )
		{
			it.second->accept = false;
		}
	}

	ozz::animation::SamplingJob sampling_job;
	sampling_job.animation = anim;
	sampling_job.cache = &_p->_Cache;
	sampling_job.ratio = time;
	sampling_job.output = ozz::make_span( _p->_Locals );
	
	if( !sampling_job.Run() )
	{
		XE_LOG( LoggerLevel::Error, "%1 state sampling job runing error", GetName() );
		return;
	}

	ozz::animation::LocalToModelJob ltm_job;
	ltm_job.skeleton = skel;
	ltm_job.input = ozz::make_span( _p->_Locals );
	ltm_job.output = ozz::make_span( _p->_Models );
	if( !ltm_job.Run() )
	{
		XE_LOG( LoggerLevel::Error, "%1 state local to model job runing error", GetName() );
		return;
	}

	for( auto & it : _p->_Events )
	{
		if( _p->_Time >= it.first && !it.second->accept )
		{
			it.second->recver->ProcessEvent( it.second );
			it.second->accept = true;
		}
	}

	auto mit = _p->_Models.begin();
	auto tit = _p->_Transform.begin();
	for( ; mit != _p->_Models.end(); ++mit, ++tit )
	{
		std::memcpy( tit->d, mit->cols[0].m128_f32, 4 * 4 * sizeof( XE::float32 ) );
	}
	_p->_UpdateSkeletonTransformEvent->accept = false;
	_p->_UpdateSkeletonTransformEvent->recver->ProcessEvent( _p->_UpdateSkeletonTransformEvent );
}

void XE::SamplingState::OnClearup()
{
	Super::OnClearup();

	_p->_Locals.clear();
	_p->_Models.clear();
	_p->_Transform.clear();
	_p->_UpdateSkeletonTransformEvent = nullptr;

	for( auto & it : _p->_Events )
	{
		it.second->sender = nullptr;
		it.second->recver = nullptr;
	}
}
