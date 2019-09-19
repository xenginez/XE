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

class ANIMATION_API AnimationIKSolver : public XE::Object
{
	OBJECT( AnimationIKSolver, Object )

public:
	AnimationIKSolver();

	~AnimationIKSolver();

public:
	IKSolverHandle GetHandle() const;

	void SetHandle( IKSolverHandle val );

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

	XE::uint32 GetMaximumIterations() const;

	void SetMaximumIterations( XE::uint32 val );

	XE::float32 GetTolerance() const;

	void SetTolerance( XE::float32 val );

public:
	void RebuildChainTrees();

	void RecalculateSegmentLengths();

	void CalculateJointRotations();

public:
	void Solve();

private:
	IKSolverHandle _Handle;

	Array<AnimationIKEffectorPtr> _EffectorList;
	Array<AnimationIKConstraintPtr> _ConstraintList;

	IKAlgorithm _Algorithm;

	bool _SolverTreeValid;
	bool _TreeNeedsRebuild;
	bool _ChainTreesNeedUpdating;

	bool _AutoSolve;
	bool _Constraints;
	bool _JointRotations;
	bool _UseOriginalPose;
	bool _TargetRotations;
	bool _UpdateActivePose;
	bool _UpdateOriginalPose;

	XE::uint32 _MaxIterations;
	XE::float32 _Tolerance;
};

END_XE_NAMESPACE

#endif // ANIMATIONIKSOLVER_H__23350757_7A32_4A7D_A723_66A8ED64D4A8
