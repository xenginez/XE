#include "AnimationIKSolver.h"

#include <ik/ik.h>

USING_XE

BEG_META( AnimationIKEffector )
type->Property( "WeightNlerp", &AnimationIKEffector::GetWeightNlerp, &AnimationIKEffector::SetWeightNlerp );
type->Property( "InheritParentRotation", &AnimationIKEffector::GetInheritParentRotation, &AnimationIKEffector::SetInheritParentRotation );
type->Property( "ChainLength", &AnimationIKEffector::GetChainLength, &AnimationIKEffector::SetChainLength );
type->Property( "Weight", &AnimationIKEffector::GetWeight, &AnimationIKEffector::SetWeight );
type->Property( "RotationWeight", &AnimationIKEffector::GetRotationWeight, &AnimationIKEffector::SetRotationWeight );
type->Property( "RotationDecay", &AnimationIKEffector::GetRotationDecay, &AnimationIKEffector::SetRotationDecay );
type->Property( "BoneJoint", &AnimationIKEffector::GetBoneJoint, &AnimationIKEffector::SetBoneJoint );
END_META()

XE::AnimationIKEffector::AnimationIKEffector()
	:_WeightNlerp( false ), _InheritParentRotation( false ), _ChainLength( 0 ), _Weight( 0.0f ), _RotationWeight( 0.0f ), _RotationDecay( 0.0f )
{

}

XE::AnimationIKEffector::~AnimationIKEffector()
{

}

bool AnimationIKEffector::GetWeightNlerp() const
{
	return _WeightNlerp;
}

void AnimationIKEffector::SetWeightNlerp( bool val )
{
	_WeightNlerp = val;
}

bool AnimationIKEffector::GetInheritParentRotation() const
{
	return _InheritParentRotation;
}

void AnimationIKEffector::SetInheritParentRotation( bool val )
{
	_InheritParentRotation = val;
}

const XE::Vec3 & AnimationIKEffector::GetTargetPosition() const
{
	return _TargetPosition;
}

void AnimationIKEffector::SetTargetPosition( const XE::Vec3 & val )
{
	_TargetPosition = val;
}

const XE::Quat & AnimationIKEffector::GetTargetRotation() const
{
	return _TargetRotation;
}

void AnimationIKEffector::SetTargetRotation( const XE::Quat & val )
{
	_TargetRotation = val;
}

XE::uint32 AnimationIKEffector::GetChainLength() const
{
	return _ChainLength;
}

void AnimationIKEffector::SetChainLength( XE::uint32 val )
{
	_ChainLength = val;
}

XE::float32 AnimationIKEffector::GetWeight() const
{
	return _Weight;
}

void AnimationIKEffector::SetWeight( XE::float32 val )
{
	_Weight = val;
}

XE::float32 AnimationIKEffector::GetRotationWeight() const
{
	return _RotationWeight;
}

void AnimationIKEffector::SetRotationWeight( XE::float32 val )
{
	_RotationWeight = val;
}

XE::float32 AnimationIKEffector::GetRotationDecay() const
{
	return _RotationDecay;
}

void AnimationIKEffector::SetRotationDecay( XE::float32 val )
{
	_RotationDecay = val;
}

XE::uint32 AnimationIKEffector::GetBoneJoint() const
{
	return _BoneJoint;
}

void AnimationIKEffector::SetBoneJoint( XE::uint32 val )
{
	_BoneJoint = val;
}

BEG_META( AnimationIKConstraint )
type->Property( "Stiffness", &AnimationIKConstraint::GetStiffness, &AnimationIKConstraint::SetStiffness );
type->Property( "Stretchiness", &AnimationIKConstraint::GetStretchiness, &AnimationIKConstraint::SetStretchiness );
type->Property( "LengthConstraints", &AnimationIKConstraint::GetLengthConstraints, &AnimationIKConstraint::SetLengthConstraints );
END_META()

XE::AnimationIKConstraint::AnimationIKConstraint()
	:_Stiffness( 0.0f ), _Stretchiness( 0.0f )
{

}

XE::AnimationIKConstraint::~AnimationIKConstraint()
{

}

XE::float32 AnimationIKConstraint::GetStiffness() const
{
	return _Stiffness;
}

void AnimationIKConstraint::SetStiffness( XE::float32 val )
{
	_Stiffness = Mathf::Clamp( val, 0.0f, 1.0f );
}

XE::float32 AnimationIKConstraint::GetStretchiness() const
{
	return _Stretchiness;
}

void AnimationIKConstraint::SetStretchiness( XE::float32 val )
{
	_Stretchiness = val;
}

const XE::Vec2 & AnimationIKConstraint::GetLengthConstraints() const
{
	return _LengthConstraints;
}

void AnimationIKConstraint::SetLengthConstraints( const XE::Vec2 & val )
{
	_LengthConstraints = val;
}


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

void CreateNodes( ik_node_t * parent, SkeletonPtr skeleton, ik_solver_t * solver )
{
	const auto & children = skeleton->GetBoneJointChildren( parent->guid );
	for( auto child : children )
	{
		struct ik_node_t * node = solver->node->create( child );
		Vec3 position; Quat rotation; Vec3 scale;
		Mathf::TRS( skeleton->GetBoneJointTransform( child ), position, rotation, scale );
		node->position = ik.vec3.vec3( position.x, position.y, position.z );
		node->rotation = ik.quat.quat( rotation.x, rotation.y, rotation.z, rotation.w );
		solver->node->add_child( parent, node );
		CreateNodes( node, skeleton, solver );
	}
};

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

void AnimationIKSolver::Startup()
{
	ik_solver_t * solver = nullptr;

	switch( _Algorithm )
	{
	case XE::IKAlgorithm::ONE_BONE:
		solver = ik.solver.create( ik_algorithm_e::IK_ONE_BONE );
		break;
	case XE::IKAlgorithm::TWO_BONE:
		solver = ik.solver.create( ik_algorithm_e::IK_TWO_BONE );
		break;
	case XE::IKAlgorithm::FABRIK:
		solver = ik.solver.create( ik_algorithm_e::IK_FABRIK );
		break;
	case XE::IKAlgorithm::MSS:
		solver = ik.solver.create( ik_algorithm_e::IK_MSS );
		break;
	}

	solver->max_iterations = GetMaximumIterations();
	solver->tolerance = GetTolerance();

	if (_Constraints)
	{
		solver->flags |= ik_flags_e::IK_ENABLE_CONSTRAINTS;
	}
	if (_TargetRotations)
	{
		solver->flags |= ik_flags_e::IK_ENABLE_TARGET_ROTATIONS;
	}
	if (_JointRotations)
	{
		solver->flags |= ik_flags_e::IK_ENABLE_JOINT_ROTATIONS;
	}

	ik_node_t * root = solver->node->create( 0 );
	Vec3 position; Quat rotation; Vec3 scale;
	Mathf::TRS( _Skeleton->GetBoneJointTransform( 0 ), position, rotation, scale );
	root->position = ik.vec3.vec3( position.x, position.y, position.z );
	root->rotation = ik.quat.quat( rotation.x, rotation.y, rotation.z, rotation.w );
	CreateNodes( root, _Skeleton, solver );

	for( const auto & eff : _EffectorList )
	{
		ik_effector_t * effector = solver->effector->create();
		solver->effector->attach( effector, solver->node->find_child( root, eff.GetBoneJoint() ) );
	}

	ik.solver.rebuild( solver );

	_Handle = ( XE::uint64 )( solver );
}

void AnimationIKSolver::Update( XE::float32 val )
{

}

void AnimationIKSolver::Clearup()
{
	ik.solver.destroy( (ik_solver_t * )_Handle.GetValue() );
	_Handle = AnimationIKSolverHandle::Invalid;
}

const SkeletonPtr & AnimationIKSolver::GetSkeleton() const
{
	return _Skeleton;
}

void AnimationIKSolver::SetSkeletion( const SkeletonPtr & val )
{
	_Skeleton = val;
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

const Array<AnimationIKEffector> & AnimationIKSolver::GetIKEffectors() const
{
	return _EffectorList;
}

void AnimationIKSolver::SetIKRffectors( const Array<AnimationIKEffector> & val )
{
	_EffectorList = val;
}

const Array<AnimationIKConstraint> & AnimationIKSolver::GetIKConstraints() const
{
	return _ConstraintList;
}

void AnimationIKSolver::SetIKConstraints( const Array<AnimationIKConstraint> & val )
{
	_ConstraintList = val;
}

void XE::AnimationIKSolver::SetTolerance( XE::float32 val )
{
	_Tolerance = val;
}
