#include "EventService.h"

#include <tbb/concurrent_vector.h>
#include <tbb/concurrent_hash_map.h>
#include <tbb/concurrent_priority_queue.h>

BEG_META( XE::EventService )
END_META()

struct XEPTimeEvent
{
	XE::EventPtr _Event;
	XE::float32 _Duration;
	XE::float32 _StartTime;
};
template<> struct std::less<XEPTimeEvent>
{
	typedef XEPTimeEvent first_argument_type;
	typedef XEPTimeEvent second_argument_type;
	typedef bool result_type;

	constexpr bool operator()( const first_argument_type& _Left, const second_argument_type& _Right ) const
	{
		return( ( _Left._StartTime + _Left._Duration ) < ( _Right._StartTime + _Right._Duration ) );
	}
};

struct XEPFrameEvent
{
	XE::EventPtr _Event;
	XE::uint64 _Frame;
	XE::uint64 _StartFrame;
};
template<> struct std::less<XEPFrameEvent>
{
	typedef XEPFrameEvent first_argument_type;
	typedef XEPFrameEvent second_argument_type;
	typedef bool result_type;

	constexpr bool operator()( const first_argument_type& _Left, const second_argument_type& _Right ) const
	{
		return( ( _Left._StartFrame + _Left._Frame ) < ( _Right._StartFrame + _Right._Frame ) );
	}
};

struct XE::EventService::Private
{
	using ListenerMap = tbb::concurrent_hash_map<XE::EventHandle, tbb::concurrent_vector<IEventService::ListenerType>>;

	ListenerMap _Listeners;
	tbb::concurrent_priority_queue<XEPTimeEvent> _TimeEvents;
	tbb::concurrent_priority_queue<XEPFrameEvent> _FrameEvents;
};

XE::EventService::EventService()
	:_p( new Private )
{

}

XE::EventService::~EventService()
{
	delete _p;
}

void XE::EventService::Prepare()
{

}

bool XE::EventService::Startup()
{
	return true;
}

void XE::EventService::Update()
{
	ProcessTimeEvent();

	ProcessFrameEvent();
}

void XE::EventService::Clearup()
{
	_p->_Listeners.clear();
	_p->_TimeEvents.clear();
	_p->_FrameEvents.clear();
}

void XE::EventService::PostEvent( XE::EventPtr val )
{
	if( val->recver )
	{
		val->recver->ProcessEvent( val );
		if( val->accept )
		{
			return;
		}
	}

	Private::ListenerMap::accessor accessor;
	if ( _p->_Listeners.find( accessor, val->handle ) )
	{
		for ( auto var : accessor->second )
		{
			if ( var )
			{
				var( val );

				if ( val->accept )
				{
					return;
				}
			}
		}
	}
}

void XE::EventService::PostEvent( XE::uint64 frame, XE::EventPtr val )
{
	if( frame == 0 )
	{
		PostEvent( val );
	}

	XEPFrameEvent evt;
	evt._Event = val;
	evt._Frame = frame;
	evt._StartFrame = GetFramework()->GetServiceT< XE::ITimerService >()->GetFrameCount();

	_p->_FrameEvents.push( std::move( evt ) );
}

void XE::EventService::PostEvent( XE::float32 dt, XE::EventPtr val )
{
	if( dt <= Mathf::Epsilon )
	{
		PostEvent( val );
	}

	XEPTimeEvent evt;
	evt._Event = val;
	evt._Duration = dt;
	evt._StartTime = GetFramework()->GetServiceT< XE::ITimerService >()->GetTime();

	_p->_TimeEvents.push( std::move( evt ) );
}

XE::Follow XE::EventService::RegisterListener( XE::EventHandle handle, ListenerType listener )
{
	Private::ListenerMap::accessor accessor;

	if ( _p->_Listeners.find( accessor, handle ) )
	{
		auto index = accessor->second.size();

		accessor->second.push_back( listener );

		return [this, handle, index]()
		{
			Private::ListenerMap::accessor accessor;

			if( _p->_Listeners.find( accessor, handle ) )
			{
				accessor->second[index] = nullptr;
			}
		};
	}

	if ( _p->_Listeners.insert( accessor, handle ) )
	{
		accessor->second.push_back( listener );

		return [this, handle]()
		{
			Private::ListenerMap::accessor accessor;

			if( _p->_Listeners.find( accessor, handle ) )
			{
				accessor->second[0] = nullptr;
			}
		};
	}

	return {};
}

void XE::EventService::ProcessTimeEvent()
{
	XE::float32 NowTime = GetFramework()->GetServiceT< XE::ITimerService >()->GetTime();

	XEPTimeEvent event;
	while ( _p->_TimeEvents.try_pop( event ) )
	{
		if ( ( NowTime - event._StartTime ) >= event._Duration )
		{
			PostEvent( event._Event );
		}
		else
		{
			_p->_TimeEvents.push( event );
			break;
		}
	}
}

void XE::EventService::ProcessFrameEvent()
{
	XE::uint64 FrameCount = GetFramework()->GetServiceT< XE::ITimerService >()->GetFrameCount();

	XEPFrameEvent event;
	while ( _p->_FrameEvents.try_pop( event ) )
	{
		if ( ( FrameCount - event._StartFrame ) >= event._Frame )
		{
			PostEvent( event._Event );
		}
		else
		{
			_p->_FrameEvents.push( event );
			break;
		}
	}
}
