#include "BlendingState.h"

#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>

#include <ozz/base/maths/vec_float.h>
#include <ozz/base/containers/vector.h>
#include <ozz/base/maths/soa_transform.h>
#include <ozz/animation/runtime/skeleton.h>
#include <ozz/animation/runtime/animation.h>
#include <ozz/animation/runtime/sampling_job.h>
#include <ozz/animation/runtime/blending_job.h>
#include <ozz/animation/runtime/local_to_model_job.h>

#include "Utils/Logger.h"
#include "Scene/GameObject.h"

#include "Skeleton.h"
#include "AnimationController.h"

static constexpr int MAX_OZZ_SAMPLING_CACHE = 5;

BEG_META( XE::BlendingState )
END_META()

struct XE::BlendingState::Private
{
	bool _Loop = false;
	XE::float32 _Time = 0.0f;
	XE::float32 _Speed = 1.0f;
	XE::float32 _Threshold = 1.0f;
	XE::Array< XE::BlendingLayerPtr > _Layers;
	XE::Array< XE::Pair<XE::float32, XE::EventPtr> > _Events;

	XE::Array< XE::Mat4 > _Transform;
	XE::EventPtr _UpdateSkeletonTransformEvent;

	XE::float32 _MaxDuration = 0;
	ozz::vector< ozz::vector<ozz::math::SoaTransform> > _LayerLocals;
	std::array< ozz::animation::SamplingCache, MAX_OZZ_SAMPLING_CACHE > _LayerCaches;

	ozz::vector<ozz::math::Float4x4> _BlendModels;
	ozz::vector<ozz::math::SoaTransform> _BlendLocals;
};

XE::BlendingState::BlendingState()
{

}

XE::BlendingState::~BlendingState()
{

}

bool XE::BlendingState::GetLoop() const
{
	return _p->_Loop;
}

void XE::BlendingState::SetLoop( bool val )
{
	_p->_Loop = val;
}

XE::float32 XE::BlendingState::GetTime() const
{
	return _p->_Time;
}

void XE::BlendingState::SetTime( XE::float32 val )
{
	_p->_Time = val;
}

XE::float32 XE::BlendingState::GetSpeed() const
{
	return _p->_Speed;
}

void XE::BlendingState::SetSpeed( XE::float32 val )
{
	_p->_Speed = val;
}

XE::float32 XE::BlendingState::GetThreshold() const
{
	return _p->_Threshold;
}

void XE::BlendingState::SetThreshold( XE::float32 val )
{
	_p->_Threshold = val;
}

const XE::Array< XE::BlendingLayerPtr > & XE::BlendingState::GetLayers() const
{
	return _p->_Layers;
}

void XE::BlendingState::SetLayers( const XE::Array< XE::BlendingLayerPtr > & val )
{
	_p->_Layers = val;
}

const XE::Array< XE::Pair<XE::float32, XE::EventPtr> > & XE::BlendingState::GetAnimationEvents() const
{
	return _p->_Events;
}

void XE::BlendingState::SetAnimationEvents( const XE::Array< XE::Pair<XE::float32, XE::EventPtr> > & val )
{
	_p->_Events = val;
}

void XE::BlendingState::OnStartup()
{
	Super::OnStartup();

	auto skel = reinterpret_cast< ozz::animation::Skeleton * >( GetAnimationController()->GetSkeleton()->GetHandle().GetValue() );

	for( auto & layer : _p->_Layers )
	{
		auto anim = reinterpret_cast< ozz::animation::Animation * >( layer->GetSkeletonAnimation()->GetHandle().GetValue() );
		_p->_MaxDuration = std::max( _p->_MaxDuration, anim->duration() );
	}

	_p->_LayerLocals.resize( _p->_Layers.size() );

	for( auto & local : _p->_LayerLocals )
	{
		local.resize( skel->num_joints() );
	}

	_p->_BlendModels.resize( skel->num_joints() );
	_p->_BlendLocals.resize( skel->num_joints() );

	auto thi = XE_THIS( XE::Object );
	auto obj = GetAnimationController()->GetGameObject();
	_p->_Transform.resize( skel->num_joints() );
	_p->_UpdateSkeletonTransformEvent = XE::MakeShared<XE::Event>( UPDATE_SKELETON_TRANSFORM, thi, obj,
		XE::BasicMemoryView< XE::Mat4 >( _p->_Transform.data(), _p->_Transform.size() ) );

	for( auto & it : _p->_Events )
	{
		it.second->sender = thi;
		it.second->recver = obj;
	}
}

void XE::BlendingState::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	if( _p->_Time >= _p->_MaxDuration )
	{
		return;
	}
	_p->_Time += dt * _p->_Speed;
	XE::float32 time = std::min( _p->_Time, _p->_MaxDuration );
	if( _p->_Time >= _p->_MaxDuration && _p->_Loop )
	{
		_p->_Time = 0;
		for( auto & it : _p->_Events )
		{
			it.second->accept = false;
		}
	}

	auto skel = reinterpret_cast< ozz::animation::Skeleton * >( GetAnimationController()->GetSkeleton()->GetHandle().GetValue() );

	tbb::parallel_for( XE::uint64( 0 ), XE::uint64( _p->_Layers.size() ), XE::uint64( 1 ), [this, time]( XE::uint64 i )
					   {
						   auto anim = reinterpret_cast< ozz::animation::Animation * >( _p->_Layers[i]->GetSkeletonAnimation()->GetHandle().GetValue() );

						   ozz::animation::SamplingJob sampling_job;
						   sampling_job.animation = anim;
						   sampling_job.cache = &_p->_LayerCaches[i];
						   sampling_job.ratio = time;
						   sampling_job.output = ozz::make_span( _p->_LayerLocals[i] );
						   if( !sampling_job.Run() )
						   {
							   XE_LOG( LoggerLevel::Error, "%1 state %2 layer samping job runing error", GetName(), _p->_Layers[i]->GetName() );
							   return;
						   }
					   } );

	XE::Array<ozz::animation::BlendingJob::Layer> layers( XE::MemoryResource::GetStackMemoryResource() );
	layers.resize( _p->_Layers.size() );
	for( int i = 0; i < layers.size(); ++i )
	{
		layers[i].weight = _p->_Layers[i]->GetWeight();
		layers[i].transform = make_span( _p->_LayerLocals[i] );
	}

	ozz::animation::BlendingJob blend_job;
	blend_job.threshold = _p->_Threshold;
	blend_job.layers = { layers.data(), layers.size() };
	blend_job.bind_pose = skel->joint_bind_poses();
	blend_job.output = make_span( _p->_BlendLocals );
	if( !blend_job.Run() )
	{
		XE_LOG( LoggerLevel::Error, "%1 state blend job runing error", GetName() );
		return;
	}

	ozz::animation::LocalToModelJob ltm_job;
	ltm_job.skeleton = skel;
	ltm_job.input = ozz::make_span( _p->_BlendLocals );
	ltm_job.output = ozz::make_span( _p->_BlendModels );
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

	auto mit = _p->_BlendModels.begin();
	auto tit = _p->_Transform.begin();
	for( ; mit != _p->_BlendModels.end(); ++mit, ++tit )
	{
		std::memcpy( tit->d, mit->cols[0].m128_f32, 4 * 4 * sizeof( XE::float32 ) );
	}
	_p->_UpdateSkeletonTransformEvent->accept = false;
	_p->_UpdateSkeletonTransformEvent->recver->ProcessEvent( _p->_UpdateSkeletonTransformEvent );
}

void XE::BlendingState::OnClearup()
{
	Super::OnClearup();

	_p->_Transform.clear();
	_p->_BlendLocals.clear();
	_p->_BlendModels.clear();
	_p->_LayerLocals.clear();
	_p->_UpdateSkeletonTransformEvent = nullptr;

	for( auto & it : _p->_Events )
	{
		it.second->sender = nullptr;
		it.second->recver = nullptr;
	}
}

void XE::BlendingState::AssetLoad()
{
	for( auto & layer : _p->_Layers )
	{
		layer->AssetLoad();
	}
}
