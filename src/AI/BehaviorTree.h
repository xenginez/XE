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

public:
	BehaviorTree();

	~BehaviorTree();

public:
	virtual void Startup() override;

	virtual void Update( XE::float32 dt ) override;

	virtual void Clearup() override;

public:
	Node * GetRoot() const;

	BlackBoard * GetBlackBoard() const;

	Node * GetNode( NodeHandle val ) const;

public:
	NodeHandle _Root;
	BlackBoardPtr _Blackboard;
	Array< NodePtr > _Nodes;
};

END_XE_NAMESPACE

#endif // __BEHAVIORTREE_H__26CB8C79_ABF7_4B28_ADE3_283D2FF378F8
