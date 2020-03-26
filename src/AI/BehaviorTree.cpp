#include "BehaviorTree.h"

#include "Node.h"

USING_XE

BEG_META( BehaviorTree )
type->Property( "Handles", &BehaviorTree::_Handles, IMetaProperty::NoDesign );
type->Property( "Root", &BehaviorTree::_Root, IMetaProperty::NoDesign );
type->Property( "Nodes", &BehaviorTree::_Nodes, IMetaProperty::NoDesign );
END_META()

XE::BehaviorTree::BehaviorTree()
	:_Handles( 0 )
{

}

XE::BehaviorTree::~BehaviorTree()
{

}

void XE::BehaviorTree::Startup()
{
	for( auto node : _Nodes )
	{
		node.second->SetBehaviorTree( XE_THIS( BehaviorTree ) );
	}
}

void XE::BehaviorTree::Update( XE::float32 dt )
{
	if( _Root == NodeHandle::Invalid )
	{
		return;
	}

	NodePtr root = _Nodes[_Root.GetValue()];

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
		if( node.second->GetStatus() != NodeStatus::Finish )
		{
			node.second->Clearup();
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

XE::NodePtr XE::BehaviorTree::GetNode( NodeHandle val ) const
{
	auto it = _Nodes.find( val );

	if( it != _Nodes.end() )
	{
		return it->second;
	}

	return nullptr;
}

NodeHandle BehaviorTree::AddNode( const IMetaClassPtr & val )
{
	if( val )
	{
		if( NodePtr node = val->ConstructPtr().Value<NodePtr>() )
		{
			node->SetName( val->GetName() );
			node->SetBehaviorTree( XE_THIS( BehaviorTree ) );
			node->SetHandle( _Handles++ );

			_Nodes.insert( { node->GetHandle(), node } );

			return node->GetHandle();
		}
	}

	return NodeHandle::Invalid;
}

void BehaviorTree::RemoveNode( XE::NodeHandle val )
{
	auto it = _Nodes.find( val );
	if( it != _Nodes.end() )
	{
		it->second->OnRemove();
		_Nodes.erase( it );
	}
}

void BehaviorTree::SwapNodeHandle( XE::NodeHandle node1, XE::NodeHandle node2 )
{
	_Nodes[node1.GetValue()]->SetHandle( node2 );
	_Nodes[node2.GetValue()]->SetHandle( node1 );

	auto node = _Nodes[node1.GetValue()];
	_Nodes[node1.GetValue()] = _Nodes[node2.GetValue()];
	_Nodes[node2.GetValue()] = node;

	_Nodes[node1.GetValue()]->OnResetHandle();
	_Nodes[node2.GetValue()]->OnResetHandle();
}
