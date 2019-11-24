#include "Node.h"

#include "Condition.h"
#include "BehaviorTree.h"

USING_XE

BEG_META( Node )
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

void Node::SetHandle( XE::NodeHandle val )
{
	_Handle = val;
}

void XE::Node::SetBehaviorTree( const BehaviorTreePtr & val )
{
	_BehaviorTree = val;
}

const XE::BehaviorTreePtr & XE::Node::GetBehaviorTree() const
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

void XE::Node::Update( XE::float32 dt )
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

void XE::Node::OnUpdate( XE::float32 dt )
{

}

void XE::Node::OnClearup()
{
	SetStatus( NodeStatus::Finish );
}
