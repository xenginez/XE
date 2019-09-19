/*!
 * \file	AnimationIKConstraint.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/18
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATIONIKCONSTRAINT_H__401C278D_845B_4C72_9781_39DF13767EE0
#define ANIMATIONIKCONSTRAINT_H__401C278D_845B_4C72_9781_39DF13767EE0

#include "Type.h"

BEG_XE_NAMESPACE

class ANIMATION_API AnimationIKConstraint : public XE::Object
{
	OBJECT( AnimationIKConstraint, Object )

public:
	AnimationIKConstraint();

	~AnimationIKConstraint();

public:
	IKConstraintHandle GetHandle() const;

	void SetHandle( IKConstraintHandle val );

public:
	XE::float32 GetStiffness() const;

	void SetStiffness( XE::float32 val );

	XE::float32 GetStretchiness() const;

	void SetStretchiness( XE::float32 val );

	const XE::Vec2 & GetLengthConstraints() const;

	void SetLengthConstraints( const XE::Vec2 & val );

private:
	IKConstraintHandle _Handle;

	XE::float32 _Stiffness;
	XE::float32 _Stretchiness;
	XE::Vec2 _LengthConstraints;
};

END_XE_NAMESPACE

#endif // ANIMATIONIKCONSTRAINT_H__401C278D_845B_4C72_9781_39DF13767EE0
