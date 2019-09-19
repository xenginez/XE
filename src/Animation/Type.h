/*!
 * \file   Type.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TYPE_H__E9FBF2A2_BC47_464B_AAAE_44C511E818E3
#define __TYPE_H__E9FBF2A2_BC47_464B_AAAE_44C511E818E3

#include "Global.h"

BEG_XE_NAMESPACE

DECL_PTR( Animator );
DECL_PTR( AnimationState );
DECL_PTR( AnimationTrigger );
DECL_PTR( SkeletonAnimation );
DECL_PTR( AnimationIKSolver );
DECL_PTR( AnimationCondition );
DECL_PTR( AnimationIKEffector );
DECL_PTR( AnimationTransition );
DECL_PTR( AnimationController );
DECL_PTR( AnimationIKConstraint );

DECL_HANDLE( ANIMATION_API, IKSolver );
DECL_HANDLE( ANIMATION_API, IKEffector );
DECL_HANDLE( ANIMATION_API, IKConstraint );

enum class AnimationCompare
{
	EQUAL,
	LESS,
	GREA,
	LEQUAL,
	GEQUAL,
	NOTEQUAL,
};
DECL_META_ENUM( ANIMATION_API, AnimationCompare );


enum class IKAlgorithm
{
	ONE_BONE,
	TWO_BONE,
	FABRIK,
	MSD,
	JACOBIAN_INVERSE,
	JACOBIAN_TRANSPOSE,
};
DECL_META_ENUM( ANIMATION_API, IKAlgorithm );

END_XE_NAMESPACE

#endif // __TYPE_H__E9FBF2A2_BC47_464B_AAAE_44C511E818E3
