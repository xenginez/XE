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
	_Status = XE::NodeStatus::None;

	OnStartup();
}

void XE::AINode::Enter()
{
	_Status = XE::NodeStatus::Running;

	OnEnter();
}

void XE::AINode::Update( XE::float32 dt )
{
	OnUpdate( dt );
}

void XE::AINode::Quit()
{
	OnQuit();

	_Status = XE::NodeStatus::None;
}

void XE::AINode::Clearup()
{
	OnClearup();
}

void XE::AINode::OnStartup()
{

}

void XE::AINode::OnEnter()
{

}

void XE::AINode::OnUpdate( XE::float32 dt )
{

}

void XE::AINode::OnQuit()
{

}

void XE::AINode::OnClearup()
{

}

BEG_META( XE::SubNode )
type->Property( "AIModule", &SubNode::_AIModule );
type->Property( "ConnectKeys", &SubNode::_ConnectKeys );
END_META()

XE::SubNode::SubNode()
{

}

XE::SubNode::~SubNode()
{

}

void XE::SubNode::OnEnter()
{
	_AIModule->Startup();
}

void XE::SubNode::OnUpdate( XE::float32 dt )
{
	for( const auto & key : _ConnectKeys )
	{
		_AIModule->SetKey( key.second, GetBehaviorTree()->GetKey( key.first ) );
	}

	_AIModule->Update( dt );
	if( _AIModule->IsStopped() )
	{
		SetStatus( NodeStatus::Success );
	}

	for( const auto & key : _ConnectKeys )
	{
		GetBehaviorTree()->SetKey( key.first, _AIModule->GetKey( key.second ) );
	}
}

void XE::SubNode::OnQuit()
{
	_AIModule->Clearup();
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

void XE::CompositeNode::OnEnter()
{
	Super::OnEnter();

	SetStatus( NodeStatus::Running );

	GetBehaviorTree()->PushCompositeNode( this );
}

void XE::CompositeNode::OnQuit()
{
	Super::OnQuit();

	for( auto handle : _Children )
	{
		auto node = GetBehaviorTree()->GetNode( handle );

		if( node->GetStatus() != NodeStatus::None )
		{
			node->Quit();
		}
	}
}

const XE::Array<XE::AINodeHandle> & XE::CompositeNode::GetChildren() const
{
	return _Children;
}

void XE::CompositeNode::SetChildren( const XE::Array<XE::AINodeHandle> & val )
{
	_Children = val;
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

void XE::SequenceNode::OnEnter()
{
	Super::OnEnter();

	_Current = 0;
}

void XE::SequenceNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	const auto & children = GetChildren();

	if( AINodePtr node = GetBehaviorTree()->GetNode( children[_Current] ) )
	{
		switch( node->GetStatus() )
		{
		case XE::NodeStatus::None:
			node->Enter();
		case XE::NodeStatus::Running:
			node->Update( dt );
			break;
		case XE::NodeStatus::Failure:
			SetStatus( XE::NodeStatus::Failure );
			break;
		case XE::NodeStatus::Success:
			_Current != children.size() ? _Current++ : SetStatus( XE::NodeStatus::Success );
		default:
			break;
		}
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

void XE::SelectorNode::OnEnter()
{
	Super::OnEnter();

	_Current = 0;
}

void XE::SelectorNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	const auto & children = GetChildren();

	if( AINodePtr node = GetBehaviorTree()->GetNode( children[_Current] ) )
	{
		auto status = node->GetStatus();
		switch( status )
		{
		case XE::NodeStatus::None:
			node->Enter();
		case XE::NodeStatus::Running:
			node->Update( dt );
			break;
		case XE::NodeStatus::Success:
			SetStatus( XE::NodeStatus::Success );
			break;
		case XE::NodeStatus::Failure:
			_Current != children.size() ? _Current++ : SetStatus( XE::NodeStatus::Failure );
			break;
		default:
			break;
		}
	}
}

BEG_META( XE::ParallelSequenceNode )
END_META()

XE::ParallelSequenceNode::ParallelSequenceNode()
{

}

XE::ParallelSequenceNode::~ParallelSequenceNode()
{

}

void XE::ParallelSequenceNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	int success_count = 0;

	const auto & children = GetChildren();

	for( auto handle : children )
	{
		AINodePtr node = GetBehaviorTree()->GetNode( handle );

		auto status = node->GetStatus();
		switch( status )
		{
		case XE::NodeStatus::None:
			node->Enter();
		case XE::NodeStatus::Running:
			node->Update( dt );
			break;
		case XE::NodeStatus::Failure:
			SetStatus( XE::NodeStatus::Failure );
			break;
		case XE::NodeStatus::Success:
			success_count++;
			break;
		default:
			break;
		}
	}

	if( success_count == children.size() )
	{
		SetStatus( XE::NodeStatus::Success );
	}
}

BEG_META( XE::ParallelSelectorNode )
END_META()

XE::ParallelSelectorNode::ParallelSelectorNode()
{

}

XE::ParallelSelectorNode::~ParallelSelectorNode()
{

}

void XE::ParallelSelectorNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	int failure_count = 0;

	const auto & children = GetChildren();

	for( auto handle : children )
	{
		AINodePtr node = GetBehaviorTree()->GetNode( handle );

		auto status = node->GetStatus();
		switch( status )
		{
		case XE::NodeStatus::None:
			node->Enter();
		case XE::NodeStatus::Running:
			node->Update( dt );
			break;
		case XE::NodeStatus::Success:
			SetStatus( NodeStatus::Success );
			break;
		case XE::NodeStatus::Failure:
			failure_count++;
			break;
		default:
			break;
		}
	}

	if( failure_count == children.size() )
	{
		SetStatus( XE::NodeStatus::Failure );
	}
}

BEG_META( XE::ConditionNode )
type->Property( "Child", &ConditionNode::_Child );
END_META()

XE::ConditionNode::ConditionNode()
	: _CurJudgment( false )
{

}

XE::ConditionNode::~ConditionNode()
{

}

void XE::ConditionNode::OnEnter()
{
	Super::OnEnter();

	bool judgment = Judgment();

	_CurJudgment = judgment;

	if( _CurJudgment )
	{
		auto node = GetBehaviorTree()->GetNode( GetChild() );

		node->Enter();

		switch( node->GetStatus() )
		{
		case XE::NodeStatus::Running:
			SetStatus( XE::NodeStatus::Running );
			GetBehaviorTree()->PushConditionNode( this );
			break;
		case XE::NodeStatus::None:
		case XE::NodeStatus::Failure:
			node->Quit();
			SetStatus( NodeStatus::Failure );
			break;
		case XE::NodeStatus::Success:
			node->Quit();
			SetStatus( NodeStatus::Success );
			break;
		default:
			break;
		}
	}
	else
	{
		SetStatus( XE::NodeStatus::Failure );
	}
}

void XE::ConditionNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	_CurJudgment = Judgment();

	if( !_CurJudgment )
	{
		SetStatus( XE::NodeStatus::Failure );
		return;
	}

	auto node = GetBehaviorTree()->GetNode( GetChild() );
	auto status = node->GetStatus();
	switch( status )
	{
	case XE::NodeStatus::None:
		node->Enter();
	case XE::NodeStatus::Running:
		node->Update( dt );
		break;
	case XE::NodeStatus::Failure:
	case XE::NodeStatus::Success:
		node->Quit();
		SetStatus( status );
		break;
	default:
		break;
	}
}

void XE::ConditionNode::OnQuit()
{
	Super::OnQuit();

	auto node = GetBehaviorTree()->GetNode( GetChild() );
	if( node->GetStatus() != XE::NodeStatus::None )
	{
		node->Quit();
	}
}

bool XE::ConditionNode::JudgmentChanged() const
{
	return Judgment() != _CurJudgment;
}

XE::AINodeHandle XE::ConditionNode::GetChild() const
{
	return _Child;
}

void XE::ConditionNode::SetChild( XE::AINodeHandle val )
{
	_Child = val;
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

void XE::DecoratorNode::OnEnter()
{
	Super::OnEnter();

	auto node = GetBehaviorTree()->GetNode( GetChild() );

	node->Enter();
}

void XE::DecoratorNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	auto node = GetBehaviorTree()->GetNode( GetChild() );

	if( node->GetStatus() == XE::NodeStatus::Running )
	{
		node->Update( dt );
	}
}

void XE::DecoratorNode::OnQuit()
{
	Super::OnQuit();

	auto node = GetBehaviorTree()->GetNode( GetChild() );

	if( node->GetStatus() != XE::NodeStatus::None )
	{
		node->Clearup();
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

void XE::RepeatNode::OnEnter()
{
	Super::OnEnter();

	_Tally = _Count;
}

void XE::RepeatNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );
	
	auto node = GetBehaviorTree()->GetNode( GetChild() );

	if( node->GetStatus() == XE::NodeStatus::Failure || node->GetStatus() == XE::NodeStatus::Success )
	{
		if( _Count == 0 )
		{
			node->Quit();
			node->Enter();
		}
		else if( --_Tally > 0 )
		{
			node->Quit();
			node->Enter();
		}
		else
		{
			SetStatus( node->GetStatus() );
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

void XE::SuccessNode::OnEnter()
{
	Super::OnEnter();

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

void XE::FailureNode::OnEnter()
{
	Super::OnEnter();

	switch( GetBehaviorTree()->GetNode( GetChild() )->GetStatus() )
	{
	case XE::NodeStatus::Failure:
	case XE::NodeStatus::Success:
		SetStatus( XE::NodeStatus::Failure );
		break;
	default:
		SetStatus( XE::NodeStatus::Running );
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

void XE::ReversedNode::OnEnter()
{
	Super::OnEnter();

	switch( GetBehaviorTree()->GetNode( GetChild() )->GetStatus() )
	{
	case XE::NodeStatus::Failure:
		SetStatus( XE::NodeStatus::Success );
		break;
	case XE::NodeStatus::Success:
		SetStatus( XE::NodeStatus::Failure );
		break;
	default:
		SetStatus( XE::NodeStatus::Running );
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

void XE::DelayNode::OnEnter()
{
	Super::OnEnter();

	_Dt = _DetlaTime;

	SetStatus( GetBehaviorTree()->GetNode( GetChild() )->GetStatus() );
}

void XE::DelayNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	auto node = GetBehaviorTree()->GetNode( GetChild() );
	if( node->GetStatus() == XE::NodeStatus::Failure || node->GetStatus() == XE::NodeStatus::Success )
	{
		_Dt += dt;

		if( _Dt > _DetlaTime )
		{
			SetStatus( node->GetStatus() );
		}
	}

}
