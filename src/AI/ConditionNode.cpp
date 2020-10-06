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

XE::NodeHandle XE::ConditionNode::GetChild() const
{
	return _Child;
}

XE::NodeHandle XE::ConditionNode::AddChild( const XE::IMetaClassPtr & val )
{
	_Child = GetBehaviorTree()->AddNode( val );
	GetBehaviorTree()->GetNode( _Child )->SetParent( GetHandle() );
	return _Child;
}

void XE::ConditionNode::RemoveChild()
{
	if( _Child != XE::NodeHandle::Invalid )
	{
		GetBehaviorTree()->RemoveNode( _Child );
		_Child = XE::NodeHandle::Invalid;
	}
}

void XE::ConditionNode::OnStartup()
{
	Super::OnStartup();

	if( ConditionalJudgment() )
	{
		GetBehaviorTree()->GetNode( GetChild() )->Startup();

		SetStatus( NodeStatus::Running );
	}
	else
	{
		SetStatus( NodeStatus::Failure );
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

void XE::ConditionNode::OnRemove()
{
	if( _Child != NodeHandle::Invalid )
	{
		GetBehaviorTree()->RemoveNode( _Child );
	}
}

void XE::ConditionNode::OnResetHandle()
{
	if( _Child != NodeHandle::Invalid )
	{
		GetBehaviorTree()->GetNode( _Child )->SetParent( GetHandle() );
	}
}
