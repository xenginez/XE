/*!
 * \file   CompositeNode.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __BTCOMPOSITENODE_H__70BFB67B_E6B3_45A9_B9E1_A31B99D95716
#define __BTCOMPOSITENODE_H__70BFB67B_E6B3_45A9_B9E1_A31B99D95716

#include "Node.h"

BEG_XE_NAMESPACE

class AI_API BTCompositeNode : public Node
{
	OBJECT( BTCompositeNode, Node )

public:
	BTCompositeNode();

	~BTCompositeNode();

public:
	const Array<Node *> GetChildren() const;

protected:
	virtual void OnStartup() override;

	virtual void OnClearup() override;

private:
	Array<NodeHandle> _Children;
	Array<Node *> _Nodes;
};

class AI_API BTSequenceNode : public BTCompositeNode
{
	OBJECT( BTSequenceNode, BTCompositeNode )

public:
	BTSequenceNode();

	~BTSequenceNode();

protected:
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::real dt ) override;

private:
	XE::uint64 _Current;
};

class AI_API BTSelectorNode : public BTCompositeNode
{
	OBJECT( BTSelectorNode, BTCompositeNode )

public:
	BTSelectorNode();

	~BTSelectorNode();

protected:
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::real dt ) override;

private:
	XE::uint64 _Current;
};

class AI_API BTParallelNode : public BTCompositeNode
{
	OBJECT( BTParallelNode, BTCompositeNode )

public:
	BTParallelNode();

	~BTParallelNode();

protected:
	virtual void OnUpdate( XE::real dt ) override;

};

END_XE_NAMESPACE

#endif // __BTCOMPOSITENODE_H__70BFB67B_E6B3_45A9_B9E1_A31B99D95716
