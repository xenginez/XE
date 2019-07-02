/*!
 * \file   Interface.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __INTERFACE_H__00216C60_5990_42A5_85EE_CB4CBE039CA5
#define __INTERFACE_H__00216C60_5990_42A5_85EE_CB4CBE039CA5

#include "Object.h"
#include "Prefab.h"

#include "IService.h"
#include "IFramework.h"
#include "IGUIService.h"
#include "IEventService.h"
#include "IInputService.h"
#include "IAudioService.h"
#include "ITimerService.h"
#include "IWorldService.h"
#include "IPluginService.h"
#include "IThreadService.h"
#include "IAssetsService.h"
#include "IConfigService.h"
#include "ILoggerService.h"
#include "IRenderService.h"
#include "IPhysicsService.h"
#include "INavigationService.h"
#include "ILocalizationService.h"

#define XE_LOG(LEVEL, FMT, ...) \
XE::IFramework::GetCurrentFramework()->GetLoggerService()->Log( LEVEL, __FILE__, __LINE__, XE::StringUtils::Format(FMT, __VA_ARGS__) );

#define REGISTER_PLUGIN( NAME ) \
extern "C" XE::IPlugin * RegisterPlugin( XE::IFrameworkPtr framework ) \
{ \
	return new NAME( framework ); \
} \
extern "C" void UnregisterPlugin( XE::IPlugin * plugin ) \
{ \
	delete plugin; \
}

#endif // __INTERFACE_H__00216C60_5990_42A5_85EE_CB4CBE039CA5
