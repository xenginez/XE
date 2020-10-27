#include "AnimationController.h"

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

	// TODO: 混合所有层的LocalTransform转换成ModelTransform
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
