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
		node->Startup();
	}
}

void XE::BehaviorTree::Enter()
{
	Super::Enter();

	_Nodes[_Root]->Enter();
}

void XE::BehaviorTree::Update( XE::float32 dt )
{
	Super::Update( dt );

	if( IsStopped() )
	{
		return;
	}

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
					if( !_ParallelNodes.empty() )
					{
						handle = _ParallelNodes.front();
					}
					break;
				}
				else
				{
					_ParallelNodes.push_front( cond->GetHandle() );
				}
			}
		}
		else
		{
			handle = static_cast< XE::CompositeNode * >( it->Node )->GetHandle();
			break;
		}
	}
	_ParallelNodes.clear();

	if( !handle )
	{
		if( !_PrivateNodes.empty() )
		{
			handle = static_cast< XE::ConditionNode * >( _PrivateNodes.back().Node )->GetChild();
		}
		else
		{
			handle = _Root;
		}
	}

	auto & current = _Nodes[handle];

	switch( current->GetStatus() )
	{
	case XE::NodeStatus::NONE:
		current->Enter();
	case XE::NodeStatus::RUNNING:
		current->Update( dt );
		break;
	case XE::NodeStatus::FAILURE:
	case XE::NodeStatus::SUCCESS:
		_Nodes[_Root]->Quit();
		_PrivateNodes.clear();
		break;
	default:
		break;
	}
}

void XE::BehaviorTree::Quit()
{
	_Nodes[_Root]->Quit();

	Super::Quit();
}

void XE::BehaviorTree::Clearup()
{
	_PrivateNodes.clear();

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
	return _Nodes[_Root]->GetStatus() == NodeStatus::SUCCESS || _Nodes[_Root]->GetStatus() == NodeStatus::FAILURE;
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

void XE::BehaviorTree::PushParallelNode( XE::ParallelNode * val )
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
