#include "ConditionNode.h"

#include "BehaviorTree.h"

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
