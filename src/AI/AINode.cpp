#include "AINode.h"

#include "Math/Math.h"
#include "Interface/IFramework.h"
#include "Interface/IAssetsService.h"

#include "BehaviorTree.h"

BEG_META( XE::AINode )
type->Property( "Name", &XE::AINode::_Name );
type->Property( "Parent", &XE::AINode::_Parent, XE::IMetaProperty::NoDesign );
type->Property( "Handle", &XE::AINode::_Handle, XE::IMetaProperty::NoDesign );
END_META()

XE::AINode::AINode()
	:_Status( NodeStatus::None )
{

}

XE::AINode::~AINode()
{

}

XE::AINodeHandle XE::AINode::GetHandle() const
{
	return _Handle;
}

void XE::AINode::SetHandle( XE::AINodeHandle val )
{
	_Handle = val;
}

XE::AINodeHandle XE::AINode::GetParent() const
{
	return _Parent;
}

void XE::AINode::SetParent( XE::AINodeHandle val )
{
	_Parent = val;
}

XE::BehaviorTreePtr XE::AINode::GetBehaviorTree() const
{
	return _BehaviorTree.lock();
}

void XE::AINode::SetBehaviorTree( BehaviorTreePtr val )
{
	_BehaviorTree = val;
}

XE::NodeStatus XE::AINode::GetStatus() const
{
	return _Status;
}

void XE::AINode::SetStatus( NodeStatus val )
{
	_Status = val;
}

const XE::String & XE::AINode::GetName() const
{
	return _Name;
}

void XE::AINode::SetName( const XE::String & val )
{
	_Name = val;
}

void XE::AINode::Startup()
{
	OnStartup();
}

void XE::AINode::Update( XE::float32 dt )
{
	OnUpdate( dt );
}

void XE::AINode::Clearup()
{
	OnClearup();
}

void XE::AINode::OnStartup()
{
	SetStatus( NodeStatus::Running );
}

void XE::AINode::OnUpdate( XE::float32 dt )
{

}

void XE::AINode::OnClearup()
{
	SetStatus( NodeStatus::Finish );
}

BEG_META( XE::SubNode )
type->Property( "SubAI", &SubNode::_SubAIPath );
type->Property( "ConnectKeys", &SubNode::_ConnectKeys );
END_META()

XE::SubNode::SubNode()
{

}

XE::SubNode::~SubNode()
{

}

void XE::SubNode::OnStartup()
{
	_SubAI = DP_CAST<XE::AIModule>( XE::IFramework::GetCurrentFramework()->GetAssetsService()->LoadObject( _SubAIPath ) );

	for( const auto & keys : _ConnectKeys )
	{
		_SubAI->SetKey( keys.second, GetBehaviorTree()->GetKey( keys.first ) );
	}

	_SubAI->Startup();
}

void XE::SubNode::OnUpdate( XE::float32 dt )
{
	for( const auto & key : _ConnectKeys )
	{
		_SubAI->SetKey( key.second, GetBehaviorTree()->GetKey( key.first ) );
	}

	_SubAI->Update( dt );

	for( const auto & key : _ConnectKeys )
	{
		GetBehaviorTree()->SetKey( key.first, _SubAI->GetKey( key.second ) );
	}
}

void XE::SubNode::OnClearup()
{
	_SubAI->Clearup();
}

const XE::Map<XE::BlackboardKey, XE::BlackboardKey> & XE::SubNode::GetConnectKeys() const
{
	return _ConnectKeys;
}

void XE::SubNode::SetConnectKeys( const XE::Map<XE::BlackboardKey, XE::BlackboardKey> & val )
{
	_ConnectKeys = val;
}

BEG_META( XE::ActionNode )
END_META()

XE::ActionNode::ActionNode()
{

}

XE::ActionNode::~ActionNode()
{

}

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
	for( auto handle : _Children )
	{
		auto node = GetBehaviorTree()->GetNode( handle );

		if( node->GetStatus() != NodeStatus::Finish )
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
		if( node->GetStatus() == XE::NodeStatus::None )
		{
			node->Startup();
		}

		if( node->GetStatus() == XE::NodeStatus::Running )
		{
			node->Update( dt );
		}
		else if( node->GetStatus() == XE::NodeStatus::Success || node->GetStatus() == XE::NodeStatus::Failure )
		{
			node->Clearup();
			_Current++;
		}
	}

	if( _Current == children.size() )
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
		if( node->GetStatus() == XE::NodeStatus::None )
		{
			node->Startup();
		}

		if( node->GetStatus() == XE::NodeStatus::Running )
		{
			node->Update( dt );
		}

		if( node->GetStatus() == XE::NodeStatus::Failure )
		{
			node->Clearup();
			_Current++;
		}
		else if( node->GetStatus() == XE::NodeStatus::Success )
		{
			node->Clearup();
			SetStatus( XE::NodeStatus::Success );
			return;
		}
	}

	if( _Current == children.size() )
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

	for( auto handle : children )
	{
		AINodePtr node = GetBehaviorTree()->GetNode( handle );

		if( node->GetStatus() == XE::NodeStatus::None )
		{
			node->Startup();
		}

		if( node->GetStatus() == XE::NodeStatus::Running )
		{
			node->Update( dt );
		}

		if( node->GetStatus() == XE::NodeStatus::Success || node->GetStatus() == XE::NodeStatus::Failure )
		{
			node->Clearup();
		}

		if( node->GetStatus() != XE::NodeStatus::Finish )
		{
			IsFinish = false;
		}
	}

	if( IsFinish )
	{
		SetStatus( XE::NodeStatus::Success );
	}
}

BEG_META( XE::ConditionNode )
type->Property( "Child", &ConditionNode::_Child );
type->Property( "MultiJudgment", &ConditionNode::_MultiJudgment );
END_META()

XE::ConditionNode::ConditionNode()
	:_MultiJudgment( false )
{

}

XE::ConditionNode::~ConditionNode()
{

}

XE::AINodeHandle XE::ConditionNode::GetChild() const
{
	return _Child;
}

void XE::ConditionNode::SetChild( XE::AINodeHandle val )
{
	_Child = val;
}

void XE::ConditionNode::OnStartup()
{
	Super::OnStartup();

	if( ConditionalJudgment() )
	{
		GetBehaviorTree()->GetNode( GetChild() )->Startup();

		SetStatus( XE::NodeStatus::Running );
	}
	else
	{
		SetStatus( XE::NodeStatus::Failure );
	}
}

void XE::ConditionNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	if( _MultiJudgment )
	{
		if( !ConditionalJudgment() )
		{
			return;
		}
	}

	GetBehaviorTree()->GetNode( GetChild() )->Update( dt );
}

void XE::ConditionNode::OnClearup()
{
	Super::OnClearup();

	if( GetBehaviorTree()->GetNode( GetChild() )->GetStatus() != XE::NodeStatus::Finish )
	{
		GetBehaviorTree()->GetNode( GetChild() )->Clearup();
	}
}

BEG_META( XE::DecoratorNode )
type->Property( "Child", &DecoratorNode::_Child );
END_META()

XE::DecoratorNode::DecoratorNode()
{

}

XE::DecoratorNode::~DecoratorNode()
{

}

XE::AINodeHandle XE::DecoratorNode::GetChild() const
{
	return _Child;
}

void XE::DecoratorNode::SetChild( XE::AINodeHandle val )
{
	_Child = val;
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

	if( GetBehaviorTree()->GetNode( GetChild() )->GetStatus() == XE::NodeStatus::Running )
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

	switch( GetBehaviorTree()->GetNode( GetChild() )->GetStatus() )
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

	switch( GetBehaviorTree()->GetNode( GetChild() )->GetStatus() )
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

	switch( GetBehaviorTree()->GetNode( GetChild() )->GetStatus() )
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

	switch( GetBehaviorTree()->GetNode( GetChild() )->GetStatus() )
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

	switch( GetBehaviorTree()->GetNode( GetChild() )->GetStatus() )
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

	switch( GetBehaviorTree()->GetNode( GetChild() )->GetStatus() )
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

	if( auto node = GetBehaviorTree()->GetNode( GetChild() ) )
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
