/*!
 * \file   BehaviorTree.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __BEHAVIORTREE_H__26CB8C79_ABF7_4B28_ADE3_283D2FF378F8
#define __BEHAVIORTREE_H__26CB8C79_ABF7_4B28_ADE3_283D2FF378F8

#include "Module.h"

BEG_AI_NAMESPACE

class CompositeNode;
class ConditionNode;

class AI_API BehaviorTree : public AI::Module
{
	OBJECT( BehaviorTree, Module )

	friend class CompositeNode;
	friend class ConditionNode;

public:
	BehaviorTree();

	~BehaviorTree();

public:
	void Startup() override;

	void Enter() override;

	void Update( XE::float32 dt ) override;

	void Quit() override;

	void Clearup() override;

	void AssetLoad() override;

	bool IsStopped() const override;

public:
	AI::NodePtr GetNode( AI::NodeHandle val ) const;

public:
	AI::NodeHandle GetRoot() const;

	void SetRoot( AI::NodeHandle val );

	const XE::Array< AI::NodePtr > & GetNodes() const;

	void SetNodes( const XE::Array< AI::NodePtr > & val );

private:
	void PushCompositeNode( AI::CompositeNode * val );

	void PushConditionNode( AI::ConditionNode * val );

public:
	AI::NodeHandle _Root;
	XE::Array< AI::NodePtr > _Nodes;

	XE::Deque< AI::Node * > _RunningNodes;
	XE::Deque< AI::NodeHandle > _CompositeNodes;
};

END_AI_NAMESPACE

#endif // __BEHAVIORTREE_H__26CB8C79_ABF7_4B28_ADE3_283D2FF378F8
