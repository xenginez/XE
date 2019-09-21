/*!
 * \file	AnimationIKSolver.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/18
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATIONIKSOLVER_H__23350757_7A32_4A7D_A723_66A8ED64D4A8
#define ANIMATIONIKSOLVER_H__23350757_7A32_4A7D_A723_66A8ED64D4A8

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API AnimationIKEffector
{
public:
	AnimationIKEffector();

	~AnimationIKEffector();

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

	XE::uint32 GetBoneJoint() const;

	void SetBoneJoint( XE::uint32 val );

private:
	bool _WeightNlerp;
	bool _InheritParentRotation;
	XE::Vec3 _TargetPosition;
	XE::Quat _TargetRotation;
	XE::uint32 _ChainLength;
	XE::float32 _Weight;
	XE::float32 _RotationWeight;
	XE::float32 _RotationDecay;
	XE::uint32 _BoneJoint;
};
DECL_META_CLASS( XE_API, AnimationIKEffector );

class XE_API AnimationIKConstraint
{
public:
	AnimationIKConstraint();

	~AnimationIKConstraint();

public:
	XE::float32 GetStiffness() const;

	void SetStiffness( XE::float32 val );

	XE::float32 GetStretchiness() const;

	void SetStretchiness( XE::float32 val );

	const XE::Vec2 & GetLengthConstraints() const;

	void SetLengthConstraints( const XE::Vec2 & val );

private:
	XE::float32 _Stiffness;
	XE::float32 _Stretchiness;
	XE::Vec2 _LengthConstraints;
};
DECL_META_CLASS( XE_API, AnimationIKConstraint );

class XE_API AnimationIKSolver : public XE::Object
{
	OBJECT( AnimationIKSolver, Object )

public:
	AnimationIKSolver();

	~AnimationIKSolver();

public:
	void Startup();

	void Update( XE::float32 val );

	void Clearup();

public:
	const SkeletonPtr & GetSkeleton() const;

	void SetSkeletion( const SkeletonPtr & val );

public:
	IKAlgorithm GetAlgorithm() const;

	void SetAlgorithm( IKAlgorithm val );

	bool GetJointRotations() const;

	void SetJointRotations( bool val );

	bool GetTargetRotations() const;

	void SetTargetRotations( bool val );

	bool GetUpdateOriginalPose() const;

	void SetUpdateOriginalPose( bool val );

	bool GetUpdateActivePose() const;

	void SetUpdateActivePose( bool val );

	bool GetUseOriginalPose() const;

	void SetUseOriginalPose( bool val );

	bool GetConstraints() const;

	void SetConstraints( bool val );

	bool GetAutoSolve() const;

	void SetAutoSolve( bool val );

	XE::float32 GetTolerance() const;

	void SetTolerance( XE::float32 val );

	XE::uint32 GetMaximumIterations() const;

	void SetMaximumIterations( XE::uint32 val );

	const Array<AnimationIKEffector> & GetIKEffectors() const;

	void SetIKRffectors( const Array<AnimationIKEffector> & val );

	const Array<AnimationIKConstraint> & GetIKConstraints() const;

	void SetIKConstraints( const Array<AnimationIKConstraint> & val );

private:
	AnimationIKSolverHandle _Handle;

	SkeletonPtr _Skeleton;

	Array<AnimationIKEffector> _EffectorList;
	Array<AnimationIKConstraint> _ConstraintList;

	IKAlgorithm _Algorithm;
	bool _Constraints;
	bool _JointRotations;
	bool _TargetRotations;
	XE::float32 _Tolerance;
	XE::uint32 _MaxIterations;

	bool _SolverTreeValid;
	bool _TreeNeedsRebuild;
	bool _ChainTreesNeedUpdating;

	bool _AutoSolve;
	bool _UseOriginalPose;
	bool _UpdateActivePose;
	bool _UpdateOriginalPose;
};

END_XE_NAMESPACE

#endif // ANIMATIONIKSOLVER_H__23350757_7A32_4A7D_A723_66A8ED64D4A8
