#include "SubState.h"

#include "StateMachine.h"

USING_XE

BEGIN_META( SubState )
type->Property( "SubAI", &SubState::_SubAI );
END_META()

XE::SubState::SubState()
{

}

XE::SubState::~SubState()
{

}

void XE::SubState::OnStartup()
{
	_SubAI->SetGameObject( GetStateMachine()->GetGameObject() );

	_SubAI->Startup();
}

void XE::SubState::OnUpdate( float dt )
{
	_SubAI->Update( dt );
}

void XE::SubState::OnClearup()
{
	_SubAI->Clearup();
}
