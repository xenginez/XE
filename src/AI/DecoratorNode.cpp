#include "DecoratorNode.h"

#include "BehaviorTree.h"

USING_XE

BEG_META( DecoratorNode )
type->Property( "Child", &DecoratorNode::_Child );
END_META()

XE::DecoratorNode::DecoratorNode()
{

}

XE::DecoratorNode::~DecoratorNode()
{

}

const XE::NodePtr & XE::DecoratorNode::GetChildNode() const
{
	return GetBehaviorTree()->GetNode( _Child );
}

void DecoratorNode::SetChildNode( const IMetaClassPtr & val )
{
	_Child = GetBehaviorTree()->AddNode( val );
}

void XE::DecoratorNode::OnStartup()
{
	Super::OnStartup();

	if ( auto node = GetChildNode() )
	{
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

	if ( GetChildNode()->GetStatus() == NodeStatus::Running )
	{
		GetChildNode()->Update( dt );
	}
}

void XE::DecoratorNode::OnClearup()
{
	Super::OnClearup();

	if( GetChildNode()->GetStatus() != NodeStatus::Finish )
	{
		GetChildNode()->Clearup();
	}
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

	auto node = GetChildNode();

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
