#include "DecoratorNode.h"

#include "BehaviorTree.h"



BEG_META( XE::DecoratorNode )
type->Property( "Child", &DecoratorNode::_Child );
END_META()

XE::DecoratorNode::DecoratorNode()
{

}

XE::DecoratorNode::~DecoratorNode()
{

}

XE::NodeHandle XE::DecoratorNode::GetChild() const
{
	return _Child;
}

XE::NodeHandle XE::DecoratorNode::AddChild( const XE::IMetaClassPtr & val )
{
	_Child = GetBehaviorTree()->AddNode( val );
	GetBehaviorTree()->GetNode( _Child )->SetParent( GetHandle() );
	return _Child;
}

void XE::DecoratorNode::RemoveChild()
{
	if( _Child != XE::NodeHandle::Invalid )
	{
		GetBehaviorTree()->RemoveNode( _Child );
		_Child = XE::NodeHandle::Invalid;
	}
}

void XE::DecoratorNode::OnStartup()
{
	Super::OnStartup();

	if( auto node = GetBehaviorTree()->GetNode( GetChild() ) )
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

	if ( GetBehaviorTree()->GetNode( GetChild() )->GetStatus() == XE::NodeStatus::Running )
	{
		GetBehaviorTree()->GetNode( GetChild() )->Update( dt );
	}
}

void XE::DecoratorNode::OnClearup()
{
	Super::OnClearup();

	if( GetBehaviorTree()->GetNode( GetChild() )->GetStatus() != XE::NodeStatus::Finish )
	{
		GetBehaviorTree()->GetNode( GetChild() )->Clearup();
	}
}

void XE::DecoratorNode::OnRemove()
{
	if( _Child != XE::NodeHandle::Invalid )
	{
		GetBehaviorTree()->RemoveNode( _Child );
	}
}

void XE::DecoratorNode::OnResetHandle()
{
	if( _Child != XE::NodeHandle::Invalid )
	{
		GetBehaviorTree()->GetNode( _Child )->SetParent( GetHandle() );
	}
}

BEG_META( XE::RepeatNode )
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

	if( auto node = GetBehaviorTree()->GetNode( GetChild() ) )
	{
		if( node->GetStatus() == XE::NodeStatus::Failure || node->GetStatus() == XE::NodeStatus::Success )
		{
			node->Clearup();

			if( _Count == -1 )
			{
				node->SetStatus( XE::NodeStatus::None );
				node->Startup();
			}
			else
			{
				_Tally--;

				if( _Tally <= 0 )
				{
					SetStatus( XE::NodeStatus::Success );
				}
				else
				{
					node->SetStatus( XE::NodeStatus::None );
					node->Startup();
				}
			}
		}

	}
}

BEG_META( XE::SuccessNode )
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

	switch ( GetBehaviorTree()->GetNode( GetChild() )->GetStatus() )
	{
	case XE::NodeStatus::Failure:
	case XE::NodeStatus::Success:
		SetStatus( XE::NodeStatus::Success );
		break;
	default:
		SetStatus( XE::NodeStatus::Running );
		break;
	}
}

void XE::SuccessNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	switch ( GetBehaviorTree()->GetNode( GetChild() )->GetStatus() )
	{
	case XE::NodeStatus::Failure:
	case XE::NodeStatus::Success:
		SetStatus( XE::NodeStatus::Success );
		break;
	default:
		break;
	}
}

BEG_META( XE::FailureNode )
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

	switch ( GetBehaviorTree()->GetNode( GetChild() )->GetStatus() )
	{
	case XE::NodeStatus::Failure:
	case XE::NodeStatus::Success:
		SetStatus( XE::NodeStatus::Failure );
		break;
	default:
		break;
	}
}

void XE::FailureNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	switch ( GetBehaviorTree()->GetNode( GetChild() )->GetStatus() )
	{
	case XE::NodeStatus::Failure:
	case XE::NodeStatus::Success:
		SetStatus( XE::NodeStatus::Failure );
		break;
	default:
		break;
	}
}

BEG_META( XE::ReversedNode )
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

	switch ( GetBehaviorTree()->GetNode( GetChild() )->GetStatus() )
	{
	case XE::NodeStatus::Failure:
		SetStatus( XE::NodeStatus::Success );
		break;
	case XE::NodeStatus::Success:
		SetStatus( XE::NodeStatus::Failure );
		break;
	default:
		break;
	}
}

void XE::ReversedNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	switch ( GetBehaviorTree()->GetNode( GetChild() )->GetStatus() )
	{
	case XE::NodeStatus::Failure:
		SetStatus( XE::NodeStatus::Success );
		break;
	case XE::NodeStatus::Success:
		SetStatus( XE::NodeStatus::Failure );
		break;
	default:
		break;
	}
}

BEG_META( XE::DelayNode )
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

	SetStatus( XE::NodeStatus::Running );
}

void XE::DelayNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	if (auto node = GetBehaviorTree()->GetNode( GetChild() ) )
	{
		if( node->GetStatus() == XE::NodeStatus::Failure || node->GetStatus() == XE::NodeStatus::Success )
		{
			_Dt -= dt;

			if( _Dt <= XE::Mathf::Epsilon )
			{
				SetStatus( GetBehaviorTree()->GetNode( GetChild() )->GetStatus() );
			}
		}
	}
}
