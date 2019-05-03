/*!
 * \file   DecoratorNode.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __BTDECORATORNODE_H__2A691197_19EA_4562_AE5B_28F1439B2C47
#define __BTDECORATORNODE_H__2A691197_19EA_4562_AE5B_28F1439B2C47

#include "Node.h"

BEG_XE_NAMESPACE

class AI_API BTDecoratorNode : public Node
{
	OBJECT( BTDecoratorNode, Node )

public:
	BTDecoratorNode();

	~BTDecoratorNode();

public:
	Node * GetChildNode() const;

public:
	virtual void OnStartup() override;

	virtual void OnUpdate( float dt ) override;

	virtual void OnClearup() override;

private:
	NodeHandle _Child;
	Node * _Node;
};

class AI_API BTRepeatNode : public BTDecoratorNode
{
	OBJECT( BTRepeatNode, BTDecoratorNode )

public:
	BTRepeatNode();

	~BTRepeatNode();

public:
	virtual void OnStartup() override;

	virtual void OnUpdate( float dt ) override;

private:
	int64 _Count;
	int64 _Tally;
};

class AI_API BTSuccessNode : public BTDecoratorNode
{
	OBJECT( BTSuccessNode, BTDecoratorNode )

public:
	BTSuccessNode();

	~BTSuccessNode();

public:
	virtual void OnStartup() override;

	virtual void OnUpdate( float dt ) override;

};

class AI_API BTFailureNode : public BTDecoratorNode
{
	OBJECT( BTFailureNode, BTDecoratorNode )

public:
	BTFailureNode();

	~BTFailureNode();

public:
	virtual void OnStartup() override;

	virtual void OnUpdate( float dt ) override;

};

class AI_API BTReversedNode : public BTDecoratorNode
{
	OBJECT( BTReversedNode, BTDecoratorNode )

public:
	BTReversedNode();

	~BTReversedNode();

public:
	virtual void OnStartup() override;

	virtual void OnUpdate( float dt ) override;

};

class AI_API BTDelayNode : public BTDecoratorNode
{
	OBJECT( BTDelayNode, BTDecoratorNode )

public:
	BTDelayNode();

	~BTDelayNode();

public:
	virtual void OnStartup() override;

	virtual void OnUpdate( float dt ) override;

private:
	float _DetlaTime;
	float _Dt;
};

END_XE_NAMESAPCE

#endif // __BTDECORATORNODE_H__2A691197_19EA_4562_AE5B_28F1439B2C47
