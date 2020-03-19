#include "ActionNode.h"

#include "BehaviorTree.h"

USING_XE

BEG_META( ActionNode )
END_META()

XE::ActionNode::ActionNode()
{

}

XE::ActionNode::~ActionNode()
{

}

BEG_META( SubNode )
type->Property( "SubAI", &SubNode::_SubAI );
type->Property( "ConnectKeys", &SubNode::_ConnectKeys );
END_META()

XE::SubNode::SubNode()
{

}

XE::SubNode::~SubNode()
{

}

void XE::SubNode::OnStartup()
{
	for( const auto & keys : _ConnectKeys )
	{
		_SubAI->SetKey( keys.second, GetBehaviorTree()->GetKey( keys.first ) );
	}

	_SubAI->Startup();
}

void XE::SubNode::OnUpdate( XE::float32 dt )
{
	for( const auto & keys : _ConnectKeys )
	{
		_SubAI->SetKey( keys.second, GetBehaviorTree()->GetKey( keys.first ) );
	}

	_SubAI->Update( dt );
}

void XE::SubNode::OnClearup()
{
	_SubAI->Clearup();
}

const XE::Map<XE::Key, XE::Key> & XE::SubNode::GetConnectKeys() const
{
	return _ConnectKeys;
}

void XE::SubNode::SetConnectKeys( const XE::Map<XE::Key, XE::Key> & val )
{
	_ConnectKeys = val;
}
