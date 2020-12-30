#include "Node.h"

#include "BehaviorTree.h"

BEG_META( AI::Node )
type->Property( "Name", &AI::Node::_Name );
type->Property( "Parent", &AI::Node::_Parent, XE::IMetaProperty::NoDesign );
type->Property( "Handle", &AI::Node::_Handle, XE::IMetaProperty::NoDesign );
END_META()

AI::Node::Node()
	:_Status( AINodeStatus::NONE )
{

}

AI::Node::~Node()
{

}

AI::AINodeType AI::Node::GetType() const
{
	return _Type;
}

void AI::Node::SetType( AI::AINodeType val )
{
	_Type = val;
}

AI::NodeHandle AI::Node::GetHandle() const
{
	return _Handle;
}

void AI::Node::SetHandle( AI::NodeHandle val )
{
	_Handle = val;
}

AI::NodeHandle AI::Node::GetParent() const
{
	return _Parent;
}

void AI::Node::SetParent( AI::NodeHandle val )
{
	_Parent = val;
}

AI::BehaviorTreePtr AI::Node::GetBehaviorTree() const
{
	return _BehaviorTree.lock();
}

void AI::Node::SetBehaviorTree( BehaviorTreePtr val )
{
	_BehaviorTree = val;
}

AI::AINodeStatus AI::Node::GetStatus() const
{
	return _Status;
}

void AI::Node::SetStatus( AINodeStatus val )
{
	_Status = val;
}

const XE::String & AI::Node::GetName() const
{
	return _Name;
}

void AI::Node::SetName( const XE::String & val )
{
	_Name = val;
}

void AI::Node::Startup()
{
	_Status = AI::AINodeStatus::NONE;

	OnStartup();
}

void AI::Node::Enter()
{
	_Status = AI::AINodeStatus::RUNNING;

	OnEnter();
}

void AI::Node::Update( XE::float32 dt )
{
	OnUpdate( dt );
}

void AI::Node::Quit()
{
	OnQuit();

	_Status = AI::AINodeStatus::NONE;
}

void AI::Node::Clearup()
{
	OnClearup();
}

void AI::Node::OnStartup()
{

}

void AI::Node::OnEnter()
{

}

void AI::Node::OnUpdate( XE::float32 dt )
{

}

void AI::Node::OnQuit()
{

}

void AI::Node::OnClearup()
{

}

BEG_META( AI::SubNode )
type->Property( "AIModule", &AI::SubNode::_AIModule );
type->Property( "ConnectKeys", &AI::SubNode::_ConnectKeys );
END_META()

AI::SubNode::SubNode()
{
	SetType( AI::AINodeType::SUB_NODE );
}

AI::SubNode::~SubNode()
{

}

void AI::SubNode::OnStartup()
{
	Super::OnStartup();

	_AIModule->Startup();
}

void AI::SubNode::OnEnter()
{
	Super::OnEnter();

	_AIModule->Enter();
}

void AI::SubNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	for( const auto & key : _ConnectKeys )
	{
		_AIModule->SetKey( key.second, GetBehaviorTree()->GetKey( key.first ) );
	}

	_AIModule->Update( dt );
	if( _AIModule->IsStopped() )
	{
		SetStatus( AINodeStatus::SUCCESS );
	}

	for( const auto & key : _ConnectKeys )
	{
		GetBehaviorTree()->SetKey( key.first, _AIModule->GetKey( key.second ) );
	}
}

void AI::SubNode::OnQuit()
{
	Super::OnQuit();

	_AIModule->Quit();
}

void AI::SubNode::OnClearup()
{
	Super::OnClearup();

	_AIModule->Clearup();
}

const XE::Map<AI::BlackboardKey, AI::BlackboardKey> & AI::SubNode::GetConnectKeys() const
{
	return _ConnectKeys;
}

void AI::SubNode::SetConnectKeys( const XE::Map<AI::BlackboardKey, AI::BlackboardKey> & val )
{
	_ConnectKeys = val;
}

BEG_META( AI::ActionNode )
END_META()

AI::ActionNode::ActionNode()
{
	SetType( AI::AINodeType::ACTION_NODE );
}

AI::ActionNode::~ActionNode()
{

}

BEG_META( AI::CompositeNode )
type->Property( "Children", &AI::CompositeNode::_Children );
END_META()

AI::CompositeNode::CompositeNode()
{
	SetType( AI::AINodeType::COMPOSITE_NODE );
}

AI::CompositeNode::~CompositeNode()
{

}

void AI::CompositeNode::OnEnter()
{
	Super::OnEnter();

	SetStatus( AINodeStatus::RUNNING );

	GetBehaviorTree()->PushCompositeNode( this );
}

void AI::CompositeNode::OnQuit()
{
	Super::OnQuit();

	for( auto handle : _Children )
	{
		auto node = GetBehaviorTree()->GetNode( handle );

		if( node->GetStatus() != AINodeStatus::NONE )
		{
			node->Quit();
		}
	}
}

const XE::Array<AI::NodeHandle> & AI::CompositeNode::GetChildren() const
{
	return _Children;
}

void AI::CompositeNode::SetChildren( const XE::Array<AI::NodeHandle> & val )
{
	_Children = val;
}

BEG_META( AI::SequenceNode )
END_META()

AI::SequenceNode::SequenceNode()
	:_Current( 0 )
{

}

AI::SequenceNode::~SequenceNode()
{

}

void AI::SequenceNode::OnEnter()
{
	Super::OnEnter();

	_Current = 0;
}

void AI::SequenceNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	const auto & children = GetChildren();

	if( AI::NodePtr node = GetBehaviorTree()->GetNode( children[_Current] ) )
	{
		switch( node->GetStatus() )
		{
		case AI::AINodeStatus::NONE:
			node->Enter();
		case AI::AINodeStatus::RUNNING:
			node->Update( dt );
			break;
		case AI::AINodeStatus::FAILURE:
			SetStatus( AI::AINodeStatus::FAILURE );
			break;
		case AI::AINodeStatus::SUCCESS:
			_Current != children.size() ? _Current++ : SetStatus( AI::AINodeStatus::SUCCESS );
		default:
			break;
		}
	}
}

BEG_META( AI::SelectorNode )
END_META()

AI::SelectorNode::SelectorNode()
	:_Current( 0 )
{

}

AI::SelectorNode::~SelectorNode()
{

}

void AI::SelectorNode::OnEnter()
{
	Super::OnEnter();

	_Current = 0;
}

void AI::SelectorNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	const auto & children = GetChildren();

	if( AI::NodePtr node = GetBehaviorTree()->GetNode( children[_Current] ) )
	{
		auto status = node->GetStatus();
		switch( status )
		{
		case AI::AINodeStatus::NONE:
			node->Enter();
		case AI::AINodeStatus::RUNNING:
			node->Update( dt );
			break;
		case AI::AINodeStatus::SUCCESS:
			SetStatus( AI::AINodeStatus::SUCCESS );
			break;
		case AI::AINodeStatus::FAILURE:
			_Current != children.size() ? _Current++ : SetStatus( AI::AINodeStatus::FAILURE );
			break;
		default:
			break;
		}
	}
}

BEG_META( AI::RandomSelectorNode )
type->Property( "Seed", &AI::RandomSelectorNode::_Seed );
END_META()

AI::RandomSelectorNode::RandomSelectorNode()
	:_Seed( 0 ), _Current( 0 )
{

}

AI::RandomSelectorNode::~RandomSelectorNode()
{

}

void AI::RandomSelectorNode::OnEnter()
{
	Super::OnEnter();

	_Random = std::default_random_engine( _Seed );
	_Uniform = std::uniform_int_distribution<XE::uint64>( 0, GetChildren().size() );

	_Current = _Uniform( _Random );
}

void AI::RandomSelectorNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	const auto & children = GetChildren();

	if( AI::NodePtr node = GetBehaviorTree()->GetNode( children[_Current] ) )
	{
		auto status = node->GetStatus();
		switch( status )
		{
		case AI::AINodeStatus::NONE:
			node->Enter();
		case AI::AINodeStatus::RUNNING:
			node->Update( dt );
			break;
		case AI::AINodeStatus::SUCCESS:
			SetStatus( AI::AINodeStatus::SUCCESS );
			break;
		case AI::AINodeStatus::FAILURE:
			_Current != children.size() ? _Current = _Uniform( _Random ) : SetStatus( AI::AINodeStatus::FAILURE );
			break;
		default:
			break;
		}
	}
}

BEG_META( AI::ParallelSequenceNode )
END_META()

AI::ParallelSequenceNode::ParallelSequenceNode()
{

}

AI::ParallelSequenceNode::~ParallelSequenceNode()
{

}

void AI::ParallelSequenceNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	int success_count = 0;

	const auto & children = GetChildren();

	for( auto handle : children )
	{
		AI::NodePtr node = GetBehaviorTree()->GetNode( handle );

		auto status = node->GetStatus();
		switch( status )
		{
		case AI::AINodeStatus::NONE:
			node->Enter();
		case AI::AINodeStatus::RUNNING:
			node->Update( dt );
			break;
		case AI::AINodeStatus::FAILURE:
			SetStatus( AI::AINodeStatus::FAILURE );
			break;
		case AI::AINodeStatus::SUCCESS:
			success_count++;
			break;
		default:
			break;
		}
	}

	if( success_count == children.size() )
	{
		SetStatus( AI::AINodeStatus::SUCCESS );
	}
}

BEG_META( AI::ParallelSelectorNode )
END_META()

AI::ParallelSelectorNode::ParallelSelectorNode()
{

}

AI::ParallelSelectorNode::~ParallelSelectorNode()
{

}

void AI::ParallelSelectorNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	int failure_count = 0;

	const auto & children = GetChildren();

	for( auto handle : children )
	{
		AI::NodePtr node = GetBehaviorTree()->GetNode( handle );

		auto status = node->GetStatus();
		switch( status )
		{
		case AI::AINodeStatus::NONE:
			node->Enter();
		case AI::AINodeStatus::RUNNING:
			node->Update( dt );
			break;
		case AI::AINodeStatus::SUCCESS:
			SetStatus( AINodeStatus::SUCCESS );
			break;
		case AI::AINodeStatus::FAILURE:
			failure_count++;
			break;
		default:
			break;
		}
	}

	if( failure_count == children.size() )
	{
		SetStatus( AI::AINodeStatus::FAILURE );
	}
}

BEG_META( AI::ConditionNode )
type->Property( "Child", &AI::ConditionNode::_Child );
END_META()

AI::ConditionNode::ConditionNode()
	: _CurJudgment( false )
{
	SetType( AI::AINodeType::CONDITION_NODE );
}

AI::ConditionNode::~ConditionNode()
{

}

void AI::ConditionNode::OnEnter()
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
		case AI::AINodeStatus::RUNNING:
			SetStatus( AI::AINodeStatus::RUNNING );
			GetBehaviorTree()->PushConditionNode( this );
			break;
		case AI::AINodeStatus::NONE:
		case AI::AINodeStatus::FAILURE:
			node->Quit();
			SetStatus( AINodeStatus::FAILURE );
			break;
		case AI::AINodeStatus::SUCCESS:
			node->Quit();
			SetStatus( AINodeStatus::SUCCESS );
			break;
		default:
			break;
		}
	}
	else
	{
		SetStatus( AI::AINodeStatus::FAILURE );
	}
}

void AI::ConditionNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	_CurJudgment = Judgment();

	if( !_CurJudgment )
	{
		SetStatus( AI::AINodeStatus::FAILURE );
		return;
	}

	auto node = GetBehaviorTree()->GetNode( GetChild() );
	auto status = node->GetStatus();
	switch( status )
	{
	case AI::AINodeStatus::NONE:
		node->Enter();
	case AI::AINodeStatus::RUNNING:
		node->Update( dt );
		break;
	case AI::AINodeStatus::FAILURE:
	case AI::AINodeStatus::SUCCESS:
		node->Quit();
		SetStatus( status );
		break;
	default:
		break;
	}
}

void AI::ConditionNode::OnQuit()
{
	Super::OnQuit();

	auto node = GetBehaviorTree()->GetNode( GetChild() );
	if( node->GetStatus() != AI::AINodeStatus::NONE )
	{
		node->Quit();
	}
}

bool AI::ConditionNode::JudgmentChanged() const
{
	return Judgment() != _CurJudgment;
}

AI::NodeHandle AI::ConditionNode::GetChild() const
{
	return _Child;
}

void AI::ConditionNode::SetChild( AI::NodeHandle val )
{
	_Child = val;
}

BEG_META( AI::DecoratorNode )
type->Property( "Child", &AI::DecoratorNode::_Child );
END_META()

AI::DecoratorNode::DecoratorNode()
{
	SetType( AI::AINodeType::DECORATOR_NODE );
}

AI::DecoratorNode::~DecoratorNode()
{

}

AI::NodeHandle AI::DecoratorNode::GetChild() const
{
	return _Child;
}

void AI::DecoratorNode::SetChild( AI::NodeHandle val )
{
	_Child = val;
}

void AI::DecoratorNode::OnEnter()
{
	Super::OnEnter();

	auto node = GetBehaviorTree()->GetNode( GetChild() );

	node->Enter();
}

void AI::DecoratorNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	auto node = GetBehaviorTree()->GetNode( GetChild() );

	if( node->GetStatus() == AI::AINodeStatus::RUNNING )
	{
		node->Update( dt );
	}
}

void AI::DecoratorNode::OnQuit()
{
	Super::OnQuit();

	auto node = GetBehaviorTree()->GetNode( GetChild() );

	if( node->GetStatus() != AI::AINodeStatus::NONE )
	{
		node->Clearup();
	}
}

BEG_META( AI::RepeatNode )
type->Property( "Count", &AI::RepeatNode::_Count );
END_META()

AI::RepeatNode::RepeatNode()
	:_Count( -1 ), _Tally( -1 )
{

}

AI::RepeatNode::~RepeatNode()
{

}

void AI::RepeatNode::OnEnter()
{
	Super::OnEnter();

	_Tally = _Count;
}

void AI::RepeatNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );
	
	auto node = GetBehaviorTree()->GetNode( GetChild() );

	if( node->GetStatus() == AI::AINodeStatus::FAILURE || node->GetStatus() == AI::AINodeStatus::SUCCESS )
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

BEG_META( AI::SuccessNode )
END_META()

AI::SuccessNode::SuccessNode()
{

}

AI::SuccessNode::~SuccessNode()
{

}

void AI::SuccessNode::OnEnter()
{
	Super::OnEnter();

	switch( GetBehaviorTree()->GetNode( GetChild() )->GetStatus() )
	{
	case AI::AINodeStatus::FAILURE:
	case AI::AINodeStatus::SUCCESS:
		SetStatus( AI::AINodeStatus::SUCCESS );
		break;
	default:
		SetStatus( AI::AINodeStatus::RUNNING );
		break;
	}
}

void AI::SuccessNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	switch( GetBehaviorTree()->GetNode( GetChild() )->GetStatus() )
	{
	case AI::AINodeStatus::FAILURE:
	case AI::AINodeStatus::SUCCESS:
		SetStatus( AI::AINodeStatus::SUCCESS );
		break;
	default:
		break;
	}
}

BEG_META( AI::FailureNode )
END_META()

AI::FailureNode::FailureNode()
{

}

AI::FailureNode::~FailureNode()
{

}

void AI::FailureNode::OnEnter()
{
	Super::OnEnter();

	switch( GetBehaviorTree()->GetNode( GetChild() )->GetStatus() )
	{
	case AI::AINodeStatus::FAILURE:
	case AI::AINodeStatus::SUCCESS:
		SetStatus( AI::AINodeStatus::FAILURE );
		break;
	default:
		SetStatus( AI::AINodeStatus::RUNNING );
		break;
	}
}

void AI::FailureNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	switch( GetBehaviorTree()->GetNode( GetChild() )->GetStatus() )
	{
	case AI::AINodeStatus::FAILURE:
	case AI::AINodeStatus::SUCCESS:
		SetStatus( AI::AINodeStatus::FAILURE );
		break;
	default:
		break;
	}
}

BEG_META( AI::ReversedNode )
END_META()

AI::ReversedNode::ReversedNode()
{

}

AI::ReversedNode::~ReversedNode()
{

}

void AI::ReversedNode::OnEnter()
{
	Super::OnEnter();

	switch( GetBehaviorTree()->GetNode( GetChild() )->GetStatus() )
	{
	case AI::AINodeStatus::FAILURE:
		SetStatus( AI::AINodeStatus::SUCCESS );
		break;
	case AI::AINodeStatus::SUCCESS:
		SetStatus( AI::AINodeStatus::FAILURE );
		break;
	default:
		SetStatus( AI::AINodeStatus::RUNNING );
		break;
	}
}

void AI::ReversedNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	switch( GetBehaviorTree()->GetNode( GetChild() )->GetStatus() )
	{
	case AI::AINodeStatus::FAILURE:
		SetStatus( AI::AINodeStatus::SUCCESS );
		break;
	case AI::AINodeStatus::SUCCESS:
		SetStatus( AI::AINodeStatus::FAILURE );
		break;
	default:
		break;
	}
}

BEG_META( AI::DelayNode )
type->Property( "DetlaTime", &AI::DelayNode::_DetlaTime );
END_META()

AI::DelayNode::DelayNode()
	:_DetlaTime( 0 ), _Dt( 0 )
{

}

AI::DelayNode::~DelayNode()
{

}

void AI::DelayNode::OnEnter()
{
	Super::OnEnter();

	_Dt = _DetlaTime;

	SetStatus( GetBehaviorTree()->GetNode( GetChild() )->GetStatus() );
}

void AI::DelayNode::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	auto node = GetBehaviorTree()->GetNode( GetChild() );
	if( node->GetStatus() == AI::AINodeStatus::FAILURE || node->GetStatus() == AI::AINodeStatus::SUCCESS )
	{
		_Dt += dt;

		if( _Dt > _DetlaTime )
		{
			SetStatus( node->GetStatus() );
		}
	}

}
