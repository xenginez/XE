#include "Logger.h"

#include <tbb/concurrent_vector.h>
#include <tbb/concurrent_hash_map.h>

#if PLATFORM_OS == OS_ANDROID
#include <android/log.h>
#endif

using LoggerMap = tbb::concurrent_hash_map< XE::LoggerLevel, tbb::concurrent_vector< XE::Logger::ListenerType > >;

struct XE::Logger::Private
{
	LoggerMap _Listeners;
};

XE::Logger::Logger()
	:_p( new Private )
{
}

XE::Logger::~Logger()
{
	delete _p;
}

void XE::Logger::Log( LoggerLevel level, const XE::String & text )
{
	auto time = std::chrono::system_clock::now();

	LoggerMap::accessor accessor;
	if( _p->_Listeners.find( accessor, level ) )
	{
		for( const auto & listener : accessor->second )
		{
			if( listener )
			{
				listener( std::ref( time ), level, std::ref( text ) );
			}
		}
	}
}

XE::Follow XE::Logger::RegisterListener( XE::LoggerLevel level, ListenerType listener )
{
	LoggerMap::accessor accessor;
	if( !_p->_Listeners.find( accessor, level ) )
	{
		_p->_Listeners.insert( accessor, level );
	}

	for( size_t i = 0; i < accessor->second.size(); i++ )
	{
		if( accessor->second[i] == nullptr )
		{
			accessor->second[i] = listener;

			return [this, level, i]()
			{
				LoggerMap::accessor accessor;
				if( _p->_Listeners.find( accessor, level ) )
				{
					accessor->second[i] = nullptr;;
				}
			};
		}
	}

	auto index = accessor->second.size();

	accessor->second.push_back( listener );

	return [this, level, index]()
	{
		LoggerMap::accessor accessor;
		if( _p->_Listeners.find( accessor, level ) )
		{
			accessor->second[index] = nullptr;;
		}
	};
}
