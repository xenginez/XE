/*!
 * \file   CompositeNode.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __COMPOSITENODE_H__70BFB67B_E6B3_45A9_B9E1_A31B99D95716
#define __COMPOSITENODE_H__70BFB67B_E6B3_45A9_B9E1_A31B99D95716

#include "Node.h"

BEG_XE_NAMESPACE

class AI_API CompositeNode : public Node
{
	OBJECT( CompositeNode, Node )

public:
	CompositeNode();

	~CompositeNode();

public:
	const Array<Node *> GetChildren() const;

protected:
	virtual void OnStartup() override;

	virtual void OnClearup() override;

private:
	Array<NodeHandle> _Children;
	Array<Node *> _Nodes;
};

class AI_API SequenceNode : public CompositeNode
{
	OBJECT( SequenceNode, CompositeNode )

public:
	SequenceNode();

	~SequenceNode();

protected:
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::real dt ) override;

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
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::real dt ) override;

private:
	XE::uint64 _Current;
};

class AI_API ParallelNode : public CompositeNode
{
	OBJECT( ParallelNode, CompositeNode )

public:
	ParallelNode();

	~ParallelNode();

protected:
	virtual void OnUpdate( XE::real dt ) override;

};

END_XE_NAMESPACE

#endif // __COMPOSITENODE_H__70BFB67B_E6B3_45A9_B9E1_A31B99D95716
