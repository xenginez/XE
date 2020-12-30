#include "State.h"

#include "StateMachine.h"

BEG_META( AI::Condition )
type->Property( "NextState", &AI::Condition::_NextState );
END_META()

AI::Condition::Condition()
	:_AIModule( nullptr )
{

}

AI::Condition::~Condition()
{

}

bool AI::Condition::Judgment() const
{
	return false;
}

const AI::ModulePtr & AI::Condition::GetAIModule() const
{
	return _AIModule;
}

void AI::Condition::SetAIModule( const AI::ModulePtr & val )
{
	_AIModule = val;
}

AI::StateHandle AI::Condition::GetNextStateHandle() const
{
	return _NextState;
}

void AI::Condition::SetNextStateHandle( AI::StateHandle val )
{
	_NextState = val;
}

BEG_META( AI::State )
type->Property( "Name", &AI::State::_Name );
type->Property( "Conditions", &AI::State::_Conditions );
type->Property( "Handle", &AI::State::_Handle, XE::IMetaProperty::NoDesign );
END_META()

AI::State::State()
{

}

AI::State::~State()
{

}

AI::StateHandle AI::State::GetHandle() const
{
	return _Handle;
}

void AI::State::SetHandle( AI::StateHandle val )
{
	_Handle = val;
}

const XE::String & AI::State::GetName() const
{
	return _Name;
}

void AI::State::SetName( const XE::String & val )
{
	_Name = val;
}

const XE::Array< AI::Condition > & AI::State::GetConditions() const
{
	return _Conditions;
}

void AI::State::SetConditions( const XE::Array< AI::Condition > & val )
{
	_Conditions = val;
}

const AI::StateMachinePtr & AI::State::GetStateMachine() const
{
	return _StateMachine;
}

void AI::State::SetStateMachine( const AI::StateMachinePtr & val )
{
	_StateMachine = val;
}

void AI::State::Startup()
{
	OnStartup();
}

void AI::State::Enter()
{
	OnEnter();
}

void AI::State::Update( XE::float32 dt )
{
	OnUpdate( dt );
}

void AI::State::Quit()
{
	OnQuit();
}

void AI::State::Clearup()
{
	OnClearup();
}

void AI::State::OnStartup()
{

}

void AI::State::OnEnter()
{

}

void AI::State::OnUpdate( XE::float32 dt )
{

}

void AI::State::OnQuit()
{

}

void AI::State::OnClearup()
{

}

BEG_META( AI::SubState )
type->Property( "AIModule", &AI::SubState::_AIModule );
type->Property( "ConnectKeys", &AI::SubState::_ConnectKeys );
END_META()

AI::SubState::SubState()
{

}

AI::SubState::~SubState()
{

}

void AI::SubState::OnStartup()
{
	Super::OnStartup();

	_AIModule->Startup();
}

void AI::SubState::OnEnter()
{
	Super::OnEnter();

	_AIModule->Enter();
}

void AI::SubState::OnUpdate( XE::float32 dt )
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

void AI::SubState::OnQuit()
{
	_AIModule->Quit();

	Super::OnQuit();
}

void AI::SubState::OnClearup()
{
	_AIModule->Clearup();

	Super::OnClearup();
}

void AI::SubState::AssetLoad()
{
	_AIModule.AsyncLoad();
}

const XE::Map<AI::BlackboardKey, AI::BlackboardKey> & AI::SubState::GetConnectKeys() const
{
	return _ConnectKeys;
}

void AI::SubState::SetConnectKeys( const XE::Map<AI::BlackboardKey, AI::BlackboardKey> & val )
{
	_ConnectKeys = val;
}
