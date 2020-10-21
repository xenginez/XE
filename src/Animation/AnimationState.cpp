#include "AnimationState.h"

#include "Math/Mathf.h"

BEG_META( XE::AnimationState )
type->Property( "Loop", &XE::AnimationState::_Loop );
type->Property( "Speed", &XE::AnimationState::_Speed );
type->Property( "Events", &XE::AnimationState::_Events, XE::IMetaProperty::NoDesign );
END_META()

XE::AnimationState::AnimationState()
{

}

XE::AnimationState::~AnimationState()
{

}

bool XE::AnimationState::GetLoop() const
{
	return _Loop;
}

void XE::AnimationState::SetLoop( bool val )
{
	_Loop = val;
}

XE::float32 XE::AnimationState::GetTime() const
{
	return _Time;
}

void XE::AnimationState::SetTime( XE::float32 val )
{
	_Time = val;
}

XE::float32 XE::AnimationState::GetSpeed() const
{
	return _Speed;
}

void XE::AnimationState::SetSpeed( XE::float32 val )
{
	_Speed = val;
}

void XE::AnimationState::AddAnimationEvent( const XE::AnimationEvent & val )
{
	_Events.push_back( val );
}

void XE::AnimationState::RemoveAnimationEvent( XE::float32 val )
{
	for( auto it = _Events.begin(); it != _Events.end(); ++it )
	{
		if( XE::Mathf::Abs( it->GetKey() - val ) < XE::Mathf::Nan )
		{
			_Events.erase( it );
			break;
		}
	}
}

const XE::Array< XE::AnimationEvent > & XE::AnimationState::GetAnimationEvents() const
{
	return _Events;
}

void XE::AnimationState::OnStartup()
{
	Super::OnStartup();
}

void XE::AnimationState::OnUpdate( XE::float32 dt )
{
	Super::OnUpdate( dt );

	_Time += dt * _Speed;

	for( auto & event : _Events )
	{
		if( !event.IsProcessed() )
		{
			if( XE::Mathf::Abs( event.GetKey() - _Time ) < XE::Mathf::Nan )
			{
				// TODO: Å×ÊÂ¼þ

				event.Processed();
			}
		}
	}
}

void XE::AnimationState::OnClearup()
{
	_Time = 0.0f;

	for( auto & event : _Events )
	{
		event.Reset();
	}

	Super::OnClearup();
}
