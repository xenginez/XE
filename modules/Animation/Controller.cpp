#include "Controller.h"

#include <tbb/parallel_for.h>

#include <ozz/base/maths/simd_math.h>
#include <ozz/base/maths/soa_transform.h>
#include <ozz/animation/runtime/skeleton.h>
#include <ozz/animation/runtime/blending_job.h>
#include <ozz/animation/runtime/local_to_model_job.h>

#include "Skeleton.h"
#include "Layer.h"

BEG_META( Animation::Controller )
type->Property( "Keys", &Animation::Controller::_Keys );
type->Property( "Layers", &Animation::Controller::_Layers );
type->Property( "Skeleton", &Animation::Controller::_Skeleton );
END_META()

Animation::Controller::Controller()
{

}

Animation::Controller::~Controller()
{

}

void Animation::Controller::Startup()
{
	auto skeleton = reinterpret_cast< ozz::animation::Skeleton * >( _Skeleton->GetHandle().GetValue() );
	_SkeletonTransform.resize( skeleton->num_joints() );

	for( auto & layer : _Layers )
	{
		layer->SetAnimationController( XE_THIS( Animation::Controller ) );
		layer->Startup();
	}
}

void Animation::Controller::Update( XE::float32 dt )
{
	for( auto & layer : _Layers )
	{
		layer->Update( dt );
	}

	XE::Array<ozz::animation::BlendingJob::Layer> layers( _Layers.size(), XE::MemoryResource::GetStackMemoryResource() );
	tbb::parallel_for( XE::uint64( 0 ), XE::uint64( _Layers.size() ), XE::uint64( 1 ), [this, &layers, dt]( XE::uint64 i )
					   {
						   _Layers[i]->Update( dt );
						   auto local = reinterpret_cast< XE::Array< ozz::math::SoaTransform > * >( _Layers[i]->GetLocalTransform() );

						   layers[i].weight = _Layers[i]->GetWeight();
						   layers[i].transform = ozz::make_span( *local );
					   } );

	auto skeleton = reinterpret_cast< ozz::animation::Skeleton * >( _Skeleton->GetHandle().GetValue() );

	XE::Array< ozz::math::SoaTransform > local( skeleton->num_soa_joints(), XE::MemoryResource::GetStackMemoryResource() );
	ozz::animation::BlendingJob blend_job;
	blend_job.threshold = 1.0f;
	blend_job.layers = ozz::make_span( layers );
	blend_job.bind_pose = skeleton->joint_bind_poses();
	blend_job.output = ozz::make_span( local );
	if( !blend_job.Run() )
	{
		XE_LOG( XE::LoggerLevel::Error, "%1 animation controller runing blend job error", GetName() );
		return;
	}

	XE::Array< ozz::math::Float4x4 > models( skeleton->num_joints(), XE::MemoryResource::GetStackMemoryResource() );
	ozz::animation::LocalToModelJob ltm_job;
	ltm_job.skeleton = skeleton;
	ltm_job.input = ozz::make_span( local );
	ltm_job.output = ozz::make_span( models );

	if( !ltm_job.Run() )
	{
		XE_LOG( XE::LoggerLevel::Error, "%1 animation controller runing local to model job error", GetName() );
		return;
	}

	for( XE::uint64 i = 0; i < models.size(); ++i )
	{
		_SkeletonTransform[i][0][0] = ozz::math::GetX( models[i].cols[0] );
		_SkeletonTransform[i][1][0] = ozz::math::GetY( models[i].cols[0] );
		_SkeletonTransform[i][2][0] = ozz::math::GetZ( models[i].cols[0] );
		_SkeletonTransform[i][3][0] = ozz::math::GetW( models[i].cols[0] );

		_SkeletonTransform[i][0][1] = ozz::math::GetX( models[i].cols[1] );
		_SkeletonTransform[i][1][1] = ozz::math::GetY( models[i].cols[1] );
		_SkeletonTransform[i][2][1] = ozz::math::GetZ( models[i].cols[1] );
		_SkeletonTransform[i][3][1] = ozz::math::GetW( models[i].cols[1] );

		_SkeletonTransform[i][0][2] = ozz::math::GetX( models[i].cols[2] );
		_SkeletonTransform[i][1][2] = ozz::math::GetY( models[i].cols[2] );
		_SkeletonTransform[i][2][2] = ozz::math::GetZ( models[i].cols[2] );
		_SkeletonTransform[i][3][2] = ozz::math::GetW( models[i].cols[2] );

		_SkeletonTransform[i][0][3] = ozz::math::GetX( models[i].cols[3] );
		_SkeletonTransform[i][1][3] = ozz::math::GetY( models[i].cols[3] );
		_SkeletonTransform[i][2][3] = ozz::math::GetZ( models[i].cols[3] );
		_SkeletonTransform[i][3][3] = ozz::math::GetW( models[i].cols[3] );
	}
}

void Animation::Controller::Clearup()
{
	for( auto & layer : _Layers )
	{
		layer->Clearup();
	}

	_Skeleton = nullptr;
}

void Animation::Controller::AssetLoad()
{
	Super::AssetLoad();

	_Skeleton.AsyncLoad();

	for( auto & layer : _Layers )
	{
		layer->AssetLoad();
	}
}

const XE::String & Animation::Controller::GetName() const
{
	return _Name;
}

void Animation::Controller::SetName( const XE::String & val )
{
	_Name = val;
}

const XE::AssetPtr<Animation::Skeleton> & Animation::Controller::GetSkeleton() const
{
	return _Skeleton;
}

void Animation::Controller::SetSkeleton( const XE::AssetPtr<Animation::Skeleton> & val )
{
	_Skeleton = val;
}

const XE::Array< XE::Mat4x4f > & Animation::Controller::GetSkeletonTransform() const
{
	return _SkeletonTransform;
}

void Animation::Controller::SetSkeletonTransform( const XE::Array< XE::Mat4x4f > & val )
{
	_SkeletonTransform = val;
}

const XE::Array< Animation::LayerPtr > & Animation::Controller::GetAnimationLayers() const
{
	return _Layers;
}

void Animation::Controller::SetAnimationLayers( const XE::Array< Animation::LayerPtr > & val )
{
	_Layers = val;
}

XE::Variant Animation::Controller::GetKey( const XE::String & val ) const
{
	auto it = _Keys.find( val );

	if( it != _Keys.end() )
	{
		return it->second;
	}

	return {};
}

void Animation::Controller::SetKey( const XE::String & key, const XE::Variant & val )
{
	_Keys[key] = val;
}

const XE::Map<XE::String, XE::Variant> & Animation::Controller::GetKeys() const
{
	return _Keys;
}

void Animation::Controller::SetKeys( const XE::Map<XE::String, XE::Variant> & val )
{
	_Keys = val;
}

void Animation::Controller::PostEvent( const XE::EventPtr & val )
{
	if( _ProcessEventCallback )
	{
		_ProcessEventCallback( std::ref( val ) );
	}
	else
	{
		ProcessEvent( val );
	}
}

void Animation::Controller::ProcessEvent( const XE::EventPtr & val )
{
	for( auto & layer : _Layers )
	{
		layer->ProcessEvent( val );
	}
}

void Animation::Controller::SetProcessEventCallback( const ProcessEventCallback & val )
{
	_ProcessEventCallback = val;
}
