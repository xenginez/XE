#include "AnimationIKSolver.h"

#include <ik/effector.h>
#include <ik/node.h>
#include <ik/solver.h>
#include <ik/util.h>

USING_XE

BEG_META( AnimationIKSolver )
type->Property( "EffectorList", &AnimationIKSolver::_EffectorList );
type->Property( "ConstraintList", &AnimationIKSolver::_ConstraintList );
type->Property( "SolverTreeValid", &AnimationIKSolver::_SolverTreeValid );
type->Property( "TreeNeedsRebuild", &AnimationIKSolver::_TreeNeedsRebuild );
type->Property( "ChainTreesNeedUpdating", &AnimationIKSolver::_ChainTreesNeedUpdating );
type->Property( "AutoSolve", &AnimationIKSolver::_AutoSolve );
type->Property( "Constraints", &AnimationIKSolver::_Constraints );
type->Property( "JointRotations", &AnimationIKSolver::_JointRotations );
type->Property( "UseOriginalPose", &AnimationIKSolver::_UseOriginalPose );
type->Property( "TargetRotations", &AnimationIKSolver::_TargetRotations );
type->Property( "UpdateActivePose", &AnimationIKSolver::_UpdateActivePose );
type->Property( "UpdateOriginalPose", &AnimationIKSolver::_UpdateOriginalPose );
type->Property( "MaxIterations", &AnimationIKSolver::_MaxIterations );
type->Property( "Tolerance", &AnimationIKSolver::_Tolerance );
END_META()

XE::AnimationIKSolver::AnimationIKSolver()
	:_Algorithm( IKAlgorithm::ONE_BONE ),
	_SolverTreeValid( false ), _TreeNeedsRebuild( false ), _ChainTreesNeedUpdating( false ),
	_AutoSolve( false ), _Constraints( false ), _JointRotations( false ), _UseOriginalPose( false ),
	_TargetRotations( false ), _UpdateActivePose( false ), _UpdateOriginalPose( false ),
	_MaxIterations( 0 ), _Tolerance( 0.0f )
{

}

XE::AnimationIKSolver::~AnimationIKSolver()
{

}

XE::IKSolverHandle AnimationIKSolver::GetHandle() const
{
	return _Handle;
}

void AnimationIKSolver::SetHandle( XE::IKSolverHandle val )
{
	_Handle = val;
}

XE::IKAlgorithm XE::AnimationIKSolver::GetAlgorithm() const
{
	return _Algorithm;
}

void XE::AnimationIKSolver::SetAlgorithm( XE::IKAlgorithm val )
{
	_Algorithm = val;
}

bool XE::AnimationIKSolver::GetJointRotations() const
{
	return _JointRotations;
}

void XE::AnimationIKSolver::SetJointRotations( bool val )
{
	_JointRotations = val;
}

bool XE::AnimationIKSolver::GetTargetRotations() const
{
	return _TargetRotations;
}

void XE::AnimationIKSolver::SetTargetRotations( bool val )
{
	_TargetRotations = val;
}

bool XE::AnimationIKSolver::GetUpdateOriginalPose() const
{
	return _UpdateOriginalPose;
}

void XE::AnimationIKSolver::SetUpdateOriginalPose( bool val )
{
	_UpdateOriginalPose = val;
}

bool XE::AnimationIKSolver::GetUpdateActivePose() const
{
	return _UpdateActivePose;
}

void XE::AnimationIKSolver::SetUpdateActivePose( bool val )
{
	_UpdateActivePose = val;
}

bool XE::AnimationIKSolver::GetUseOriginalPose() const
{
	return _UseOriginalPose;
}

void XE::AnimationIKSolver::SetUseOriginalPose( bool val )
{
	_UseOriginalPose = val;
}

bool XE::AnimationIKSolver::GetConstraints() const
{
	return _Constraints;
}

void XE::AnimationIKSolver::SetConstraints( bool val )
{
	_Constraints = val;
}

bool XE::AnimationIKSolver::GetAutoSolve() const
{
	return _AutoSolve;
}

void XE::AnimationIKSolver::SetAutoSolve( bool val )
{
	_AutoSolve = val;
}

XE::uint32 XE::AnimationIKSolver::GetMaximumIterations() const
{
	return _MaxIterations;
}

void XE::AnimationIKSolver::SetMaximumIterations( XE::uint32 val )
{
	_MaxIterations = val;
}

XE::float32 XE::AnimationIKSolver::GetTolerance() const
{
	return _Tolerance;
}

void XE::AnimationIKSolver::SetTolerance( XE::float32 val )
{
	_Tolerance = val;
}

void XE::AnimationIKSolver::RebuildChainTrees()
{

}

void XE::AnimationIKSolver::RecalculateSegmentLengths()
{

}

void XE::AnimationIKSolver::CalculateJointRotations()
{

}

void XE::AnimationIKSolver::Solve()
{

}
