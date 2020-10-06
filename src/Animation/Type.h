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

#include "Reflect/Reflect.h"
#include "Utils/Handle.hpp"

BEG_XE_NAMESPACE

DECL_PTR( Animator );
DECL_PTR( AnimationState );
DECL_PTR( AnimationTrigger );
DECL_PTR( SkeletonAnimation );
DECL_PTR( AnimationIKSolver );
DECL_PTR( AnimationCondition );
DECL_PTR( AnimationTransition );
DECL_PTR( AnimationController );

DECL_HANDLE( XE_API, AnimationIKSolver );

enum class AnimationCompare
{
	EQUAL,
	LESS,
	GREA,
	LEQUAL,
	GEQUAL,
	NOTEQUAL,
};
DECL_META_ENUM( XE_API, AnimationCompare );


enum class IKAlgorithm
{
	ONE_BONE,
	TWO_BONE,
	FABRIK,
	MSS,
};
DECL_META_ENUM( XE_API, IKAlgorithm );

END_XE_NAMESPACE

#endif // __TYPE_H__E9FBF2A2_BC47_464B_AAAE_44C511E818E3
