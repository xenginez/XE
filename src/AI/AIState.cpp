#include "AIState.h"

#include <Interface/IFramework.h>
#include <Interface/IAssetsService.h>

#include "Condition.h"
#include "StateMachine.h"

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

const XE::Array< XE::ConditionPtr > & XE::AIState::GetConditions() const
{
	return _Conditions;
}

void XE::AIState::SetConditions( const XE::Array< XE::ConditionPtr > & val )
{
	_Conditions = val;
}

XE::StateMachinePtr XE::AIState::GetStateMachine() const
{
	return _StateMachine.lock();
}

void XE::AIState::SetStateMachine( XE::StateMachinePtr val )
{
	_StateMachine = val;
}

void XE::AIState::Startup()
{
	OnStartup();
}

void XE::AIState::Update( XE::float32 dt )
{
	OnUpdate( dt );
}

void XE::AIState::Clearup()
{
	OnClearup();
}

void XE::AIState::OnStartup()
{

}

void XE::AIState::OnUpdate( XE::float32 dt )
{

}

void XE::AIState::OnClearup()
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
