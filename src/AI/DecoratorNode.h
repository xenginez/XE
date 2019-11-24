/*!
 * \file   DecoratorNode.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __DECORATORNODE_H__2A691197_19EA_4562_AE5B_28F1439B2C47
#define __DECORATORNODE_H__2A691197_19EA_4562_AE5B_28F1439B2C47

#include "Node.h"

BEG_XE_NAMESPACE

class XE_API DecoratorNode : public Node
{
	OBJECT( DecoratorNode, Node )

public:
	DecoratorNode();

	~DecoratorNode();

public:
	const NodePtr & GetChildNode() const;

	void SetChildNode( const IMetaClassPtr & val );

public:
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::float32 dt ) override;

	virtual void OnClearup() override;

private:
	NodeHandle _Child;
};

class XE_API RepeatNode : public DecoratorNode
{
	OBJECT( RepeatNode, DecoratorNode )

public:
	RepeatNode();

	~RepeatNode();

public:
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::float32 dt ) override;

private:
	XE::int64 _Count;
	XE::int64 _Tally;
};

class XE_API SuccessNode : public DecoratorNode
{
	OBJECT( SuccessNode, DecoratorNode )

public:
	SuccessNode();

	~SuccessNode();

public:
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::float32 dt ) override;

};

class XE_API FailureNode : public DecoratorNode
{
	OBJECT( FailureNode, DecoratorNode )

public:
	FailureNode();

	~FailureNode();

public:
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::float32 dt ) override;

};

class XE_API ReversedNode : public DecoratorNode
{
	OBJECT( ReversedNode, DecoratorNode )

public:
	ReversedNode();

	~ReversedNode();

public:
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::float32 dt ) override;

};

class XE_API DelayNode : public DecoratorNode
{
	OBJECT( DelayNode, DecoratorNode )

public:
	DelayNode();

	~DelayNode();

public:
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::float32 dt ) override;

private:
	XE::float32 _DetlaTime;
	XE::float32 _Dt;
};

END_XE_NAMESPACE

#endif // __DECORATORNODE_H__2A691197_19EA_4562_AE5B_28F1439B2C47
