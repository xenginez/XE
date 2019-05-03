/*!
 * \file   StaticMeshComponent.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/16
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __STATICMESHCOMPONENT_H__3488930D_21E8_435B_8F0F_42F631AACCDD
#define __STATICMESHCOMPONENT_H__3488930D_21E8_435B_8F0F_42F631AACCDD

#include "MeshComponent.h"

BEG_XE_NAMESPACE

class RENDER_API StaticMeshComponent : public XE::MeshComponent
{
	OBJECT( StaticMeshComponent, MeshComponent )

public:
	StaticMeshComponent();

	~StaticMeshComponent();

public:

};

END_XE_NAMESAPCE

#endif // __STATICMESHCOMPONENT_H__3488930D_21E8_435B_8F0F_42F631AACCDD
