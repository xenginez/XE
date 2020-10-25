/*!
 * \file   Node.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __NODE_H__4E15E329_D9A1_4F5D_B63A_CA4079844C18
#define __NODE_H__4E15E329_D9A1_4F5D_B63A_CA4079844C18

#include "Item.h"
#include "BlackboardKey.h"

BEG_XE_NAMESPACE

class XE_API Node : public XE::Item
{
	OBJECT( Node, Item )

private:
	friend class BehaviorTree;

public:
	Node();

	~Node();

public:
	NodeHandle GetHandle() const;

	void SetHandle( NodeHandle val );

	NodeHandle GetParent() const;

	void SetParent( NodeHandle val );

	const BehaviorTreePtr & GetBehaviorTree() const;

	void SetBehaviorTree( const BehaviorTreePtr & val );

public:
	NodeStatus GetStatus() const;

	void SetStatus( NodeStatus val );

public:
	virtual void Startup();

	virtual void Update( XE::float32 dt );

	virtual void Clearup();

protected:
	virtual void OnStartup();
				 
	virtual void OnUpdate( XE::float32 dt );
				 
	virtual void OnClearup();

	virtual void OnRemove();

	virtual void OnResetHandle();

private:
	NodeHandle _Handle;
	NodeHandle _Parent;
	NodeStatus _Status;

	BehaviorTreePtr _BehaviorTree;
};

class XE_API SubNode : public XE::Node
{
	OBJECT( SubNode, Node )

public:
	SubNode();

	~SubNode();

public:
	const XE::Map<XE::BlackboardKey, XE::BlackboardKey> & GetConnectKeys() const;

	void SetConnectKeys( const XE::Map<XE::BlackboardKey, XE::BlackboardKey> & val );

protected:
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::float32 dt ) override;

	virtual void OnClearup() override;

private:
	XE::AIModulePtr _SubAI;
	XE::FileSystem::Path _SubAIPath;
	XE::Map<XE::BlackboardKey, XE::BlackboardKey> _ConnectKeys;
};

END_XE_NAMESPACE

#endif // __NODE_H__4E15E329_D9A1_4F5D_B63A_CA4079844C18
