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

#include "Global.h"

BEG_XE_NAMESPACE

DECL_PTR( AIModule );

DECL_PTR( Node );
DECL_PTR( BlackBoard );
DECL_PTR( BehaviorTree );

DECL_PTR( State );
DECL_PTR( Condition );
DECL_PTR( StateMachine );



enum class NodeStatus
{
	None,
	Running,
	Success,
	Failure,
	Finish,
};
DECL_META_ENUM( AI_API, NodeStatus );

enum class ConditionStatus
{
	Once,
	Always,
};
DECL_META_ENUM( AI_API, ConditionStatus );


DECL_HANDLE( AI_API, Node );
DECL_HANDLE( AI_API, State );

END_XE_NAMESAPCE

#endif // __TYPE_H__73959EA8_D866_4007_8631_FA5571A35593
