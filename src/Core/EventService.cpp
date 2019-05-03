#include "EventService.h"

#include <tbb/concurrent_vector.h>
#include <tbb/concurrent_hash_map.h>
#include <tbb/concurrent_priority_queue.h>

USING_XE

BEGIN_META( EventService )
END_META()

struct XEPTimeEvent
{
	EventPtr _Event;
	float _Duration;
	float _StartTime;
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
	using MapType = tbb::concurrent_hash_map<uint64, tbb::concurrent_vector< IEventService::ListenerType>>;

	MapType _Maps;

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
	_p->_Maps.clear();
	_p->_TimeEvents.clear();
	_p->_FrameEvents.clear();
}

void XE::EventService::PostEvent( EventPtr val )
{
	Private::MapType::accessor it;
	if ( _p->_Maps.find( it, val->id ) )
	{
		for ( auto var : it->second )
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
	XEPFrameEvent evt;
	evt._Event = val;
	evt._Frame = frame;
	evt._StartFrame = GetFramework()->GetTimerService()->GetFrameCount();

	_p->_FrameEvents.push( std::move( evt ) );
}

void XE::EventService::PostEvent( float dt, EventPtr val )
{
	XEPTimeEvent evt;
	evt._Event = val;
	evt._Duration = dt;
	evt._StartTime = GetFramework()->GetTimerService()->GetTime();

	_p->_TimeEvents.push( std::move( evt ) );
}

XE::uint64 XE::EventService::RegisterListener( uint32 event, ListenerType listener )
{
	Private::MapType::accessor it;

	if ( _p->_Maps.find( it, event ) )
	{
		auto i = it->second.size();
		it->second.push_back( listener );
		return i;
	}

	if ( _p->_Maps.insert( it, event ) )
	{
		it->second.push_back( nullptr );
		it->second.push_back( listener );
		return 1;
	}

	return 0;
}

void XE::EventService::UnregisterListener( uint32 event, XE::uint64 index )
{
	Private::MapType::accessor it;

	if ( _p->_Maps.find( it, event ) )
	{
		it->second[index] = nullptr;
	}
}

void XE::EventService::ProcessTimeEvent()
{
	auto now_time = GetFramework()->GetTimerService()->GetTime();

	XEPTimeEvent tevt;
	while ( _p->_TimeEvents.try_pop( tevt ) )
	{
		if ( ( now_time - tevt._StartTime ) >= tevt._Duration )
		{
			Private::MapType::accessor it;
			if ( _p->_Maps.find( it, tevt._Event->id ) )
			{
				for ( auto var : it->second )
				{
					if ( var )
					{
						var( tevt._Event );

						if ( tevt._Event->ignore )
						{
							return;
						}
					}
				}
			}
		}
		else
		{
			_p->_TimeEvents.push( tevt );
			break;
		}
	}
}

void XE::EventService::ProcessFrameEvent()
{
	XE::uint64 FrameCount = GetFramework()->GetTimerService()->GetFrameCount();

	XEPFrameEvent fevt;
	while ( _p->_FrameEvents.try_pop( fevt ) )
	{
		if ( ( FrameCount - fevt._StartFrame ) >= fevt._Frame )
		{
			Private::MapType::accessor it;
			if ( _p->_Maps.find( it, fevt._Event->id ) )
			{
				for ( auto var : it->second )
				{
					if ( var )
					{
						var( fevt._Event );

						if ( fevt._Event->ignore )
						{
							return;
						}
					}
				}
			}
		}
		else
		{
			_p->_FrameEvents.push( fevt );
			break;
		}
	}
}
