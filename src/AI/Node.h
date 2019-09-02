/*!
 * \file   Node.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __NODE_H__4E15E329_D9A1_4F5D_B63A_CA4079844C18
#define __NODE_H__4E15E329_D9A1_4F5D_B63A_CA4079844C18

#include "Type.h"

BEG_XE_NAMESPACE

class AI_API Node : public XE::Object
{
	OBJECT( Node, Object )

public:
	Node();

	~Node();

public:
	NodeHandle GetHandle() const;

	BlackBoard * GetBlackBoard() const;

public:
	BehaviorTree * GetBehaviorTree() const;

	void SetBehaviorTree( BehaviorTree * val );

public:
	NodeStatus GetStatus() const;

	void SetStatus( NodeStatus val );

public:
	void Startup();

	void Update( XE::float32 dt );

	void Clearup();

protected:
	virtual void OnStartup();
				 
	virtual void OnUpdate( XE::float32 dt );
				 
	virtual void OnClearup();

private:
	NodeHandle _Handle;
	NodeStatus _Status;
	ConditionPtr _PreCondition;
	ConditionStatus _ConditionStatus;

	BehaviorTree * _BehaviorTree;
};

END_XE_NAMESPACE

#endif // __NODE_H__4E15E329_D9A1_4F5D_B63A_CA4079844C18
