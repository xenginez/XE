#include "SubState.h"

#include "StateMachine.h"

USING_XE

BEG_META( SubState )
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
	_SubAI->Startup();
}

void XE::SubState::OnUpdate( XE::float32 dt )
{
	_SubAI->Update( dt );
}

void XE::SubState::OnClearup()
{
	_SubAI->Clearup();
}
