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

	~LoggerService();

public:
	virtual bool Startup() override;

	virtual void Update() override;

	virtual void Clearup() override;

public:
	virtual void Log( LoggerLevel level, const String& file, XE::uint64 line, const String& text ) override;

public:
	virtual XE::uint64 RegisterListener( ListenerType listener ) override;

	virtual void UnregisterListener( XE::uint64 index ) override;

private:
	Private * _p;
};

END_XE_NAMESAPCE

#endif // __LOGGERSERVICE_H__4F80F575_8FBD_4501_95B3_B1F7242F5540
