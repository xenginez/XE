#include "Logger.h"

#include <tbb/concurrent_queue.h>



namespace std
{
	inline std::string to_string( XE::LoggerLevel _Val )
	{
		switch( _Val )
		{
		case XE::LoggerLevel::Error:
			return "Error";
		case XE::LoggerLevel::Warning:
			return "Warning";
		case XE::LoggerLevel::Message:
			return "Message";
		}

		return "";
	}
}

struct XE::Logger::Private
{
	bool _Exit = false;
	std::mutex _Mutex;
	std::thread _Thread;
	std::condition_variable _Cond;
	tbb::concurrent_queue< std::string > _Queue;

	std::mutex _ListenerMutex;
	std::map<XE::uint64, XE::Logger::ListenerType> _Listeners;
};

XE::Logger::Logger()
	:_p( new Private )
{
	std::thread th( [this]()
					{
						while( _p->_Exit )
						{
							{
								std::unique_lock<std::mutex> lock( _p->_Mutex );

								_p->_Cond.wait( lock );
							}

							std::string text;
							while( _p->_Queue.try_pop( text ) )
							{
								for( const auto & listener : _p->_Listeners )
								{
									if( listener.second )
									{
										listener.second( std::ref( text ) );
									}
								}
							}
						}
					} );
}

XE::Logger::~Logger()
{
	delete _p;
}

void XE::Logger::Log( LoggerLevel level, const std::string & text )
{
	std::string str = XE::StringUtils::Format( "%1:%2\t%3", std::chrono::system_clock::now(), level, text );

	_p->_Queue.push( std::move( str ) );

	_p->_Cond.notify_one();
}

XE::uint64 XE::Logger::RegisterListener( ListenerType listener )
{
	std::unique_lock<std::mutex> lock( _p->_ListenerMutex );

	auto code = std::chrono::system_clock::now().time_since_epoch().count();

	_p->_Listeners.insert( { code, listener } );

	return code;
}

void XE::Logger::UnregisterListener( XE::uint64 code )
{
	std::unique_lock<std::mutex> lock( _p->_ListenerMutex );

	auto it = _p->_Listeners.find( code );
	if( it != _p->_Listeners.end() )
	{
		_p->_Listeners.erase( it );
	}
}
