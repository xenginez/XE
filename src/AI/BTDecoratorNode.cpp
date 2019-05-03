#include "BTDecoratorNode.h"

#include "BehaviorTree.h"

USING_XE

BEGIN_META( BTDecoratorNode )
type->Property( "Child", &BTDecoratorNode::_Child );
END_META()

XE::BTDecoratorNode::BTDecoratorNode()
	:_Node( nullptr )
{

}

XE::BTDecoratorNode::~BTDecoratorNode()
{

}

XE::Node * XE::BTDecoratorNode::GetChildNode() const
{
	return _Node;
}

void XE::BTDecoratorNode::OnStartup()
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

void XE::BTDecoratorNode::OnUpdate( float dt )
{
	Super::OnUpdate( dt );

	if ( _Node && _Node->GetStatus() == NodeStatus::Running )
	{
		_Node->Update( dt );
	}
}

void XE::BTDecoratorNode::OnClearup()
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

BEGIN_META( BTRepeatNode )
type->Property( "Count", &BTRepeatNode::_Count );
END_META()

XE::BTRepeatNode::BTRepeatNode()
	:_Count( -1 ), _Tally( -1 )
{

}

XE::BTRepeatNode::~BTRepeatNode()
{

}

void XE::BTRepeatNode::OnStartup()
{
	_Tally = _Count;

	Super::OnStartup();
}

void XE::BTRepeatNode::OnUpdate( float dt )
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

BEGIN_META( BTSuccessNode )
END_META()

XE::BTSuccessNode::BTSuccessNode()
{

}

XE::BTSuccessNode::~BTSuccessNode()
{

}

void XE::BTSuccessNode::OnStartup()
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

void XE::BTSuccessNode::OnUpdate( float dt )
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

BEGIN_META( BTFailureNode )
END_META()

XE::BTFailureNode::BTFailureNode()
{

}

XE::BTFailureNode::~BTFailureNode()
{

}

void XE::BTFailureNode::OnStartup()
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

void XE::BTFailureNode::OnUpdate( float dt )
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

BEGIN_META( BTReversedNode )
END_META()

XE::BTReversedNode::BTReversedNode()
{

}

XE::BTReversedNode::~BTReversedNode()
{

}

void XE::BTReversedNode::OnStartup()
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

void XE::BTReversedNode::OnUpdate( float dt )
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

BEGIN_META( BTDelayNode )
type->Property( "DetlaTime", &BTDelayNode::_DetlaTime );
END_META()

XE::BTDelayNode::BTDelayNode()
	:_DetlaTime( 0 ), _Dt( 0 )
{

}

XE::BTDelayNode::~BTDelayNode()
{

}

void XE::BTDelayNode::OnStartup()
{
	Super::OnStartup();

	_Dt = _DetlaTime;

	SetStatus( NodeStatus::Running );
}

void XE::BTDelayNode::OnUpdate( float dt )
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
