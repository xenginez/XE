/*!
 * \file   DecalComponent.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/16
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __DECALCOMPONENT_H__74730DF4_A1AF_4583_9EEA_124BDF1E0EF7
#define __DECALCOMPONENT_H__74730DF4_A1AF_4583_9EEA_124BDF1E0EF7

#include "Type.h"

BEG_XE_NAMESPACE

class RENDER_API DecalComponent : public XE::RenderComponent
{
	OBJECT( DecalComponent, RenderComponent )

public:
	DecalComponent();

	~DecalComponent();

};

END_XE_NAMESAPCE

#endif // __DECALCOMPONENT_H__74730DF4_A1AF_4583_9EEA_124BDF1E0EF7
