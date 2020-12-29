#include "AIState.h"

#include "StateMachine.h"

BEG_META( XE::Condition )
type->Property( "NextState", &Condition::_NextState );
END_META()

XE::Condition::Condition()
	:_AIModule( nullptr )
{

}

XE::Condition::~Condition()
{

}

bool XE::Condition::Judgment() const
{
	return false;
}

const XE::AIModulePtr & XE::Condition::GetAIModule() const
{
	return _AIModule;
}

void XE::Condition::SetAIModule( const XE::AIModulePtr & val )
{
	_AIModule = val;
}

XE::AIStateHandle XE::Condition::GetNextStateHandle() const
{
	return _NextState;
}

void XE::Condition::SetNextStateHandle( XE::AIStateHandle val )
{
	_NextState = val;
}

BEG_META( XE::AIState )
type->Property( "Name", &AIState::_Name );
type->Property( "Conditions", &AIState::_Conditions );
type->Property( "Handle", &AIState::_Handle, IMetaProperty::NoDesign );
END_META()

XE::AIState::AIState()
{

}

XE::AIState::~AIState()
{

}

XE::AIStateHandle XE::AIState::GetHandle() const
{
	return _Handle;
}

void XE::AIState::SetHandle( XE::AIStateHandle val )
{
	_Handle = val;
}

const XE::String & XE::AIState::GetName() const
{
	return _Name;
}

void XE::AIState::SetName( const XE::String & val )
{
	_Name = val;
}

const XE::Array< XE::Condition > & XE::AIState::GetConditions() const
{
	return _Conditions;
}

void XE::AIState::SetConditions( const XE::Array< XE::Condition > & val )
{
	_Conditions = val;
}

const XE::StateMachinePtr & XE::AIState::GetStateMachine() const
{
	return _StateMachine;
}

void XE::AIState::SetStateMachine( const XE::StateMachinePtr & val )
{
	_StateMachine = val;
}

void XE::AIState::Startup()
{
	OnStartup();
}

void XE::AIState::Enter()
{
	OnEnter();
}

void XE::AIState::Update( XE::float32 dt )
{
	OnUpdate( dt );
}

void XE::AIState::Quit()
{
	OnQuit();
}

void XE::AIState::Clearup()
{
	OnClearup();
}

void XE::AIState::OnStartup()
{

}

void XE::AIState::OnEnter()
{

}

void XE::AIState::OnUpdate( XE::float32 dt )
{

}

void XE::AIState::OnQuit()
{

}

void XE::AIState::OnClearup()
{

}

BEG_META( XE::SubState )
type->Property( "AIModule", &SubState::_AIModule );
type->Property( "ConnectKeys", &SubState::_ConnectKeys );
END_META()

XE::SubState::SubState()
{

}

XE::SubState::~SubState()
{

}

void XE::SubState::OnStartup()
{
	Super::OnStartup();

	_AIModule->Startup();
}

void XE::SubState::OnEnter()
{
	Super::OnEnter();

	_AIModule->Enter();
}

void XE::SubState::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	for( const auto & key : _ConnectKeys )
	{
		_AIModule->SetKey( key.second, GetStateMachine()->GetKey( key.first ) );
	}

	_AIModule->Update( dt );

	for( const auto & key : _ConnectKeys )
	{
		GetStateMachine()->SetKey( key.first, _AIModule->GetKey( key.second ) );
	}
}

void XE::SubState::OnQuit()
{
	_AIModule->Quit();

	Super::OnQuit();
}

void XE::SubState::OnClearup()
{
	_AIModule->Clearup();

	Super::OnClearup();
}

void XE::SubState::AssetLoad()
{
	_AIModule.AsyncLoad();
}

const XE::Map<XE::BlackboardKey, XE::BlackboardKey> & XE::SubState::GetConnectKeys() const
{
	return _ConnectKeys;
}

void XE::SubState::SetConnectKeys( const XE::Map<XE::BlackboardKey, XE::BlackboardKey> & val )
{
	_ConnectKeys = val;
}
