/*!
 * \file   Type.h
 *
 * \author ZhengYuanQing
 * \date   2019/02/26
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TYPE_H__14214677_E236_47F9_92B5_48295B609787
#define __TYPE_H__14214677_E236_47F9_92B5_48295B609787

#include "Interface/Interface.h"

BEG_XE_NAMESPACE

DECL_PTR( EventService );
DECL_PTR( TimerService );
DECL_PTR( AudioService );
DECL_PTR( SceneService );
DECL_PTR( InputService );
DECL_PTR( AssetsService );
DECL_PTR( ConfigService );
DECL_PTR( RenderService );
DECL_PTR( ThreadService );
DECL_PTR( PhysicsService );
DECL_PTR( NavigationService );
DECL_PTR( LocalizationService );
class CoreFramework;  using CoreFrameworkPtr = CoreFramework * ;

END_XE_NAMESPACE

#endif // __TYPE_H__14214677_E236_47F9_92B5_48295B609787
