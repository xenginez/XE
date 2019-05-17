/*!
 * \file   LogService.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/05
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __LOGGERSERVICE_H__4F80F575_8FBD_4501_95B3_B1F7242F5540
#define __LOGGERSERVICE_H__4F80F575_8FBD_4501_95B3_B1F7242F5540

#include "Type.h"

BEG_XE_NAMESPACE

class CORE_API LoggerService : public ILoggerService
{
	OBJECT( LoggerService, ILoggerService )

private:
	struct Private;

public:
	LoggerService();

	~LoggerService() override;

public:
	bool Startup() override;

	void Update() override;

	void Clearup() override;

public:
	void Log( LoggerLevel level, const String& file, XE::uint64 line, const String& text ) override;

public:
	XE::uint64 RegisterListener( ListenerType listener ) override;

	void UnregisterListener( XE::uint64 index ) override;

private:
	Private * _p;
};

END_XE_NAMESAPCE

#endif // __LOGGERSERVICE_H__4F80F575_8FBD_4501_95B3_B1F7242F5540
