/*!
 * \file   GrassComponent.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/20
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __GRASSCOMPONENT_H__73FD9F66_F8C7_4DF7_9EF8_3F14A092AB97
#define __GRASSCOMPONENT_H__73FD9F66_F8C7_4DF7_9EF8_3F14A092AB97

#include "Type.h"

BEG_XE_NAMESPACE

class RENDER_API GrassComponent : public XE::RenderComponent
{
	OBJECT( GrassComponent, RenderComponent )

public:
	GrassComponent();

	~GrassComponent();
};

END_XE_NAMESAPCE

#endif // __GRASSCOMPONENT_H__73FD9F66_F8C7_4DF7_9EF8_3F14A092AB97
