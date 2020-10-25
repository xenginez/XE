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

#include "BlackboardKey.h"

BEG_XE_NAMESPACE

class XE_API AINode : public XE::Object
{
	OBJECT( AINode, Object )

private:
	friend class BehaviorTree;

public:
	AINode();

	~AINode();

public:
	NodeStatus GetStatus() const;

	void SetStatus( NodeStatus val );

	AINodeHandle GetHandle() const;

	void SetHandle( AINodeHandle val );

	AINodeHandle GetParent() const;

	void SetParent( AINodeHandle val );

	const XE::String & GetName() const;

	void SetName( const XE::String & val );

public:
	BehaviorTreePtr GetBehaviorTree() const;

private:
	void SetBehaviorTree( BehaviorTreePtr val );

public:
	virtual void Startup();

	virtual void Update( XE::float32 dt );

	virtual void Clearup();

protected:
	virtual void OnStartup();
				 
	virtual void OnUpdate( XE::float32 dt );
				 
	virtual void OnClearup();

private:
	XE::String _Name;
	NodeStatus _Status;
	AINodeHandle _Handle;
	AINodeHandle _Parent;

	BehaviorTreeWPtr _BehaviorTree;
};

class XE_API SubNode : public XE::AINode
{
	OBJECT( SubNode, AINode )

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
