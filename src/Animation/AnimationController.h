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

#include "Type.h"

BEG_XE_NAMESPACE

class ANIMATION_API AnimationController : public XE::Object
{
	OBJECT( AnimationController, Object )

public:
	AnimationController();

	~AnimationController() override;

public:
	void Activate();

	void Activate( XE::uint32 val );

	void Activate( const XE::String & val );

	void Deactivate();

	void Deactivate( XE::uint32 val );

	void Deactivate( const XE::String & val );

public:
	void Startup();

	void Update( XE::float32 val );

	void Clearup();

public:
	void Play();

	void Play( XE::uint32 val );

	void Play( const XE::String & val );

public:
	void Stop();

	void Stop( XE::uint32 val );

	void Stop( const XE::String & val );

public:
	bool IsPlaying() const;

	bool IsPlaying( XE::uint32 val ) const;

	bool IsPlaying( const XE::String & val ) const;

public:
	XE::Variant GetParameter( const XE::String & val ) const;

	void SetParameter( const XE::String & name, const XE::Variant & val );

public:
	template< typename T >
	T GetParameterT( const XE::String & val ) const
	{
		return GetParameter( val ).Value<T>();
	}

private:
	Array< AnimatorPtr > _Animators;
	Map< XE::String, XE::Variant > _Parameters;
	Map< XE::String, XE::uint32 > _AnimatorMaps;
};

END_XE_NAMESPACE

#endif // ANIMATIONCONTROLLER_H__ADFBA495_DC2D_4E46_BBC6_A81D9890F673
