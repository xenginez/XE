#include "BehaviorTree.h"

#include "Node.h"

USING_XE

XE::BehaviorTree::BehaviorTree()
{

}

XE::BehaviorTree::~BehaviorTree()
{

}

void XE::BehaviorTree::Startup()
{
	for ( auto node : _Nodes )
	{
		node->SetBehaviorTree( this );
	}
}

void XE::BehaviorTree::Update( XE::float32 dt )
{
	NodePtr root = _Nodes[_Root.GetValue()];

	if ( root->GetStatus() == NodeStatus::Finish )
	{
		return;
	}

	if ( root->GetStatus() == NodeStatus::None )
	{
		root->Startup();
	}

	if ( root->GetStatus() == NodeStatus::Running )
	{
		root->Update( dt );
	}

	if ( root->GetStatus() == NodeStatus::Success || root->GetStatus() == NodeStatus::Failure )
	{
		root->Clearup();
	}
}

void XE::BehaviorTree::Clearup()
{
	for ( auto node : _Nodes )
	{
		if ( node->GetStatus() != NodeStatus::Finish )
		{
			node->Clearup();
		}
	}
}

XE::Node * XE::BehaviorTree::GetRoot() const
{
	return _Nodes[_Root.GetValue()].get();
}

XE::BlackBoard * XE::BehaviorTree::GetBlackBoard() const
{
	return _Blackboard.get();
}

XE::Node * XE::BehaviorTree::GetNode( NodeHandle val ) const
{
	XE_ASSERT( val.GetValue() < _Nodes.size() );

	return _Nodes[val.GetValue()].get();
}
