#include "SubNode.h"

#include "BehaviorTree.h"

USING_XE

BEG_META( SubNode )
type->Property( "SubAI", &SubNode::_SubAI );
END_META()

XE::SubNode::SubNode()
{

}

XE::SubNode::~SubNode()
{

}

void XE::SubNode::OnStartup()
{
	_SubAI->SetGameObject( GetBehaviorTree()->GetGameObject() );

	_SubAI->Startup();
}

void XE::SubNode::OnUpdate( float dt )
{
	_SubAI->Update( dt );
}

void XE::SubNode::OnClearup()
{
	_SubAI->Clearup();
}
