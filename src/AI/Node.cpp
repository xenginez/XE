#include "Node.h"

#include "BehaviorTree.h"
#include "Condition.h"

USING_XE

BEGIN_META( Node )
type->Property( "PreCondition", &Node::_PreCondition );
type->Property( "ConditionStatus", &Node::_ConditionStatus );
END_META()

XE::Node::Node()
	:_Status( NodeStatus::None ), _BehaviorTree( nullptr )
{

}

XE::Node::~Node()
{

}

XE::NodeHandle XE::Node::GetHandle() const
{
	return _Handle;
}

XE::BlackBoard * XE::Node::GetBlackBoard() const
{
	return _BehaviorTree->GetBlackBoard();
}

void XE::Node::SetBehaviorTree( BehaviorTree * val )
{
	_BehaviorTree = val;
}

XE::BehaviorTree * XE::Node::GetBehaviorTree() const
{
	return _BehaviorTree;
}

XE::NodeStatus XE::Node::GetStatus() const
{
	return _Status;
}

void XE::Node::SetStatus( NodeStatus val )
{
	_Status = val;
}

void XE::Node::Startup()
{
	if ( _PreCondition )
	{
		_PreCondition->SetAIModule( GetBehaviorTree() );

		if ( !_PreCondition->Judgment() )
		{
			return;
		}
	}

	OnStartup();
}

void XE::Node::Update( float dt )
{
	if ( _PreCondition && _ConditionStatus == ConditionStatus::Always )
	{
		if ( !_PreCondition->Judgment() )
		{
			SetStatus( NodeStatus::Failure );

			return;
		}
	}

	OnUpdate( dt );
}

void XE::Node::Clearup()
{
	OnClearup();
}

void XE::Node::OnStartup()
{
	SetStatus( NodeStatus::Running );
}

void XE::Node::OnUpdate( float dt )
{

}

void XE::Node::OnClearup()
{
	SetStatus( NodeStatus::Finish );
}
