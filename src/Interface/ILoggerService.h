/*!
 * \file   ILoggerService.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __ILOGGERSERVICE_H__1B5FD701_A9FF_4EC9_B3F6_B2490F7E7DFB
#define __ILOGGERSERVICE_H__1B5FD701_A9FF_4EC9_B3F6_B2490F7E7DFB

#include "IService.h"

BEG_XE_NAMESPACE

class INTERFACE_API Logger
{
public:
	String File;
	XE::uint64 Line;
	String Text;
	LoggerLevel Level;
	std::chrono::system_clock::time_point Time;
};
DECL_PTR( Logger );

class INTERFACE_API ILoggerService : public IService
{
	OBJECT( ILoggerService, IService )

public:
	typedef std::function<void( LoggerPtr )> ListenerType;

public:
	ILoggerService();

	virtual ~ILoggerService();

public:
	virtual void Log( LoggerLevel level, const String& file, XE::uint64 line, const String& text ) = 0;

public:
	virtual XE::uint64 RegisterListener( ListenerType listener ) = 0;

	virtual void UnregisterListener( XE::uint64 index ) = 0;

};

END_XE_NAMESAPCE

#endif // __ILOGGERSERVICE_H__1B5FD701_A9FF_4EC9_B3F6_B2490F7E7DFB
