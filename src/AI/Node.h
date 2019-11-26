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

class XE_API Node : public XE::Object
{
	OBJECT( Node, Object )

public:
	Node();

	~Node();

public:
	NodeHandle GetHandle() const;

	void SetHandle( NodeHandle val );

	NodeHandle GetParent() const;

	void SetParent( NodeHandle val );

	const BehaviorTreePtr & GetBehaviorTree() const;

	void SetBehaviorTree( const BehaviorTreePtr & val );

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
	NodeHandle _Parent;
	NodeStatus _Status;
	ConditionPtr _PreCondition;
	ConditionStatus _ConditionStatus;

	BehaviorTreePtr _BehaviorTree;
};

END_XE_NAMESPACE

#endif // __NODE_H__4E15E329_D9A1_4F5D_B63A_CA4079844C18
