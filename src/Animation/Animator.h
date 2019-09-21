/*!
 * \file	AnimationControllor.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/15
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATIONCONTROLLOR_H__D062F72F_C871_4E50_8716_7A512A2D6EBC
#define ANIMATIONCONTROLLOR_H__D062F72F_C871_4E50_8716_7A512A2D6EBC

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API Animator : public XE::Object
{
	OBJECT( Animator, Object )

public:
	static constexpr XE::uint32 AnyState = 0;
	static constexpr XE::uint32 npos = std::numeric_limits<XE::uint32>::max();

public:
	Animator();

	~Animator() override;

public:
	void Startup();

	void Update( XE::float32 val );

	void Clearup();

public:
	void Play();

	void Stop();

	bool IsPlaying() const;

public:
	bool GetEnable() const;

	void SetEnable( bool val );

	const XE::String & GetName() const;

	void SetName( const XE::String & val );

	AnimationControllerPtr GetAnimationController() const;

	void SetAnimationController( const AnimationControllerPtr & val );

protected:
	bool _Enable;
	XE::String _Name;

	XE::uint32 _CurState;
	XE::uint32 _EntryState;
	Array< AnimationStatePtr > _States;
	Array< AnimationTransitionPtr > _Transitions;

	AnimationControllerWPtr _Controller;
};

END_XE_NAMESPACE

#endif // ANIMATIONCONTROLLOR_H__D062F72F_C871_4E50_8716_7A512A2D6EBC
