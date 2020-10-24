#include "BlendingLayer.h"

BEG_META( XE::BlendingLayer )
type->Property( "Name", XE::BlendingLayer::_Name );
type->Property( "Weight", XE::BlendingLayer::_Weight );
type->Property( "Animation", XE::BlendingLayer::_Animation );
END_META()

XE::BlendingLayer::BlendingLayer()
{

}

XE::BlendingLayer::~BlendingLayer()
{

}

XE::float32 XE::BlendingLayer::GetWeight() const
{
	return _Weight;
}

void XE::BlendingLayer::SetWeight( XE::float32 val )
{
	_Weight = val;
}

const XE::String & XE::BlendingLayer::GetName() const
{
	return _Name;
}

void XE::BlendingLayer::SetName( const XE::String & val )
{
	_Name = val;
}

const XE::AssetPtr< XE::SkeletonAnimation > & XE::BlendingLayer::GetSkeletonAnimation() const
{
	return _Animation;
}

void XE::BlendingLayer::SetSkeletonAnimation( const XE::AssetPtr< XE::SkeletonAnimation > & val )
{
	_Animation = val;
}

void XE::BlendingLayer::AssetLoad()
{
	_Animation.Load();
}
