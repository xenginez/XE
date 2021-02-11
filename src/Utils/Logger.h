/*!
 * \file	Logger.h
 *
 * \author	ZhengYuanQing
 * \date	2020/05/16
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef LOGGER_H__FABB4435_9587_4290_9EA3_18733C722EE2
#define LOGGER_H__FABB4435_9587_4290_9EA3_18733C722EE2

#include "Follow.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API Logger : public XE::Singleton< Logger >
{
	SINGLETON( Logger )

public:
	struct Private;

	using ListenerType = std::function<void( const std::chrono::system_clock::time_point&, XE::LoggerLevel, const std::string & )>;

private:
	Logger();

	~Logger();

public:
	void Log( XE::LoggerLevel level, const std::string & text );

public:
	XE::Follow RegisterListener( XE::LoggerLevel level, ListenerType listener );

private:
	Private * _p;
};

XE_INLINE std::string ToString( XE::LoggerLevel _Val )
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

#define XE_LOG(LEVEL, FMT, ...) \
XE::Logger::Instance()->Log( LEVEL, XE::StringUtils::Format(FMT, __VA_ARGS__) )

#endif // LOGGER_H__FABB4435_9587_4290_9EA3_18733C722EE2
