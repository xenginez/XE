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

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API Logger : public XE::Singleton< Logger >
{
	SINGLETON( Logger )

public:
	struct Private;

	using ListenerType = std::function<void( const std::string & )>;

private:
	Logger();

	~Logger();

public:
	void Log( XE::LoggerLevel level, const std::string & text );

public:
	XE::uint64 RegisterListener( ListenerType listener );

	void UnregisterListener( XE::uint64 code );

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // LOGGER_H__FABB4435_9587_4290_9EA3_18733C722EE2
