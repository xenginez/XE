#include "BehaviorTree.h"

#include "Node.h"



BEG_META( XE::BehaviorTree )
type->Property( "HandleAlloc", &BehaviorTree::_HandleAlloc, IMetaProperty::NoDesign );
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

	NodePtr root = _Nodes[_Root];

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

XE::NodeHandle XE::BehaviorTree::GetRoot() const
{
	return _Root;
}

void XE::BehaviorTree::SetRoot( XE::NodeHandle val )
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

XE::NodeHandle XE::BehaviorTree::AddNode( const XE::IMetaClassPtr & val )
{
	if( val )
	{
		if( XE::NodePtr node = val->ConstructPtr().Value<XE::NodePtr>() )
		{
			node->SetName( val->GetName() );
			node->SetBehaviorTree( XE_THIS( XE::BehaviorTree ) );
			node->SetHandle( _HandleAlloc.Alloc() );

			_Nodes.insert( { node->GetHandle(), node } );

			return node->GetHandle();
		}
	}

	return XE::NodeHandle::Invalid;
}

void XE::BehaviorTree::RemoveNode( XE::NodeHandle val )
{
	auto it = _Nodes.find( val );
	if( it != _Nodes.end() )
	{
		it->second->OnRemove();
		_Nodes.erase( it );
	}
}

void XE::BehaviorTree::SwapNodeHandle( XE::NodeHandle node1, XE::NodeHandle node2 )
{
	_Nodes[node1]->SetHandle( node2 );
	_Nodes[node2]->SetHandle( node1 );

	auto node = _Nodes[node1];
	_Nodes[node1] = _Nodes[node2];
	_Nodes[node2] = node;

	_Nodes[node1]->OnResetHandle();
	_Nodes[node2]->OnResetHandle();
}
