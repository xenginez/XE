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

class XE_API BehaviorTree : public XE::AIModule
{
	OBJECT( BehaviorTree, AIModule )

	struct PrivateNode;
	friend class CompositeNode;
	friend class ConditionNode;

public:
	BehaviorTree();

	~BehaviorTree();

public:
	void Startup() override;

	void Update( XE::float32 dt ) override;

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
	XE::NodeStatus _Status;
	XE::Array< XE::AINodePtr > _Nodes;
	XE::Deque< PrivateNode > _PrivateNodes;
};

END_XE_NAMESPACE

#endif // __BEHAVIORTREE_H__26CB8C79_ABF7_4B28_ADE3_283D2FF378F8
