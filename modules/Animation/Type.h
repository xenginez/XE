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

BEG_ANIMATION_NAMESPACE

DECL_PTR( Skeleton );
DECL_PTR( BlendingLayer );
DECL_PTR( State );
DECL_PTR( Layer );
DECL_PTR( SkeletonAnimation );
DECL_PTR( Condition );
DECL_PTR( Controller );

DECL_HANDLE( ANIMATION_API, Skeleton );
DECL_HANDLE( ANIMATION_API, State );
DECL_HANDLE( ANIMATION_API, SkeletonAnimation );

enum class BlendMode : XE::uint8
{
	ADDITIVE,
	OVERRIDE,
};
DECL_META_ENUM( ANIMATION_API, BlendMode );

enum class StateStatus : XE::uint8
{
	NONE,
	RUNNING,
	FAILED,
	SUCCESS,
};
DECL_META_ENUM( ANIMATION_API, StateStatus );

END_ANIMATION_NAMESPACE

#endif // __TYPE_H__E9FBF2A2_BC47_464B_AAAE_44C511E818E3
