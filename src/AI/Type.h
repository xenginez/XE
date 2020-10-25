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


DECL_PTR( Node );
DECL_PTR( State );
DECL_PTR( AIModule );
DECL_PTR( Condition );
DECL_PTR( BlackBoard );
DECL_PTR( BehaviorTree );
DECL_PTR( StateMachine );

DECL_PTR( GameObject );

DECL_HANDLE( XE_API, Node );
DECL_HANDLE( XE_API, State );

class BlackboardKey;
template<typename T> class BlackboardKeyKeyT;


enum class NodeStatus
{
	None,
	Running,
	Success,
	Failure,
	Finish,
};
DECL_META_ENUM( XE_API, NodeStatus );

enum class ConditionStatus
{
	Once,
	Always,
};
DECL_META_ENUM( XE_API, ConditionStatus );

END_XE_NAMESPACE

#endif // __TYPE_H__73959EA8_D866_4007_8631_FA5571A35593
