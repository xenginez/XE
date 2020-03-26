#include "Node.h"

#include "BehaviorTree.h"

USING_XE

BEG_META( Node )
type->Property( "Parent", &Node::_Parent, IMetaProperty::NoDesign );
type->Property( "Handle", &Node::_Handle, IMetaProperty::NoDesign );
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

NodeHandle Node::GetParent() const
{
	return _Parent;
}

void Node::SetParent( NodeHandle val )
{
	_Parent = val;
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
	OnStartup();
}

void XE::Node::Update( XE::float32 dt )
{
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

void Node::OnRemove()
{

}

void Node::OnResetHandle()
{

}

