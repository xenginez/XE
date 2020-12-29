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

#include "Math/Mat4.h"
#include "Utils/Event.h"
#include "Utils/Handle.hpp"
#include "Reflect/Reflect.h"

BEG_XE_NAMESPACE

DECL_PTR( Skeleton );
DECL_PTR( BlendingLayer );
DECL_PTR( AnimationState );
DECL_PTR( AnimationLayer );
DECL_PTR( SkeletonAnimation );
DECL_PTR( AnimationCondition );
DECL_PTR( AnimationController );

DECL_HANDLE( XE_API, Skeleton );
DECL_HANDLE( XE_API, AnimationState );
DECL_HANDLE( XE_API, SkeletonAnimation );

enum class AnimationBlendMode : XE::uint8
{
	ADDITIVE,
	OVERRIDE,
};
DECL_META_ENUM( XE_API, AnimationBlendMode );

enum class AnimationStateStatus : XE::uint8
{
	NONE,
	RUNNING,
	FAILED,
	SUCCESS,
};
DECL_META_ENUM( XE_API, AnimationStateStatus );

END_XE_NAMESPACE

#endif // __TYPE_H__E9FBF2A2_BC47_464B_AAAE_44C511E818E3
