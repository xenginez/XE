#include "AnimationController.h"

#include <tbb/parallel_for.h>

#include <ozz/base/maths/simd_math.h>
#include <ozz/base/maths/soa_transform.h>
#include <ozz/animation/runtime/skeleton.h>
#include <ozz/animation/runtime/blending_job.h>
#include <ozz/animation/runtime/local_to_model_job.h>

#include "Utils/Logger.h"

#include "Skeleton.h"
#include "AnimationLayer.h"

BEG_META( XE::AnimationController )
type->Property( "Keys", &XE::AnimationController::_Keys );
type->Property( "Layers", &XE::AnimationController::_Layers );
type->Property( "Skeleton", &XE::AnimationController::_Skeleton );
END_META()

XE::AnimationController::AnimationController()
{

}

XE::AnimationController::~AnimationController()
{

}

void XE::AnimationController::Startup()
{
	auto skeleton = reinterpret_cast< ozz::animation::Skeleton * >( _Skeleton->GetHandle().GetValue() );
	_SkeletonTransform.resize( skeleton->num_joints() );

	for( auto & layer : _Layers )
	{
		layer->SetAnimationController( XE_THIS( XE::AnimationController ) );
		layer->Startup();
	}
}

void XE::AnimationController::Update( XE::float32 dt )
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
		XE_LOG( LoggerLevel::Error, "%1 animation controller runing blend job error", GetName() );
		return;
	}

	XE::Array< ozz::math::Float4x4 > models( skeleton->num_joints(), XE::MemoryResource::GetStackMemoryResource() );
	ozz::animation::LocalToModelJob ltm_job;
	ltm_job.skeleton = skeleton;
	ltm_job.input = ozz::make_span( local );
	ltm_job.output = ozz::make_span( models );

	if( !ltm_job.Run() )
	{
		XE_LOG( LoggerLevel::Error, "%1 animation controller runing local to model job error", GetName() );
		return;
	}

	for( XE::uint64 i = 0; i < models.size(); ++i )
	{
		_SkeletonTransform[i].m00 = ozz::math::GetX( models[i].cols[0] );
		_SkeletonTransform[i].m10 = ozz::math::GetY( models[i].cols[0] );
		_SkeletonTransform[i].m20 = ozz::math::GetZ( models[i].cols[0] );
		_SkeletonTransform[i].m30 = ozz::math::GetW( models[i].cols[0] );

		_SkeletonTransform[i].m01 = ozz::math::GetX( models[i].cols[1] );
		_SkeletonTransform[i].m11 = ozz::math::GetY( models[i].cols[1] );
		_SkeletonTransform[i].m21 = ozz::math::GetZ( models[i].cols[1] );
		_SkeletonTransform[i].m31 = ozz::math::GetW( models[i].cols[1] );

		_SkeletonTransform[i].m02 = ozz::math::GetX( models[i].cols[2] );
		_SkeletonTransform[i].m12 = ozz::math::GetY( models[i].cols[2] );
		_SkeletonTransform[i].m22 = ozz::math::GetZ( models[i].cols[2] );
		_SkeletonTransform[i].m32 = ozz::math::GetW( models[i].cols[2] );

		_SkeletonTransform[i].m03 = ozz::math::GetX( models[i].cols[3] );
		_SkeletonTransform[i].m13 = ozz::math::GetY( models[i].cols[3] );
		_SkeletonTransform[i].m23 = ozz::math::GetZ( models[i].cols[3] );
		_SkeletonTransform[i].m33 = ozz::math::GetW( models[i].cols[3] );
	}
}

void XE::AnimationController::Clearup()
{
	for( auto & layer : _Layers )
	{
		layer->Clearup();
	}

	_Skeleton = nullptr;
}

void XE::AnimationController::AssetLoad()
{
	Super::AssetLoad();

	_Skeleton.AsyncLoad();

	for( auto & layer : _Layers )
	{
		layer->AssetLoad();
	}
}

const XE::String & XE::AnimationController::GetName() const
{
	return _Name;
}

void XE::AnimationController::SetName( const XE::String & val )
{
	_Name = val;
}

const XE::AssetPtr<XE::Skeleton> & XE::AnimationController::GetSkeleton() const
{
	return _Skeleton;
}

void XE::AnimationController::SetSkeleton( const XE::AssetPtr<XE::Skeleton> & val )
{
	_Skeleton = val;
}

const XE::Array< XE::Mat4 > & XE::AnimationController::GetSkeletonTransform() const
{
	return _SkeletonTransform;
}

void XE::AnimationController::SetSkeletonTransform( const XE::Array< XE::Mat4 > & val )
{
	_SkeletonTransform = val;
}

const XE::Array< XE::AnimationLayerPtr > & XE::AnimationController::GetAnimationLayers() const
{
	return _Layers;
}

void XE::AnimationController::SetAnimationLayers( const XE::Array< XE::AnimationLayerPtr > & val )
{
	_Layers = val;
}

XE::Variant XE::AnimationController::GetKey( const XE::String & val ) const
{
	auto it = _Keys.find( val );

	if( it != _Keys.end() )
	{
		return it->second;
	}

	return {};
}

void XE::AnimationController::SetKey( const XE::String & key, const XE::Variant & val )
{
	_Keys[key] = val;
}

const XE::Map<XE::String, XE::Variant> & XE::AnimationController::GetKeys() const
{
	return _Keys;
}

void XE::AnimationController::SetKeys( const XE::Map<XE::String, XE::Variant> & val )
{
	_Keys = val;
}

void XE::AnimationController::PostEvent( const XE::EventPtr & val )
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

void XE::AnimationController::ProcessEvent( const EventPtr & val )
{
	for( auto & layer : _Layers )
	{
		layer->ProcessEvent( val );
	}
}

void XE::AnimationController::SetProcessEventCallback( const ProcessEventCallback & val )
{
	_ProcessEventCallback = val;
}
