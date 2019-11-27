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

const XE::Array<NodeHandle> & XE::CompositeNode::GetChildren() const
{
	return _Children;
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

void XE::CompositeNode::OnRemove()
{
	for( const auto & child : _Children )
	{
		if( child != NodeHandle::Invalid )
		{
			GetBehaviorTree()->RemoveNode( child );
		}
	}
}

XE::NodeHandle CompositeNode::AddChild( const IMetaClassPtr & val )
{
	NodeHandle handle = GetBehaviorTree()->AddNode( val );
	GetBehaviorTree()->GetNode( handle )->SetParent( GetHandle() );
	_Children.push_back( handle );
	return handle;
}

void CompositeNode::RemoveChild( NodeHandle val )
{
	auto it = std::find( _Children.begin(), _Children.end(), val );

	if( it != _Children.end() )
	{
		_Children.erase( it );

		GetBehaviorTree()->RemoveNode( val );
	}
}

void CompositeNode::OnResetHandle()
{
	for( const auto & handle : _Children )
	{
		GetBehaviorTree()->GetNode( handle )->SetParent( GetHandle() );
	}
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

void XE::SequenceNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	auto children = GetChildren();

	if( NodePtr node = GetBehaviorTree()->GetNode( GetChildren()[_Current] ) )
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

void XE::SelectorNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	auto children = GetChildren();

	if( NodePtr node = GetBehaviorTree()->GetNode( GetChildren()[_Current] ) )
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

void XE::ParallelNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	auto children = GetChildren();

	bool IsFinish = true;

	for ( auto handle : children )
	{
		NodePtr node = GetBehaviorTree()->GetNode( handle );

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
