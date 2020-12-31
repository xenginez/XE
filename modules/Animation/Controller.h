/*!
 * \file	Controller.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/22
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef CONTROLLER_H__791BB598_7A96_4DEC_B252_90E6EF8ACCAC
#define CONTROLLER_H__791BB598_7A96_4DEC_B252_90E6EF8ACCAC

#include "Type.h"

BEG_ANIMATION_NAMESPACE

class ANIMATION_API Controller : public XE::Object
{
	OBJECT( Controller, Object )

public:
	using ProcessEventCallback = std::function<void( const XE::EventPtr & )>;

public:
	Controller();

	~Controller() override;

public:
	void Startup();

	void Update( XE::float32 dt );

	void Clearup();

	void AssetLoad() override;

public:
	const XE::String & GetName() const;

	void SetName( const XE::String & val );

	const XE::Array< XE::Mat4x4f > & GetSkeletonTransform() const;

	void SetSkeletonTransform( const XE::Array< XE::Mat4x4f > & val );

	const XE::AssetPtr<Animation::Skeleton> & GetSkeleton() const;

	void SetSkeleton( const XE::AssetPtr<Animation::Skeleton> & val );

	const XE::Array< Animation::LayerPtr > & GetAnimationLayers() const;

	void SetAnimationLayers( const XE::Array< Animation::LayerPtr > & val );

public:
	XE::Variant GetKey( const XE::String & val ) const;

	void SetKey( const XE::String & key, const XE::Variant & val );

	const XE::Map<XE::String, XE::Variant> & GetKeys() const;

	void SetKeys( const XE::Map<XE::String, XE::Variant> & val );

public:
	void PostEvent( const XE::EventPtr & val );

	void ProcessEvent( const XE::EventPtr & val ) override;

	void SetProcessEventCallback( const ProcessEventCallback & val );

private:
	XE::String _Name;
	XE::Map<XE::String, XE::Variant> _Keys;
	XE::Array< Animation::LayerPtr > _Layers;
	XE::Array< XE::Mat4x4f > _SkeletonTransform;
	ProcessEventCallback _ProcessEventCallback;
	XE::AssetPtr<Animation::Skeleton> _Skeleton;
};

END_ANIMATION_NAMESPACE

#endif // CONTROLLER_H__791BB598_7A96_4DEC_B252_90E6EF8ACCAC
