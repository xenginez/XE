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

	for( auto it = _RunningNodes.begin(); it != _RunningNodes.end(); ++it )
	{
		if( ( *it )->GetType() == XE::AINodeType::CONDITION_NODE )
		{
			auto cond = static_cast< XE::ConditionNode * >( ( *it ) );
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
			handle = static_cast< XE::CompositeNode * >( ( *it ) )->GetHandle();
			break;
		}
	}
	_CompositeNodes.clear();

	if( !handle )
	{
		if( !_RunningNodes.empty() )
		{
			handle = static_cast< XE::ConditionNode * >( _RunningNodes.back() )->GetChild();
		}
		else
		{
			handle = _Root;
		}
	}

	auto & current = _Nodes[handle];

	switch( current->GetStatus() )
	{
	case XE::AINodeStatus::NONE:
		current->Enter();
	case XE::AINodeStatus::RUNNING:
		current->Update( dt );
		break;
	case XE::AINodeStatus::FAILURE:
	case XE::AINodeStatus::SUCCESS:
		_Nodes[_Root]->Quit();
		_RunningNodes.clear();
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
	_RunningNodes.clear();

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
	return _Nodes[_Root]->GetStatus() == AINodeStatus::SUCCESS || _Nodes[_Root]->GetStatus() == AINodeStatus::FAILURE;
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
	_RunningNodes.emplace_back( std::move( node ) );
}

void XE::BehaviorTree::PushConditionNode( XE::ConditionNode * val )
{
	XE::BehaviorTree::PrivateNode node;
	node.Node = val;
	node.IsCondition = true;
	_RunningNodes.emplace_back( std::move( node ) );
}
