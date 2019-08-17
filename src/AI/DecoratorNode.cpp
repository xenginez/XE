#include "DecoratorNode.h"

#include "BehaviorTree.h"

USING_XE

BEG_META( DecoratorNode )
type->Property( "Child", &DecoratorNode::_Child );
END_META()

XE::DecoratorNode::DecoratorNode()
	:_Node( nullptr )
{

}

XE::DecoratorNode::~DecoratorNode()
{

}

XE::Node * XE::DecoratorNode::GetChildNode() const
{
	return _Node;
}

void XE::DecoratorNode::OnStartup()
{
	Super::OnStartup();

	if ( Node * node = GetBehaviorTree()->GetNode( _Child ) )
	{
		_Node = node;

		node->Startup();

		SetStatus( NodeStatus::Running );
	}
	else
	{
		SetStatus( NodeStatus::Failure );
	}
}

void XE::DecoratorNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	if ( _Node && _Node->GetStatus() == NodeStatus::Running )
	{
		_Node->Update( dt );
	}
}

void XE::DecoratorNode::OnClearup()
{
	Super::OnClearup();

	if ( _Node )
	{
		if ( _Node->GetStatus() != NodeStatus::Finish )
		{
			_Node->Clearup();
		}
	}

	_Node = nullptr;
}

BEG_META( RepeatNode )
type->Property( "Count", &RepeatNode::_Count );
END_META()

XE::RepeatNode::RepeatNode()
	:_Count( -1 ), _Tally( -1 )
{

}

XE::RepeatNode::~RepeatNode()
{

}

void XE::RepeatNode::OnStartup()
{
	_Tally = _Count;

	Super::OnStartup();
}

void XE::RepeatNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	Node * node = GetChildNode();

	if ( node->GetStatus() == NodeStatus::Failure || node->GetStatus() == NodeStatus::Success )
	{
		node->Clearup();

		if ( _Count == -1 )
		{
			node->SetStatus( NodeStatus::None );
			node->Startup();
		}
		else
		{
			_Tally--;

			if ( _Tally <= 0 )
			{
				SetStatus( NodeStatus::Success );
			}
			else
			{
				node->SetStatus( NodeStatus::None );
				node->Startup();
			}
		}
	}
}

BEG_META( SuccessNode )
END_META()

XE::SuccessNode::SuccessNode()
{

}

XE::SuccessNode::~SuccessNode()
{

}

void XE::SuccessNode::OnStartup()
{
	Super::OnStartup();

	switch ( GetChildNode()->GetStatus() )
	{
	case NodeStatus::Failure:
	case NodeStatus::Success:
		SetStatus( NodeStatus::Success );
		break;
	default:
		SetStatus( NodeStatus::Running );
		break;
	}
}

void XE::SuccessNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	switch ( GetChildNode()->GetStatus() )
	{
	case NodeStatus::Failure:
	case NodeStatus::Success:
		SetStatus( NodeStatus::Success );
		break;
	default:
		break;
	}
}

BEG_META( FailureNode )
END_META()

XE::FailureNode::FailureNode()
{

}

XE::FailureNode::~FailureNode()
{

}

void XE::FailureNode::OnStartup()
{
	Super::OnStartup();

	switch ( GetChildNode()->GetStatus() )
	{
	case NodeStatus::Failure:
	case NodeStatus::Success:
		SetStatus( NodeStatus::Failure );
		break;
	default:
		break;
	}
}

void XE::FailureNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	switch ( GetChildNode()->GetStatus() )
	{
	case NodeStatus::Failure:
	case NodeStatus::Success:
		SetStatus( NodeStatus::Failure );
		break;
	default:
		break;
	}
}

BEG_META( ReversedNode )
END_META()

XE::ReversedNode::ReversedNode()
{

}

XE::ReversedNode::~ReversedNode()
{

}

void XE::ReversedNode::OnStartup()
{
	Super::OnStartup();

	switch ( GetChildNode()->GetStatus() )
	{
	case NodeStatus::Failure:
		SetStatus( NodeStatus::Success );
		break;
	case NodeStatus::Success:
		SetStatus( NodeStatus::Failure );
		break;
	default:
		break;
	}
}

void XE::ReversedNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	switch ( GetChildNode()->GetStatus() )
	{
	case NodeStatus::Failure:
		SetStatus( NodeStatus::Success );
		break;
	case NodeStatus::Success:
		SetStatus( NodeStatus::Failure );
		break;
	default:
		break;
	}
}

BEG_META( DelayNode )
type->Property( "DetlaTime", &DelayNode::_DetlaTime );
END_META()

XE::DelayNode::DelayNode()
	:_DetlaTime( 0 ), _Dt( 0 )
{

}

XE::DelayNode::~DelayNode()
{

}

void XE::DelayNode::OnStartup()
{
	Super::OnStartup();

	_Dt = _DetlaTime;

	SetStatus( NodeStatus::Running );
}

void XE::DelayNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	if ( GetChildNode()->GetStatus() == NodeStatus::Failure || GetChildNode()->GetStatus() == NodeStatus::Success )
	{
		_Dt -= dt;

		if ( _Dt <= Mathf::Epsilon )
		{
			SetStatus( GetChildNode()->GetStatus() );
		}
	}
}
