#include "CompositeNode.h"

#include "BehaviorTree.h"

BEG_META( XE::CompositeNode )
type->Property( "Children", &CompositeNode::_Children );
END_META()

XE::CompositeNode::CompositeNode()
{

}

XE::CompositeNode::~CompositeNode()
{

}

const XE::Array<XE::AINodeHandle> & XE::CompositeNode::GetChildren() const
{
	return _Children;
}

void XE::CompositeNode::SetChildren( const XE::Array<XE::AINodeHandle> & val )
{
	_Children = val;
}

void XE::CompositeNode::OnStartup()
{
	Super::OnStartup();

	SetStatus( NodeStatus::Running );
}

void XE::CompositeNode::OnClearup()
{
	for ( auto handle : _Children )
	{
		auto node = GetBehaviorTree()->GetNode( handle );

		if ( node->GetStatus() != NodeStatus::Finish )
		{
			node->Clearup();
		}
	}

	Super::OnClearup();
}

BEG_META( XE::SequenceNode )
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

void XE::SequenceNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	auto children = GetChildren();

	if( AINodePtr node = GetBehaviorTree()->GetNode( GetChildren()[_Current] ) )
	{
		if ( node->GetStatus() == XE::NodeStatus::None )
		{
			node->Startup();
		}

		if ( node->GetStatus() == XE::NodeStatus::Running )
		{
			node->Update( dt );
		}
		else if ( node->GetStatus() == XE::NodeStatus::Success || node->GetStatus() == XE::NodeStatus::Failure )
		{
			node->Clearup();
			_Current++;
		}
	}

	if ( _Current == children.size() )
	{
		SetStatus( XE::NodeStatus::Success );
	}
}

BEG_META( XE::SelectorNode )
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

void XE::SelectorNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	auto children = GetChildren();

	if( AINodePtr node = GetBehaviorTree()->GetNode( GetChildren()[_Current] ) )
	{
		if ( node->GetStatus() == XE::NodeStatus::None )
		{
			node->Startup();
		}

		if ( node->GetStatus() == XE::NodeStatus::Running )
		{
			node->Update( dt );
		}

		if ( node->GetStatus() == XE::NodeStatus::Failure )
		{
			node->Clearup();
			_Current++;
		}
		else if ( node->GetStatus() == XE::NodeStatus::Success )
		{
			node->Clearup();
			SetStatus( XE::NodeStatus::Success );
			return;
		}
	}

	if ( _Current == children.size() )
	{
		SetStatus( XE::NodeStatus::Failure );
	}
}

BEG_META( XE::ParallelNode )
END_META()

XE::ParallelNode::ParallelNode()
{

}

XE::ParallelNode::~ParallelNode()
{

}

void XE::ParallelNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	auto children = GetChildren();

	bool IsFinish = true;

	for ( auto handle : children )
	{
		AINodePtr node = GetBehaviorTree()->GetNode( handle );

		if ( node->GetStatus() == XE::NodeStatus::None )
		{
			node->Startup();
		}

		if ( node->GetStatus() == XE::NodeStatus::Running )
		{
			node->Update( dt );
		}

		if ( node->GetStatus() == XE::NodeStatus::Success || node->GetStatus() == XE::NodeStatus::Failure )
		{
			node->Clearup();
		}

		if ( node->GetStatus() != XE::NodeStatus::Finish )
		{
			IsFinish = false;
		}
	}

	if ( IsFinish )
	{
		SetStatus( XE::NodeStatus::Success );
	}
}
