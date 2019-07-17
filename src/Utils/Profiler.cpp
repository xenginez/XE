#include "Profiler.h"

USING_XE

XE::ProfilerTrack::ProfilerTrack( const String & file, XE::uint64 line, const String & function )
	: _Item( Profiler::Acquire( file, line, function ) )
{

}

XE::ProfilerTrack::ProfilerTrack( ProfilerTrack && val )
	: _Item( val._Item )
{

}

XE::ProfilerTrack & XE::ProfilerTrack::operator=( ProfilerTrack && val )
{
	std::swap( _Item, val._Item );

	return *this;
}

XE::ProfilerTrack::~ProfilerTrack()
{
	Profiler::Release( _Item );
}


struct XE::Profiler::Private
{
	using FramePair = Pair< ProfilerFramePtr, Stack<ProfilerItem *> >;

	std::mutex Lock;
	UnorderedMap< std::thread::id, FramePair > Frames;
	UnorderedMap< std::thread::id, Array<ListenerType> > Callbacks;
};

XE::Profiler::Profiler()
	:_p( new Private )
{

}

XE::Profiler::~Profiler()
{
	delete _p;
}

void Profiler::Beg()
{
	auto id = std::this_thread::get_id();

	auto it = This()->_p->Frames.find( id );

	XE_ASSERT( it == This()->_p->Frames.end() );

	ProfilerFramePtr frame = make_shared<ProfilerFrame>();
	frame->tid = id;
	This()->_p->Frames[id] = std::make_pair( frame, Stack<ProfilerItem *>() );
}

void Profiler::End()
{
	auto id = std::this_thread::get_id();

	auto it = This()->_p->Frames.find( id );

	XE_ASSERT( it != This()->_p->Frames.end() );

	auto rit = This()->_p->Callbacks.find( id );
	if( rit != This()->_p->Callbacks.end() )
	{
		for( auto & reg : rit->second )
		{
			if( reg )
			{
				reg( it->second.first );
			}
		}
	}

	This()->_p->Frames.erase( it );
}

XE::ProfilerItem * XE::Profiler::Acquire( const String & file, XE::uint64 line, const String & function )
{
	auto id = std::this_thread::get_id();

	auto it = This()->_p->Frames.find( id );

	XE_ASSERT( it != This()->_p->Frames.end() );

	ProfilerItem * item = nullptr;
	if( it->second.second.empty() )
	{
		item = &( it->second.first->Children.emplace_back( ProfilerItem() ) );
	}
	else
	{
		item = it->second.second.top();
		item = &( item->Children.emplace_back( ProfilerItem() ) );
	}

	item->File = file;
	item->Line = line;
	item->Function = function;
	item->StartTime = std::chrono::system_clock::now();
	it->second.second.push( item );
	return item;
}

void XE::Profiler::Release( ProfilerItem * val )
{
	val->StopTime = std::chrono::system_clock::now();

	auto it = This()->_p->Frames.find( std::this_thread::get_id() );

	XE_ASSERT( it != This()->_p->Frames.end() );

	it->second.second.pop();
}

XE::uint64 Profiler::RegisterListener( Profiler::ListenerType val )
{
	auto id = std::this_thread::get_id();

	std::lock_guard<std::mutex> lock( This()->_p->Lock );

	This()->_p->Callbacks[id].push_back( val );

	return This()->_p->Callbacks[id].size() - 1;
}

void XE::Profiler::UnregisterListener( XE::uint64 val )
{
	auto id = std::this_thread::get_id();

	XE_ASSERT( val < This()->_p->Callbacks[id].size() );

	std::lock_guard<std::mutex> lock( This()->_p->Lock );

	This()->_p->Callbacks[id][val] = nullptr;
}
