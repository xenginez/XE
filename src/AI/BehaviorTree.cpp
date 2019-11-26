#include "BehaviorTree.h"

#include "CompositeNode.h"

USING_XE

BEG_META( BehaviorTree )
END_META()

XE::BehaviorTree::BehaviorTree()
{

}

XE::BehaviorTree::~BehaviorTree()
{

}

void XE::BehaviorTree::Startup()
{
	if( _Nodes.empty() )
	{
		_Root = AddNode( SequenceNode::GetMetaClassStatic() );
	}

	for ( auto node : _Nodes )
	{
		node->SetBehaviorTree( XE_THIS( BehaviorTree ) );
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

NodeHandle XE::BehaviorTree::GetRoot() const
{
	return _Root;
}

void BehaviorTree::SetRoot( NodeHandle val )
{
	_Root = val;
}

XE::BlackBoardPtr XE::BehaviorTree::GetBlackBoard() const
{
	return _Blackboard;
}

const XE::NodePtr & XE::BehaviorTree::GetNode( NodeHandle val ) const
{
	XE_ASSERT( val.GetValue() < _Nodes.size() );

	return _Nodes[val.GetValue()];
}

NodeHandle BehaviorTree::AddNode( const IMetaClassPtr & val )
{
	if( val )
	{
		if( NodePtr node = val->ConstructPtr().Value<NodePtr>() )
		{
			node->SetHandle( _Nodes.size() );
			node->SetBehaviorTree( XE_THIS( BehaviorTree ) );

			_Nodes.push_back( node );

			return node->GetHandle();
		}
	}

	return NodeHandle::Invalid;
}

void BehaviorTree::RemoveNode( XE::NodeHandle val )
{
	XE_ASSERT( val.GetValue() < _Nodes.size() );

	_Nodes[val.GetValue()]->OnRemove();

	_Nodes[val.GetValue()] = nullptr;
}
