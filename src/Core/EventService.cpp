#include "EventService.h"

#include <tbb/concurrent_vector.h>
#include <tbb/concurrent_hash_map.h>
#include <tbb/concurrent_priority_queue.h>

USING_XE

BEG_META( EventService )
END_META()

struct XEPTimeEvent
{
	EventPtr _Event;
	XE::real _Duration;
	XE::real _StartTime;
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
	EventPtr _Event;
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


struct EventService::Private
{
	using ListenerMap = tbb::concurrent_hash_map<XE::uint64, tbb::concurrent_vector<IEventService::ListenerType>>;

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

void XE::EventService::PostEvent( EventPtr val )
{
	Private::ListenerMap::accessor accessor;
	if ( _p->_Listeners.find( accessor, val->id ) )
	{
		for ( auto var : accessor->second )
		{
			if ( var )
			{
				var( val );

				if ( val->ignore )
				{
					return;
				}
			}
		}
	}
}

void XE::EventService::PostEvent( XE::uint64 frame, EventPtr val )
{
	if( frame == 0 )
	{
		PostEvent( val );
	}

	XEPFrameEvent evt;
	evt._Event = val;
	evt._Frame = frame;
	evt._StartFrame = GetFramework()->GetTimerService()->GetFrameCount();

	_p->_FrameEvents.push( std::move( evt ) );
}

void XE::EventService::PostEvent( XE::real dt, EventPtr val )
{
	if( dt <= Mathf::Epsilon )
	{
		PostEvent( val );
	}

	XEPTimeEvent evt;
	evt._Event = val;
	evt._Duration = dt;
	evt._StartTime = GetFramework()->GetTimerService()->GetTime();

	_p->_TimeEvents.push( std::move( evt ) );
}

XE::uint64 XE::EventService::RegisterListener( XE::uint32 event, ListenerType listener )
{
	Private::ListenerMap::accessor accessor;

	if ( _p->_Listeners.find( accessor, event ) )
	{
		accessor->second.push_back( listener );
		return accessor->second.size() - 1;
	}

	if ( _p->_Listeners.insert( accessor, event ) )
	{
		accessor->second.push_back( nullptr );
		accessor->second.push_back( listener );
		return 1;
	}

	return 0;
}

void XE::EventService::UnregisterListener( XE::uint32 event, XE::uint64 index )
{
	Private::ListenerMap::accessor accessor;

	if ( _p->_Listeners.find( accessor, event ) )
	{
		accessor->second[index] = nullptr;
	}
}

void XE::EventService::ProcessTimeEvent()
{
	XE::real NowTime = GetFramework()->GetTimerService()->GetTime();

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
	XE::uint64 FrameCount = GetFramework()->GetTimerService()->GetFrameCount();

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
