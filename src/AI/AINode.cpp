#include "AINode.h"

#include <Interface/IFramework.h>
#include <Interface/IAssetsService.h>

#include "BehaviorTree.h"

BEG_META( XE::AINode )
type->Property( "Name", &XE::AINode::_Name );
type->Property( "Parent", &XE::AINode::_Parent, XE::IMetaProperty::NoDesign );
type->Property( "Handle", &XE::AINode::_Handle, XE::IMetaProperty::NoDesign );
END_META()

XE::AINode::AINode()
	:_Status( NodeStatus::None )
{

}

XE::AINode::~AINode()
{

}

XE::AINodeHandle XE::AINode::GetHandle() const
{
	return _Handle;
}

void XE::AINode::SetHandle( XE::AINodeHandle val )
{
	_Handle = val;
}

XE::AINodeHandle XE::AINode::GetParent() const
{
	return _Parent;
}

void XE::AINode::SetParent( XE::AINodeHandle val )
{
	_Parent = val;
}

XE::BehaviorTreePtr XE::AINode::GetBehaviorTree() const
{
	return _BehaviorTree.lock();
}

void XE::AINode::SetBehaviorTree( BehaviorTreePtr val )
{
	_BehaviorTree = val;
}

XE::NodeStatus XE::AINode::GetStatus() const
{
	return _Status;
}

void XE::AINode::SetStatus( NodeStatus val )
{
	_Status = val;
}

const XE::String & XE::AINode::GetName() const
{
	return _Name;
}

void XE::AINode::SetName( const XE::String & val )
{
	_Name = val;
}

void XE::AINode::Startup()
{
	OnStartup();
}

void XE::AINode::Update( XE::float32 dt )
{
	OnUpdate( dt );
}

void XE::AINode::Clearup()
{
	OnClearup();
}

void XE::AINode::OnStartup()
{
	SetStatus( NodeStatus::Running );
}

void XE::AINode::OnUpdate( XE::float32 dt )
{

}

void XE::AINode::OnClearup()
{
	SetStatus( NodeStatus::Finish );
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
	for( const auto & key : _ConnectKeys )
	{
		_SubAI->SetKey( key.second, GetBehaviorTree()->GetKey( key.first ) );
	}

	_SubAI->Update( dt );

	for( const auto & key : _ConnectKeys )
	{
		GetBehaviorTree()->SetKey( key.first, _SubAI->GetKey( key.second ) );
	}
}

void XE::SubNode::OnClearup()
{
	_SubAI->Clearup();
}

const XE::Map<XE::BlackboardKey, XE::BlackboardKey> & XE::SubNode::GetConnectKeys() const
{
	return _ConnectKeys;
}

void XE::SubNode::SetConnectKeys( const XE::Map<XE::BlackboardKey, XE::BlackboardKey> & val )
{
	_ConnectKeys = val;
}
