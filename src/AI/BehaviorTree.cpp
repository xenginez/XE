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

	_Current = _Root;
}

void XE::BehaviorTree::Update( XE::float32 dt )
{
	Super::Update( dt );

	for( auto it = _Conditions.begin(); it != _Conditions.end(); ++it )
	{
		if( ( *it )->JudgmentChanged() )
		{
			( *it )->Quit();
			_Current = ( *it )->GetHandle();
			_Conditions.erase( it, _Conditions.end() );
		}
	}

	auto & current = _Nodes[_Current];

	auto status = current->GetStatus();

	switch( status )
	{
	case XE::NodeStatus::None:
		current->Enter();
	case XE::NodeStatus::Running:
		current->Update( dt );
		break;
	case XE::NodeStatus::Failure:
	case XE::NodeStatus::Success:
		current->Quit();
	default:
		break;
	}

	_Status = status;
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

void XE::BehaviorTree::PushConditionNode( XE::ConditionNode * val )
{
	if( !_Conditions.empty() )
	{
		if( _Conditions.back() == val )
		{
			return;
		}
	}

	_Current = val->GetHandle();
	_Conditions.push_back( val );
}
