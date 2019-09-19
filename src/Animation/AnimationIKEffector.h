/*!
 * \file	AnimationIKEffector.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/18
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATIONIKEFFECTOR_H__918AFEEC_10DA_4997_88F7_9D08D25F1E80
#define ANIMATIONIKEFFECTOR_H__918AFEEC_10DA_4997_88F7_9D08D25F1E80

#include "Type.h"

BEG_XE_NAMESPACE

class ANIMATION_API AnimationIKEffector : public XE::Object
{
	OBJECT( AnimationIKEffector, Object )

public:
	AnimationIKEffector();

	~AnimationIKEffector();

public:
	IKEffectorHandle GetHandle() const;

	void SetHandle( IKEffectorHandle val );

public:
	bool GetWeightNlerp() const;

	void SetWeightNlerp( bool val );

	bool GetInheritParentRotation() const;

	void SetInheritParentRotation( bool val );

	const XE::Vec3 & GetTargetPosition() const;

	void SetTargetPosition( const XE::Vec3 & val );

	const XE::Quat & GetTargetRotation() const;

	void SetTargetRotation( const XE::Quat & val );

	XE::uint32 GetChainLength() const;

	void SetChainLength( XE::uint32 val );

	XE::float32 GetWeight() const;

	void SetWeight( XE::float32 val );

	XE::float32 GetRotationWeight() const;

	void SetRotationWeight( XE::float32 val );

	XE::float32 GetRotationDecay() const;

	void SetRotationDecay( XE::float32 val );

private:
	bool _WeightNlerp;
	bool _InheritParentRotation;
	XE::Vec3 _TargetPosition;
	XE::Quat _TargetRotation;
	XE::uint32 _ChainLength;
	XE::float32 _Weight;
	XE::float32 _RotationWeight;
	XE::float32 _RotationDecay;

	IKEffectorHandle _Handle;
};

END_XE_NAMESPACE

#endif // ANIMATIONIKEFFECTOR_H__918AFEEC_10DA_4997_88F7_9D08D25F1E80
