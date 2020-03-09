/*!
 * \file	Interface.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/21
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef INTERFACE_H__F027F37D_259E_4565_8851_20A77361A913
#define INTERFACE_H__F027F37D_259E_4565_8851_20A77361A913

#include "IService.h"
#include "IFramework.h"
#include "IAudioService.h"
#include "ITimerService.h"
#include "IWorldService.h"
#include "IEventService.h"
#include "IInputService.h"
#include "IRenderService.h"
#include "IThreadService.h"
#include "IAssetsService.h"
#include "IConfigService.h"
#include "ILoggerService.h"
#include "IPhysicsService.h"
#include "IProfilerService.h"
#include "INavigationService.h"
#include "ILocalizationService.h"


#define XE_LOG(LEVEL, FMT, ...) \
XE::IFramework::GetCurrentFramework()->GetLoggerService()->Log( LEVEL, __FILE__, __LINE__, XE::StringUtils::Format(FMT, __VA_ARGS__) );

#define CHECK_THREAD(THREAD_TYPE) \
if( XE::IFramework::GetCurrentFramework()->GetThreadService()->GetCurrentThreadType() == XE::THREAD_TYPE ) { XE_LOG( XE::LoggerLevel::Error, "the current thread is not the " #THREAD_TYPE ) };

#endif // INTERFACE_H__F027F37D_259E_4565_8851_20A77361A913
