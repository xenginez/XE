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

#include "AIModule.h"

BEG_XE_NAMESPACE

class CompositeNode;
class ConditionNode;

class XE_API BehaviorTree : public XE::AIModule
{
	OBJECT( BehaviorTree, AIModule )

	friend class CompositeNode;
	friend class ConditionNode;

private:
	struct PrivateNode
	{
		bool IsCondition = false;
		XE::AINode * Node = nullptr;
	};

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
	XE::AINodePtr GetNode( XE::AINodeHandle val ) const;

public:
	XE::AINodeHandle GetRoot() const;

	void SetRoot( XE::AINodeHandle val );

	const XE::Array< XE::AINodePtr > & GetNodes() const;

	void SetNodes( const XE::Array< XE::AINodePtr > & val );

private:
	void PushCompositeNode( XE::CompositeNode * val );

	void PushConditionNode( XE::ConditionNode * val );

public:
	XE::AINodeHandle _Root;
	XE::Array< XE::AINodePtr > _Nodes;

	XE::Deque< XE::AINode * > _RunningNodes;
	XE::Deque< XE::AINodeHandle > _CompositeNodes;
};

END_XE_NAMESPACE

#endif // __BEHAVIORTREE_H__26CB8C79_ABF7_4B28_ADE3_283D2FF378F8
