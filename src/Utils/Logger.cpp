#include "Logger.h"

#include <tbb/concurrent_queue.h>

#if PLATFORM_OS == OS_ANDROID
#include <android/log.h>
#endif

BEG_XE_NAMESPACE
inline std::string ToString( XE::LoggerLevel _Val )
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
END_XE_NAMESPACE

struct LoggerNode
{
	std::string msg;
	XE::LoggerLevel level;
	std::chrono::system_clock::time_point time;
};

struct XE::Logger::Private
{
	bool _Exit = false;
	std::mutex _Mutex;
	std::thread _Thread;
	std::condition_variable _Cond;
	tbb::concurrent_queue< LoggerNode > _Queue;

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

							LoggerNode node;
							while( _p->_Queue.try_pop( node ) )
							{
								for( const auto & listener : _p->_Listeners )
								{
									if( listener.second )
									{
										listener.second( std::ref(node.time), node.level, std::ref( node.msg ) );
									}
								}
							}
						}
					} );

	RegisterListener( []( const std::chrono::system_clock::time_point & time, XE::LoggerLevel level, const std::string & msg )
					  {
#if PLATFORM_OS == OS_ANDROID
						  switch( level )
						  {
						  case LoggerLevel::Error:
							  __android_log_print( ANDROID_LOG_ERROR, "XE", "%s\n", msg.c_str() );
							  break;
						  case LoggerLevel::Warning:
							  __android_log_print( ANDROID_LOG_WARN, "XE", "%s\n", msg.c_str() );
							  break;
						  case LoggerLevel::Message:
							  __android_log_print( ANDROID_LOG_INFO, "XE", "%s\n", msg.c_str() );
							  break;
						  default:
						  }
#else
						  std::string str = XE::StringUtils::Format( "%1:[%2] %3", time, level, msg );
						  std::cout << str << std::endl;
#endif
					  } );
}

XE::Logger::~Logger()
{
	delete _p;
}

void XE::Logger::Log( LoggerLevel level, const std::string & text )
{
	LoggerNode node;

	node.msg = text;
	node.level = level;
	node.time = std::chrono::system_clock::now();


	_p->_Queue.push( std::move( node ) );

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
