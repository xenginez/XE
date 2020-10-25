#include "State.h"

#include <Interface/IFramework.h>
#include <Interface/IAssetsService.h>

#include "Condition.h"
#include "StateMachine.h"

BEG_META( XE::State )
type->Property( "Handle", &State::_Handle, IMetaProperty::NoDesign );
type->Property( "Conditions", &State::_Conditions );
END_META()

XE::State::State()
{

}

XE::State::~State()
{

}

XE::StateHandle XE::State::GetHandle() const
{
	return _Handle;
}

void XE::State::AddConditions( const XE::ConditionPtr & val )
{
	_Conditions.push_back( val );
}

void XE::State::RemoveConditions( const XE::ConditionPtr & val )
{
	for( auto it = _Conditions.begin(); it != _Conditions.end(); ++it )
	{
		if( ( *it ) == val )
		{
			_Conditions.erase( it );
			return;
		}
	}
}

const XE::Array< XE::ConditionPtr > & XE::State::GetConditions() const
{
	return _Conditions;
}

const XE::StateMachinePtr & XE::State::GetStateMachine() const
{
	return _StateMachine;
}

void XE::State::SetStateMachine( const XE::StateMachinePtr & val )
{
	_StateMachine = val;
}

void XE::State::Startup()
{
	OnStartup();
}

void XE::State::Update( XE::float32 dt )
{
	OnUpdate( dt );
}

void XE::State::Clearup()
{
	OnClearup();
}

void XE::State::OnStartup()
{

}

void XE::State::OnUpdate( XE::float32 dt )
{

}

void XE::State::OnClearup()
{

}

BEG_META( XE::SubState )
type->Property( "SubAI", &SubState::_SubAIPath );
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
	_SubAI = DP_CAST<XE::AIModule>( XE::IFramework::GetCurrentFramework()->GetAssetsService()->LoadObject( _SubAIPath ) );

	for( const auto & keys : _ConnectKeys )
	{
		_SubAI->SetKey( keys.second, GetStateMachine()->GetKey( keys.first ) );
	}

	_SubAI->Startup();
}

void XE::SubState::OnUpdate( XE::float32 dt )
{
	for( const auto & key : _ConnectKeys )
	{
		_SubAI->SetKey( key.second, GetStateMachine()->GetKey( key.first ) );
	}

	_SubAI->Update( dt );

	for( const auto & key : _ConnectKeys )
	{
		GetStateMachine()->SetKey( key.first, _SubAI->GetKey( key.second ) );
	}
}

void XE::SubState::OnClearup()
{
	_SubAI->Clearup();
}

const XE::Map<XE::BlackboardKey, XE::BlackboardKey> & XE::SubState::GetConnectKeys() const
{
	return _ConnectKeys;
}

void XE::SubState::SetConnectKeys( const XE::Map<XE::BlackboardKey, XE::BlackboardKey> & val )
{
	_ConnectKeys = val;
}
