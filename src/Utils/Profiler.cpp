#include "Profiler.h"

USING_XE

XE::ProfilerTrack::ProfilerTrack( const String& file, XE::uint64 line, const String& function )
	: _Item( Profiler::Begin( file, line, function ) )
{

}

XE::ProfilerTrack::ProfilerTrack( ProfilerTrack &&val )
	: _Item( val._Item )
{

}

XE::ProfilerTrack& XE::ProfilerTrack::operator=( ProfilerTrack &&val )
{
	_Item = val._Item;
	return *this;
}

XE::ProfilerTrack::~ProfilerTrack()
{
	Profiler::End( _Item );
}


struct XE::Profiler::Private
{
	using FramePair = Pair< ProfilerFramePtr, Stack<ProfilerItem *> >;

	std::mutex Lock;
	Array<ListenerType> Callback;
	UnorderedMap< std::thread::id, FramePair > Frames;
};


XE::Profiler::Profiler()
	:_p(new Private)
{

}

XE::Profiler::~Profiler()
{
	delete _p;
}

XE::ProfilerItem * XE::Profiler::Begin( const String& file, XE::uint64 line, const String& function )
{
	auto id = std::this_thread::get_id();

	auto it = This()->_p->Frames.find( id );

	if ( it == This()->_p->Frames.end() || it->second.first == nullptr )
	{
		ProfilerFramePtr frame = make_shared<ProfilerFrame>();
		frame->TID = id;
		This()->_p->Frames[id] = std::make_pair( frame, Stack<ProfilerItem*>() );
	}

	ProfilerItem * item = nullptr;
	if (it->second.second.empty())
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

void XE::Profiler::End( ProfilerItem * val )
{
	val->StopTime = std::chrono::system_clock::now();


	auto it = This()->_p->Frames.find( std::this_thread::get_id() );

	XE_ASSERT( it != This()->_p->Frames.end() );

	it->second.second.pop();

	if ( it->second.second.empty() )
	{
		for ( XE::uint64 i = 0; i < This()->_p->Callback.size(); ++i )
		{
			if ( This()->_p->Callback[i] )
			{
				This()->_p->Callback[i]( it->second.first );
			}
		}

		it->second.first = nullptr;
	}
}

XE::uint64 XE::Profiler::RegisterListener( ListenerType val )
{
	std::lock_guard<std::mutex> lock( This()->_p->Lock );

	This()->_p->Callback.push_back( val );

	return This()->_p->Callback.size() - 1;
}

void XE::Profiler::UnregisterListener( XE::uint64 val )
{
	XE_ASSERT( val < This()->_p->Callback.size() );

	std::lock_guard<std::mutex> lock( This()->_p->Lock );

	This()->_p->Callback[val] = nullptr;
}
