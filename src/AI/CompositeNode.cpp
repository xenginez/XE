#include "CompositeNode.h"

#include "BehaviorTree.h"

USING_XE

BEG_META( CompositeNode )
type->Property( "Children", &CompositeNode::_Children );
END_META()

XE::CompositeNode::CompositeNode()
{

}

XE::CompositeNode::~CompositeNode()
{

}

const XE::Array<Node *> XE::CompositeNode::GetChildren() const
{
	return _Nodes;
}

void XE::CompositeNode::OnStartup()
{
	Super::OnStartup();

	for (auto h : _Children)
	{
		_Nodes.push_back( GetBehaviorTree()->GetNode( h ) );
	}

	SetStatus( NodeStatus::Running );
}

void XE::CompositeNode::OnClearup()
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

BEG_META( SequenceNode )
END_META()

XE::SequenceNode::SequenceNode()
	:_Current( 0 )
{

}

XE::SequenceNode::~SequenceNode()
{

}

void XE::SequenceNode::OnStartup()
{
	Super::OnStartup();

	_Current = 0;
}

void XE::SequenceNode::OnUpdate( float dt )
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

BEG_META( SelectorNode )
END_META()

XE::SelectorNode::SelectorNode()
	:_Current( 0 )
{

}

XE::SelectorNode::~SelectorNode()
{

}

void XE::SelectorNode::OnStartup()
{
	Super::OnStartup();

	_Current = 0;
}

void XE::SelectorNode::OnUpdate( float dt )
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

BEG_META( ParallelNode )
END_META()

XE::ParallelNode::ParallelNode()
{

}

XE::ParallelNode::~ParallelNode()
{

}

void XE::ParallelNode::OnUpdate( float dt )
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
