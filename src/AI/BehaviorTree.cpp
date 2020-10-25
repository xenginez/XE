#include "BehaviorTree.h"

#include "AINode.h"

BEG_META( XE::BehaviorTree )
type->Property( "Root", &BehaviorTree::_Root, IMetaProperty::NoDesign );
type->Property( "Nodes", &BehaviorTree::_Nodes, IMetaProperty::NoDesign );
END_META()

XE::BehaviorTree::BehaviorTree()
{

}

XE::BehaviorTree::~BehaviorTree()
{

}

void XE::BehaviorTree::Startup()
{
	Super::Startup();

	for( auto node : _Nodes )
	{
		node->SetBehaviorTree( XE_THIS( BehaviorTree ) );
	}
}

void XE::BehaviorTree::Update( XE::float32 dt )
{
	Super::Update( dt );

	if( _Root == AINodeHandle::Invalid )
	{
		return;
	}

	AINodePtr root = _Nodes[_Root];

	if( root->GetStatus() == NodeStatus::Finish )
	{
		return;
	}

	if( root->GetStatus() == NodeStatus::None )
	{
		root->Startup();
	}

	if( root->GetStatus() == NodeStatus::Running )
	{
		root->Update( dt );
	}

	if( root->GetStatus() == NodeStatus::Success || root->GetStatus() == NodeStatus::Failure )
	{
		root->Clearup();
	}
}

void XE::BehaviorTree::Clearup()
{
	for( auto node : _Nodes )
	{
		if( node->GetStatus() != NodeStatus::Finish )
		{
			node->Clearup();
		}
	}

	Super::Clearup();
}

XE::AINodeHandle XE::BehaviorTree::GetRoot() const
{
	return _Root;
}

void XE::BehaviorTree::SetRoot( XE::AINodeHandle val )
{
	_Root = val;
}

XE::AINodePtr XE::BehaviorTree::GetNode( AINodeHandle val ) const
{
	XE_ASSERT( val.GetValue() <= _Nodes.size() );

	return _Nodes[val.GetValue()];
}

const XE::Array< XE::AINodePtr > & XE::BehaviorTree::GetNodes() const
{
	return _Nodes;
}

void XE::BehaviorTree::SetNodes( const XE::Array< XE::AINodePtr > & val )
{
	_Nodes = val;
}
