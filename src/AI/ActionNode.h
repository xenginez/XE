/*!
 * \file   ActionNode.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __ACTIONNODE_H__C24DA3A3_57C0_409B_B964_A146B2FF23E1
#define __ACTIONNODE_H__C24DA3A3_57C0_409B_B964_A146B2FF23E1

#include "Key.h"
#include "Node.h"

BEG_XE_NAMESPACE

class ConditionNode;

class XE_API ActionNode : public Node
{
	OBJECT( ActionNode, Node )

public:
	ActionNode();

	~ActionNode();

};

class XE_API SubNode : public XE::ActionNode
{
	OBJECT( SubNode, ActionNode )

public:
	SubNode();

	~SubNode();

public:
	const XE::Map<XE::Key, XE::Key> & GetConnectKeys() const;

	void SetConnectKeys( const XE::Map<XE::Key, XE::Key> & val );

protected:
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::float32 dt ) override;

	virtual void OnClearup() override;

private:
	XE::String _SubAIPath;
	XE::AIModulePtr _SubAI;
	XE::Map<XE::Key, XE::Key> _ConnectKeys;
};

END_XE_NAMESPACE

#endif // __ACTIONNODE_H__C24DA3A3_57C0_409B_B964_A146B2FF23E1
