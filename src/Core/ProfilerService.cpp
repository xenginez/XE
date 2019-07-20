#include "ProfilerService.h"

USING_XE

BEG_META(ProfilerService)
END_META()

struct XE::ProfilerService::Private
{
	using FramePair = Pair< ProfilerFramePtr, Stack<ProfilerItem*> >;

	std::mutex Lock;
	UnorderedMap< std::thread::id, FramePair > Frames;
	UnorderedMap< std::thread::id, Array<IProfilerService::ListenerType> > Callbacks;
};


XE::ProfilerService::ProfilerService()
	:_p( new Private )
{

}

XE::ProfilerService::~ProfilerService()
{
	delete _p;
}

void XE::ProfilerService::Prepare()
{

}

bool XE::ProfilerService::Startup()
{
	return true;
}

void XE::ProfilerService::Update()
{

}

void XE::ProfilerService::Clearup()
{
	_p->Callbacks.clear();
	_p->Frames.clear();
}

void XE::ProfilerService::BeginFrame()
{
	auto id = std::this_thread::get_id();

	auto it = _p->Frames.find( id );

	XE_ASSERT( it == _p->Frames.end() );

	ProfilerFramePtr frame = make_shared<ProfilerFrame>();
	
	frame->tid = id;

	_p->Frames[id] = std::make_pair( frame, Stack<ProfilerItem*>() );
}

void XE::ProfilerService::EndFrame()
{
	auto id = std::this_thread::get_id();

	auto it = _p->Frames.find( id );

	XE_ASSERT( it != _p->Frames.end() );

	auto rit = _p->Callbacks.find( id );
	if( rit != _p->Callbacks.end() )
	{
		for( auto& func : rit->second )
		{
			if( func )
			{
				func( it->second.first );
			}
		}
	}

	_p->Frames.erase( it );
}

XE::uint64 XE::ProfilerService::RegisterListener( const ListenerType& val )
{
	auto id = std::this_thread::get_id();

	std::lock_guard<std::mutex> lock( _p->Lock );

	_p->Callbacks[id].push_back( val );

	return _p->Callbacks[id].size() - 1;
}

bool XE::ProfilerService::UnregisterListener( XE::uint64 val )
{
	auto id = std::this_thread::get_id();

	XE_ASSERT( val < _p->Callbacks[id].size() );

	std::lock_guard<std::mutex> lock( _p->Lock );

	_p->Callbacks[id][val] = nullptr;

	return true;
}

XE::ProfilerItem* XE::ProfilerService::AcquireTrack( const String& val )
{
	auto id = std::this_thread::get_id();

	auto it = _p->Frames.find( id );

	XE_ASSERT( it != _p->Frames.end() );

	ProfilerItem* item = nullptr;
	if( it->second.second.empty() )
	{
		item = &( it->second.first->Children.emplace_back( ProfilerItem() ) );
	}
	else
	{
		item = it->second.second.top();
		item = &( item->Children.emplace_back( ProfilerItem() ) );
	}

	item->Text = val;
	item->StartTime = std::chrono::system_clock::now();
	it->second.second.push( item );
	return item;
}

void XE::ProfilerService::ReleaseTrack( ProfilerItem* val )
{
	val->StopTime = std::chrono::system_clock::now();

	auto it = _p->Frames.find( std::this_thread::get_id() );

	XE_ASSERT( it != _p->Frames.end() );

	it->second.second.pop();
}
