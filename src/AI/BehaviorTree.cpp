#include "BehaviorTree.h"

#include "AINode.h"

BEG_META( XE::BehaviorTree )
type->Property( "Root", &BehaviorTree::_Root, IMetaProperty::NoDesign );
type->Property( "Nodes", &BehaviorTree::_Nodes, IMetaProperty::NoDesign );
END_META()

struct XE::BehaviorTree::PrivateNode
{
	bool IsCondition = false;
	XE::AINode * Node = nullptr;
};

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
		node->Startup();
	}

	_Current = _Root;
}

void XE::BehaviorTree::Update( XE::float32 dt )
{
	Super::Update( dt );

	XE::AINodeHandle handle;
	for( auto it = _PrivateNodes.begin(); it != _PrivateNodes.end(); ++it )
	{
		if( it->IsCondition )
		{
			auto cond = static_cast< XE::ConditionNode * >( it->Node );
			if( cond->JudgmentChanged() )
			{
				if( handle )
				{
					_PrivateNodes.erase( it + 1, _PrivateNodes.end() );
					break;
				}
				else
				{
					handle = cond->GetHandle();
					break;
				}
			}
		}
		else
		{
			handle = static_cast< XE::CompositeNode * >( it->Node )->GetHandle();
		}
	}

	if( !handle && !_PrivateNodes.empty() )
	{
		handle = static_cast< XE::ConditionNode * >( _PrivateNodes.back().Node )->GetChild();
	}
	else
	{
		handle = _Root;
	}

	auto & current = _Nodes[handle];

	switch( current->GetStatus() )
	{
	case XE::NodeStatus::None:
		current->Enter();
	case XE::NodeStatus::Running:
		current->Update( dt );
		_Status = NodeStatus::Running;
		break;
	case XE::NodeStatus::Failure:
		_Status = NodeStatus::Failure;
		current->Quit();
		break;
	case XE::NodeStatus::Success:
		_Status = NodeStatus::Success;
		current->Quit();
		break;
	default:
		break;
	}
}

void XE::BehaviorTree::Clearup()
{
	for( auto node : _Nodes )
	{
		node->Clearup();
		node->SetBehaviorTree( nullptr );
	}

	Super::Clearup();
}

void XE::BehaviorTree::AssetLoad()
{
	Super::AssetLoad();

	for( auto & node : _Nodes )
	{
		node->AssetLoad();
	}
}

bool XE::BehaviorTree::IsStopped() const
{
	return _Status == NodeStatus::Success || _Status == NodeStatus::Failure;
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

void XE::BehaviorTree::PushCompositeNode( XE::CompositeNode * val )
{
	XE::BehaviorTree::PrivateNode node;
	node.Node = val;
	node.IsCondition = false;
	_PrivateNodes.emplace_back( std::move( node ) );
}

void XE::BehaviorTree::PushConditionNode( XE::ConditionNode * val )
{
	XE::BehaviorTree::PrivateNode node;
	node.Node = val;
	node.IsCondition = true;
	_PrivateNodes.emplace_back( std::move( node ) );
}
