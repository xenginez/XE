/*!
 * \file   Type.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TYPE_H__73959EA8_D866_4007_8631_FA5571A35593
#define __TYPE_H__73959EA8_D866_4007_8631_FA5571A35593

#include "Utils/Handle.hpp"

BEG_XE_NAMESPACE

DECL_PTR( AINode );
DECL_PTR( AIState );
DECL_PTR( AIModule );
DECL_PTR( BehaviorTree );
DECL_PTR( StateMachine );

DECL_HANDLE( XE_API, AINode );
DECL_HANDLE( XE_API, AIState );

enum class NodeStatus
{
	NONE,
	RUNNING,
	SUCCESS,
	FAILURE,
};
DECL_META_ENUM( XE_API, NodeStatus );

enum class ConditionStatus
{
	ONCE,
	ALWAYS,
};
DECL_META_ENUM( XE_API, ConditionStatus );

END_XE_NAMESPACE

#endif // __TYPE_H__73959EA8_D866_4007_8631_FA5571A35593
