#include "ActionNode.h"

#include <Interface/IFramework.h>
#include <Interface/IAssetsService.h>

#include "BehaviorTree.h"

BEG_META( XE::ActionNode )
END_META()

XE::ActionNode::ActionNode()
{

}

XE::ActionNode::~ActionNode()
{

}

BEG_META( XE::SubNode )
type->Property( "SubAI", &SubNode::_SubAIPath );
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
	_SubAI = DP_CAST<XE::AIModule>( XE::IFramework::GetCurrentFramework()->GetAssetsService()->LoadObject( _SubAIPath ) );

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
