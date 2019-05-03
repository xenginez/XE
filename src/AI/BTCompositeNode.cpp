#include "BTCompositeNode.h"

#include "BehaviorTree.h"

USING_XE

BEGIN_META( BTCompositeNode )
type->Property( "Children", &BTCompositeNode::_Children );
END_META()

XE::BTCompositeNode::BTCompositeNode()
{

}

XE::BTCompositeNode::~BTCompositeNode()
{

}

const XE::Array<Node *> XE::BTCompositeNode::GetChildren() const
{
	return _Nodes;
}

void XE::BTCompositeNode::OnStartup()
{
	Super::OnStartup();

	for (auto h : _Children)
	{
		_Nodes.push_back( GetBehaviorTree()->GetNode( h ) );
	}

	SetStatus( NodeStatus::Running );
}

void XE::BTCompositeNode::OnClearup()
{
	for ( auto node : _Nodes )
	{
		if ( node->GetStatus() != NodeStatus::Finish )
		{
			node->Clearup();
		}
	}

	Super::OnClearup();
}

BEGIN_META( BTSequenceNode )
END_META()

XE::BTSequenceNode::BTSequenceNode()
	:_Current( 0 )
{

}

XE::BTSequenceNode::~BTSequenceNode()
{

}

void XE::BTSequenceNode::OnStartup()
{
	Super::OnStartup();

	_Current = 0;
}

void XE::BTSequenceNode::OnUpdate( float dt )
{
	Super::OnUpdate( dt );

	auto children = GetChildren();

	if ( Node * node = children[_Current] )
	{
		if ( node->GetStatus() == NodeStatus::None )
		{
			node->Startup();
		}

		if ( node->GetStatus() == NodeStatus::Running )
		{
			node->Update( dt );
		}
		else if ( node->GetStatus() == NodeStatus::Success || node->GetStatus() == NodeStatus::Failure )
		{
			node->Clearup();
			_Current++;
		}
	}

	if ( _Current == children.size() )
	{
		SetStatus( NodeStatus::Success );
	}
}

BEGIN_META( BTSelectorNode )
END_META()

XE::BTSelectorNode::BTSelectorNode()
	:_Current( 0 )
{

}

XE::BTSelectorNode::~BTSelectorNode()
{

}

void XE::BTSelectorNode::OnStartup()
{
	Super::OnStartup();

	_Current = 0;
}

void XE::BTSelectorNode::OnUpdate( float dt )
{
	Super::OnUpdate( dt );

	auto children = GetChildren();

	if ( Node * node = children[_Current] )
	{
		if ( node->GetStatus() == NodeStatus::None )
		{
			node->Startup();
		}

		if ( node->GetStatus() == NodeStatus::Running )
		{
			node->Update( dt );
		}

		if ( node->GetStatus() == NodeStatus::Failure )
		{
			node->Clearup();
			_Current++;
		}
		else if ( node->GetStatus() == NodeStatus::Success )
		{
			node->Clearup();
			SetStatus( NodeStatus::Success );
			return;
		}
	}

	if ( _Current == children.size() )
	{
		SetStatus( NodeStatus::Failure );
	}
}

BEGIN_META( BTParallelNode )
END_META()

XE::BTParallelNode::BTParallelNode()
{

}

XE::BTParallelNode::~BTParallelNode()
{

}

void XE::BTParallelNode::OnUpdate( float dt )
{
	Super::OnUpdate( dt );

	auto children = GetChildren();

	bool IsFinish = true;

	for ( auto node : children )
	{
		if ( node->GetStatus() == NodeStatus::None )
		{
			node->Startup();
		}

		if ( node->GetStatus() == NodeStatus::Running )
		{
			node->Update( dt );
		}

		if ( node->GetStatus() == NodeStatus::Success || node->GetStatus() == NodeStatus::Failure )
		{
			node->Clearup();
		}

		if ( node->GetStatus() != NodeStatus::Finish )
		{
			IsFinish = false;
		}
	}

	if ( IsFinish )
	{
		SetStatus( NodeStatus::Success );
	}
}
