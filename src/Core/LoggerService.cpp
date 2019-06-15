#include "LoggerService.h"

USING_XE

struct XE::LoggerService::Private
{
	std::mutex _Lock;
	std::vector<ILoggerService::ListenerType> _Listeners;
};

XE::LoggerService::LoggerService()
	:_p(new Private)
{

}

XE::LoggerService::~LoggerService()
{
	delete _p;
}

bool XE::LoggerService::Startup()
{
	return true;
}

void XE::LoggerService::Update()
{

}

void XE::LoggerService::Clearup()
{
	_p->_Listeners.clear();
}

void XE::LoggerService::Log( LoggerLevel level, const String& file, XE::uint64 line, const String& text )
{
	LoggerPtr log = XE::make_object<Logger>();

	log->Level = level;
	log->File = file;
	log->Line = line;
	log->Text = text;

	if( _p->_Listeners.empty() )
	{
		std::cout << "[" << EnumID<LoggerLevel>::Get()->FindName( static_cast< int64 >( level ) ) << "] File: " << file << " : " << line << std::endl;
		std::cout << "\t" << text << std::endl;
	}

	for ( auto var : _p->_Listeners )
	{
		if (var)
		{
			var( log );
		}
	}
}

XE::uint64 XE::LoggerService::RegisterListener( ListenerType listener )
{
	std::lock_guard<std::mutex> lock( _p->_Lock );

	XE::uint64 i = _p->_Listeners.size();

	_p->_Listeners.push_back( listener );

	return i;
}

void XE::LoggerService::UnregisterListener( XE::uint64 index )
{
	XE_ASSERT( index < _p->_Listeners.size() );

	std::lock_guard<std::mutex> lock( _p->_Lock );

	_p->_Listeners[index] = nullptr;
}
