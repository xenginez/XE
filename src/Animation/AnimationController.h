/*!
 * \file	AnimationController.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/22
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATIONCONTROLLER_H__791BB598_7A96_4DEC_B252_90E6EF8ACCAC
#define ANIMATIONCONTROLLER_H__791BB598_7A96_4DEC_B252_90E6EF8ACCAC

#include "Utils/Asset.h"
#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API AnimationController : public XE::Object
{
	OBJECT( AnimationController, Object )

public:
	AnimationController();

	~AnimationController() override;

public:
	void Startup();

	void Update( XE::float32 dt );

	void Clearup();

	void AssetLoad() override;

public:
	const XE::String & GetName() const;

	void SetName( const XE::String & val );

	const XE::AssetPtr<XE::Skeleton> & GetSkeleton() const;

	void SetSkeleton( const XE::AssetPtr<XE::Skeleton> & val );

	const XE::Array< XE::AnimationLayerPtr > & GetAnimationLayers() const;

	void SetAnimationLayers( const XE::Array< XE::AnimationLayerPtr > & val );

public:
	XE::Variant GetKey( const XE::String & val ) const;

	void SetKey( const XE::String & key, const XE::Variant & val );

	const XE::Map<XE::String, XE::Variant> & GetKeys() const;

	void SetKeys( const XE::Map<XE::String, XE::Variant> & val );

private:
	XE::String _Name;
	XE::AssetPtr<XE::Skeleton> _Skeleton;
	XE::Map<XE::String, XE::Variant> _Keys;
	XE::Array< XE::AnimationLayerPtr > _Layers;
};

END_XE_NAMESPACE

#endif // ANIMATIONCONTROLLER_H__791BB598_7A96_4DEC_B252_90E6EF8ACCAC
