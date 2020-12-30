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

BEG_AI_NAMESPACE

DECL_PTR( Node );
DECL_PTR( State );
DECL_PTR( Module );
DECL_PTR( Element );
DECL_PTR( Blueprint );
DECL_PTR( InputPort );
DECL_PTR( OutputPort );
DECL_PTR( BehaviorTree );
DECL_PTR( StateMachine );

DECL_HANDLE( AI_API, Node );
DECL_HANDLE( AI_API, State );
DECL_HANDLE( AI_API, Element );

enum class AINodeType
{
	SUB_NODE,
	ACTION_NODE,
	COMPOSITE_NODE,
	CONDITION_NODE,
	DECORATOR_NODE,
};
DECL_META_ENUM( AI_API, AINodeType );

enum class AINodeStatus
{
	NONE,
	RUNNING,
	SUCCESS,
	FAILURE,
};
DECL_META_ENUM( AI_API, AINodeStatus );

enum class AIElementType
{
	DATA_ELEMENET,
	CALC_ELEMENET,
	EVENT_ELEMENET,
	LOGIC_ELEMENET,
	ACTION_ELEMENET,
	VARIABLE_ELEMENET,
};
DECL_META_ENUM( AI_API, AIElementType );

DECL_EVENT( START, "blueprint event element start event", void );
DECL_EVENT( ENTER, "blueprint event element enter event", void );
DECL_EVENT( UPDATE, "blueprint event element update event", XE::float32 );
DECL_EVENT( QUIT, "blueprint event element quit event", void );
DECL_EVENT( CLEAR, "blueprint event element clear event", void );

DECL_META_MODULE( AI_API );

END_AI_NAMESPACE

#endif // __TYPE_H__73959EA8_D866_4007_8631_FA5571A35593
