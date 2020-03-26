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
	NodeHandle GetRoot() const;

	void SetRoot( NodeHandle val );

	NodePtr GetNode( NodeHandle val ) const;

public:
	NodeHandle AddNode( const IMetaClassPtr & val );

	void RemoveNode( XE::NodeHandle val );

	void SwapNodeHandle( XE::NodeHandle node1, XE::NodeHandle node2 );

public:
	NodeHandle _Root;
	XE::uint64 _Handles;
	XE::Map< XE::NodeHandle,  NodePtr > _Nodes;
};

END_XE_NAMESPACE

#endif // __BEHAVIORTREE_H__26CB8C79_ABF7_4B28_ADE3_283D2FF378F8
