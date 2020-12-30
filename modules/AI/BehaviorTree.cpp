#include "BehaviorTree.h"

#include "Node.h"

BEG_META( AI::BehaviorTree )
type->Property( "Root", &AI::BehaviorTree::_Root, IMetaProperty::NoDesign );
type->Property( "Nodes", &AI::BehaviorTree::_Nodes, IMetaProperty::NoDesign );
END_META()

AI::BehaviorTree::BehaviorTree()
{

}

AI::BehaviorTree::~BehaviorTree()
{

}

void AI::BehaviorTree::Startup()
{
	Super::Startup();

	for( auto node : _Nodes )
	{
		node->SetBehaviorTree( XE_THIS( BehaviorTree ) );
		node->Startup();
	}
}

void AI::BehaviorTree::Enter()
{
	Super::Enter();

	_Nodes[_Root]->Enter();
}

void AI::BehaviorTree::Update( XE::float32 dt )
{
	Super::Update( dt );

	if( IsStopped() )
	{
		return;
	}

	AI::NodeHandle handle;

	for( auto it = _RunningNodes.begin(); it != _RunningNodes.end(); ++it )
	{
		if( ( *it )->GetType() == AI::AINodeType::CONDITION_NODE )
		{
			auto cond = static_cast< AI::ConditionNode * >( ( *it ) );
			if( cond->JudgmentChanged() )
			{
				if( handle )
				{
					_RunningNodes.erase( it + 1, _RunningNodes.end() );
					if( !_CompositeNodes.empty() )
					{
						handle = _CompositeNodes.front();
					}
					break;
				}
				else
				{
					_CompositeNodes.push_front( cond->GetHandle() );
				}
			}
		}
		else
		{
			handle = static_cast< AI::CompositeNode * >( ( *it ) )->GetHandle();
			break;
		}
	}
	_CompositeNodes.clear();

	if( !handle )
	{
		if( !_RunningNodes.empty() )
		{
			handle = static_cast< AI::ConditionNode * >( _RunningNodes.back() )->GetChild();
		}
		else
		{
			handle = _Root;
		}
	}

	auto & current = _Nodes[handle];

	switch( current->GetStatus() )
	{
	case AI::AINodeStatus::NONE:
		current->Enter();
	case AI::AINodeStatus::RUNNING:
		current->Update( dt );
		break;
	case AI::AINodeStatus::FAILURE:
	case AI::AINodeStatus::SUCCESS:
		_Nodes[_Root]->Quit();
		_RunningNodes.clear();
		break;
	default:
		break;
	}
}

void AI::BehaviorTree::Quit()
{
	_Nodes[_Root]->Quit();

	Super::Quit();
}

void AI::BehaviorTree::Clearup()
{
	_RunningNodes.clear();

	for( auto node : _Nodes )
	{
		node->Clearup();
		node->SetBehaviorTree( nullptr );
	}

	Super::Clearup();
}

void AI::BehaviorTree::AssetLoad()
{
	Super::AssetLoad();

	for( auto & node : _Nodes )
	{
		node->AssetLoad();
	}
}

bool AI::BehaviorTree::IsStopped() const
{
	return _Nodes[_Root]->GetStatus() == AINodeStatus::SUCCESS || _Nodes[_Root]->GetStatus() == AINodeStatus::FAILURE;
}

AI::NodeHandle AI::BehaviorTree::GetRoot() const
{
	return _Root;
}

void AI::BehaviorTree::SetRoot( AI::NodeHandle val )
{
	_Root = val;
}

AI::NodePtr AI::BehaviorTree::GetNode( AI::NodeHandle val ) const
{
	XE_ASSERT( val.GetValue() <= _Nodes.size() );

	return _Nodes[val.GetValue()];
}

const XE::Array< AI::NodePtr > & AI::BehaviorTree::GetNodes() const
{
	return _Nodes;
}

void AI::BehaviorTree::SetNodes( const XE::Array< AI::NodePtr > & val )
{
	_Nodes = val;
}

void AI::BehaviorTree::PushCompositeNode( AI::CompositeNode * val )
{
	_RunningNodes.push_back( val );
}

void AI::BehaviorTree::PushConditionNode( AI::ConditionNode * val )
{
	_RunningNodes.push_back( val );
}
