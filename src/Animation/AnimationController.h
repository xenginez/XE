/*!
 * \file	AnimationController.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/16
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATIONCONTROLLER_H__ADFBA495_DC2D_4E46_BBC6_A81D9890F673
#define ANIMATIONCONTROLLER_H__ADFBA495_DC2D_4E46_BBC6_A81D9890F673

#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

DECL_PTR( Skeleton );

class XE_API AnimationController : public XE::Object
{
	OBJECT( AnimationController, Object )

public:
	AnimationController();

	~AnimationController() override;

public:
	void Startup();

	void Update( XE::float32 val );

	void Clearup();

public:
	XE::ObjectPtr GetGameObject() const;

	void SetGameObject( XE::ObjectPtr & val );

	XE::SkeletonPtr GetSkeleton() const;

	void SetSkeleton( const XE::SkeletonPtr & val );

public:
	bool GetEnable();

	bool GetEnable( XE::uint32 layer );

	bool GetEnable( const XE::String & layer );

	void SetEnable( bool val );

	void SetEnable( XE::uint32 layer, bool val );

	void SetEnable( const XE::String & layer, bool val );

public:
	bool GetParameterBool( const XE::String & val ) const;

	XE::int32 GetParameterInt( const XE::String & val ) const;

	XE::float32 GetParameterFloat( const XE::String & val ) const;

	XE::String GetParameterString( const XE::String & val ) const;

public:
	void SetParameterBool( const XE::String & name, bool val );

	void SetParameterInt( const XE::String & name, XE::int32 val );

	void SetParameterFloat( const XE::String & name, XE::float32 val );

	void SetParameterString( const XE::String & name, XE::String val );

private:
	XE::Variant GetParameter( const XE::String & val ) const;

	void SetParameter( const XE::String & name, const XE::Variant & val );

private:
	bool _Enable;
	XE::ObjectPtr _GameObject;
	XE::SkeletonPtr _Skeleton;
	Array< AnimatorPtr > _Animators;
	Map< XE::String, XE::Variant > _Parameters;
	Map< XE::String, XE::uint32 > _AnimatorMaps;
};

END_XE_NAMESPACE

#endif // ANIMATIONCONTROLLER_H__ADFBA495_DC2D_4E46_BBC6_A81D9890F673
