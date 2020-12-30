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

#include <random>

#include "BlackboardKey.h"

BEG_AI_NAMESPACE

class AI_API Node : public XE::Object
{
	OBJECT( Node, Object )

private:
	friend class BehaviorTree;

public:
	Node();

	~Node();

public:
	AI::AINodeType GetType() const;

	AINodeStatus GetStatus() const;

	void SetStatus( AINodeStatus val );

	AI::NodeHandle GetHandle() const;

	void SetHandle( AI::NodeHandle val );

	AI::NodeHandle GetParent() const;

	void SetParent( AI::NodeHandle val );

	const XE::String & GetName() const;

	void SetName( const XE::String & val );

	BehaviorTreePtr GetBehaviorTree() const;

protected:
	void SetType( AI::AINodeType val );

private:
	void SetBehaviorTree( BehaviorTreePtr val );

public:
	virtual void Startup();

	virtual void Enter();

	virtual void Update( XE::float32 dt );

	virtual void Quit();

	virtual void Clearup();

protected:
	virtual void OnStartup();
				 
	virtual void OnEnter();

	virtual void OnUpdate( XE::float32 dt );
				 
	virtual void OnQuit();

	virtual void OnClearup();

private:
	XE::String _Name;
	AI::AINodeType _Type;
	AINodeStatus _Status;
	AI::NodeHandle _Handle;
	AI::NodeHandle _Parent;

	BehaviorTreeWPtr _BehaviorTree;
};

class AI_API SubNode : public AI::Node
{
	OBJECT( SubNode, Node )

public:
	SubNode();

	~SubNode();

public:
	const XE::Map<AI::BlackboardKey, AI::BlackboardKey> & GetConnectKeys() const;

	void SetConnectKeys( const XE::Map<AI::BlackboardKey, AI::BlackboardKey> & val );

protected:
	void OnStartup() override;

	void OnEnter() override;

	void OnUpdate( XE::float32 dt ) override;

	void OnQuit() override;

	void OnClearup() override;

private:
	XE::AssetInstance< AI::Module > _AIModule;
	XE::Map<AI::BlackboardKey, AI::BlackboardKey> _ConnectKeys;
};

class AI_API ActionNode : public Node
{
	OBJECT( ActionNode, Node )

public:
	ActionNode();

	~ActionNode();

};

class AI_API CompositeNode : public Node
{
	OBJECT( CompositeNode, Node )

public:
	CompositeNode();

	~CompositeNode();

protected:
	void OnEnter() override;

	void OnQuit() override;

public:
	const XE::Array<AI::NodeHandle> & GetChildren() const;

	void SetChildren( const XE::Array<AI::NodeHandle> & val );

private:
	XE::Array<AI::NodeHandle> _Children;
};

class AI_API SequenceNode : public CompositeNode
{
	OBJECT( SequenceNode, CompositeNode )

public:
	SequenceNode();

	~SequenceNode();

protected:
	void OnEnter() override;

	void OnUpdate( XE::float32 dt ) override;

private:
	XE::uint64 _Current;
};

class AI_API SelectorNode : public CompositeNode
{
	OBJECT( SelectorNode, CompositeNode )

public:
	SelectorNode();

	~SelectorNode();

protected:
	void OnEnter() override;

	void OnUpdate( XE::float32 dt ) override;

private:
	XE::uint64 _Current;
};

class AI_API RandomSelectorNode : public CompositeNode
{
	OBJECT( RandomSelectorNode, CompositeNode )

public:
	RandomSelectorNode();

	~RandomSelectorNode();

protected:
	void OnEnter() override;

	void OnUpdate( XE::float32 dt ) override;

private:
	XE::uint64 _Seed;
	XE::uint64 _Current;
	std::default_random_engine _Random;
	std::uniform_int_distribution<XE::uint64> _Uniform;
};

class AI_API ParallelSequenceNode : public CompositeNode
{
	OBJECT( ParallelSequenceNode, CompositeNode )

public:
	ParallelSequenceNode();

	~ParallelSequenceNode();

protected:
	void OnUpdate( XE::float32 dt ) override;

};

class AI_API ParallelSelectorNode : public CompositeNode
{
	OBJECT( ParallelSelectorNode, CompositeNode )

public:
	ParallelSelectorNode();

	~ParallelSelectorNode();

protected:
	void OnUpdate( XE::float32 dt ) override;

};

class AI_API ConditionNode : public AI::Node
{
	OBJECT( ConditionNode, Node )

public:
	ConditionNode();

	~ConditionNode();

public:
	AI::NodeHandle GetChild() const;

	void SetChild( AI::NodeHandle val );

public:
	void OnEnter() override;

	void OnUpdate( XE::float32 dt ) override;

	void OnQuit() override;

public:
	virtual bool Judgment() const = 0;

public:
	bool JudgmentChanged() const;

private:
	bool _CurJudgment;
	AI::NodeHandle _Child;
};

class AI_API DecoratorNode : public Node
{
	OBJECT( DecoratorNode, Node )

public:
	DecoratorNode();

	~DecoratorNode();

public:
	AI::NodeHandle GetChild() const;

	void SetChild( AI::NodeHandle val );

public:
	void OnEnter() override;

	void OnUpdate( XE::float32 dt ) override;

	void OnQuit() override;

private:
	AI::NodeHandle _Child;
};

class AI_API RepeatNode : public DecoratorNode
{
	OBJECT( RepeatNode, DecoratorNode )

public:
	RepeatNode();

	~RepeatNode();

public:
	void OnEnter() override;

	void OnUpdate( XE::float32 dt ) override;

private:
	XE::uint64 _Count;
	XE::uint64 _Tally;
};

class AI_API SuccessNode : public DecoratorNode
{
	OBJECT( SuccessNode, DecoratorNode )

public:
	SuccessNode();

	~SuccessNode();

public:
	void OnEnter() override;

	void OnUpdate( XE::float32 dt ) override;

};

class AI_API FailureNode : public DecoratorNode
{
	OBJECT( FailureNode, DecoratorNode )

public:
	FailureNode();

	~FailureNode();

public:
	void OnEnter() override;

	void OnUpdate( XE::float32 dt ) override;

};

class AI_API ReversedNode : public DecoratorNode
{
	OBJECT( ReversedNode, DecoratorNode )

public:
	ReversedNode();

	~ReversedNode();

public:
	void OnEnter() override;

	void OnUpdate( XE::float32 dt ) override;

};

class AI_API DelayNode : public DecoratorNode
{
	OBJECT( DelayNode, DecoratorNode )

public:
	DelayNode();

	~DelayNode();

public:
	void OnEnter() override;

	void OnUpdate( XE::float32 dt ) override;

private:
	XE::float32 _DetlaTime;
	XE::float32 _Dt;
};

END_AI_NAMESPACE

#endif // __NODE_H__4E15E329_D9A1_4F5D_B63A_CA4079844C18
