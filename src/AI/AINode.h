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

#include "BlackboardKey.h"

BEG_XE_NAMESPACE

class XE_API AINode : public XE::Object
{
	OBJECT( AINode, Object )

private:
	friend class BehaviorTree;

public:
	AINode();

	~AINode();

public:
	NodeStatus GetStatus() const;

	void SetStatus( NodeStatus val );

	AINodeHandle GetHandle() const;

	void SetHandle( AINodeHandle val );

	AINodeHandle GetParent() const;

	void SetParent( AINodeHandle val );

	const XE::String & GetName() const;

	void SetName( const XE::String & val );

public:
	BehaviorTreePtr GetBehaviorTree() const;

private:
	void SetBehaviorTree( BehaviorTreePtr val );

public:
	virtual void Startup();

	virtual void Update( XE::float32 dt );

	virtual void Clearup();

protected:
	virtual void OnStartup();
				 
	virtual void OnUpdate( XE::float32 dt );
				 
	virtual void OnClearup();

private:
	XE::String _Name;
	NodeStatus _Status;
	AINodeHandle _Handle;
	AINodeHandle _Parent;

	BehaviorTreeWPtr _BehaviorTree;
};

class XE_API SubNode : public XE::AINode
{
	OBJECT( SubNode, AINode )

public:
	SubNode();

	~SubNode();

public:
	const XE::Map<XE::BlackboardKey, XE::BlackboardKey> & GetConnectKeys() const;

	void SetConnectKeys( const XE::Map<XE::BlackboardKey, XE::BlackboardKey> & val );

protected:
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::float32 dt ) override;

	virtual void OnClearup() override;

private:
	XE::AIModulePtr _SubAI;
	XE::FileSystem::Path _SubAIPath;
	XE::Map<XE::BlackboardKey, XE::BlackboardKey> _ConnectKeys;
};

class XE_API ActionNode : public AINode
{
	OBJECT( ActionNode, AINode )

public:
	ActionNode();

	~ActionNode();

};

class XE_API CompositeNode : public AINode
{
	OBJECT( CompositeNode, AINode )

public:
	CompositeNode();

	~CompositeNode();

public:
	const XE::Array<XE::AINodeHandle> & GetChildren() const;

	void SetChildren( const XE::Array<XE::AINodeHandle> & val );

protected:
	void OnStartup() override;

	void OnClearup() override;

private:
	XE::Array<XE::AINodeHandle> _Children;
};

class XE_API SequenceNode : public CompositeNode
{
	OBJECT( SequenceNode, CompositeNode )

public:
	SequenceNode();

	~SequenceNode();

protected:
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::float32 dt ) override;

private:
	XE::uint64 _Current;
};

class XE_API SelectorNode : public CompositeNode
{
	OBJECT( SelectorNode, CompositeNode )

public:
	SelectorNode();

	~SelectorNode();

protected:
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::float32 dt ) override;

private:
	XE::uint64 _Current;
};

class XE_API ParallelNode : public CompositeNode
{
	OBJECT( ParallelNode, CompositeNode )

public:
	ParallelNode();

	~ParallelNode();

protected:
	virtual void OnUpdate( XE::float32 dt ) override;

};

class XE_API ConditionNode : public XE::AINode
{
	OBJECT( ConditionNode, AINode )

public:
	ConditionNode();

	~ConditionNode();

public:
	XE::AINodeHandle GetChild() const;

	void SetChild( XE::AINodeHandle val );

public:
	void OnStartup() override;

	void OnUpdate( XE::float32 dt ) override;

	void OnClearup() override;

public:
	virtual bool ConditionalJudgment() const = 0;

private:
	bool _MultiJudgment;
	XE::AINodeHandle _Child;
};

class XE_API DecoratorNode : public AINode
{
	OBJECT( DecoratorNode, AINode )

public:
	DecoratorNode();

	~DecoratorNode();

public:
	XE::AINodeHandle GetChild() const;

	void SetChild( XE::AINodeHandle val );

public:
	void OnStartup() override;

	void OnUpdate( XE::float32 dt ) override;

	void OnClearup() override;

private:
	AINodeHandle _Child;
};

class XE_API RepeatNode : public DecoratorNode
{
	OBJECT( RepeatNode, DecoratorNode )

public:
	RepeatNode();

	~RepeatNode();

public:
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::float32 dt ) override;

private:
	XE::int64 _Count;
	XE::int64 _Tally;
};

class XE_API SuccessNode : public DecoratorNode
{
	OBJECT( SuccessNode, DecoratorNode )

public:
	SuccessNode();

	~SuccessNode();

public:
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::float32 dt ) override;

};

class XE_API FailureNode : public DecoratorNode
{
	OBJECT( FailureNode, DecoratorNode )

public:
	FailureNode();

	~FailureNode();

public:
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::float32 dt ) override;

};

class XE_API ReversedNode : public DecoratorNode
{
	OBJECT( ReversedNode, DecoratorNode )

public:
	ReversedNode();

	~ReversedNode();

public:
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::float32 dt ) override;

};

class XE_API DelayNode : public DecoratorNode
{
	OBJECT( DelayNode, DecoratorNode )

public:
	DelayNode();

	~DelayNode();

public:
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::float32 dt ) override;

private:
	XE::float32 _DetlaTime;
	XE::float32 _Dt;
};

END_XE_NAMESPACE

#endif // __NODE_H__4E15E329_D9A1_4F5D_B63A_CA4079844C18
