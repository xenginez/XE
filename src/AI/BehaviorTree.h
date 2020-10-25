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
	void Startup() override;

	void Update( XE::float32 dt ) override;

	void Clearup() override;

	void AssetLoad() override;

public:
	AINodeHandle GetRoot() const;

	void SetRoot( AINodeHandle val );

	AINodePtr GetNode( AINodeHandle val ) const;

public:
	const XE::Array< XE::AINodePtr > & GetNodes() const;

	void SetNodes( const XE::Array< XE::AINodePtr > & val );

public:
	AINodeHandle _Root;
	XE::Array< XE::AINodePtr > _Nodes;
};

END_XE_NAMESPACE

#endif // __BEHAVIORTREE_H__26CB8C79_ABF7_4B28_ADE3_283D2FF378F8
