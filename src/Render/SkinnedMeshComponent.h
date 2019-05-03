/*!
 * \file   SkinnedMeshComponent.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/16
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __SKINNEDMESHCOMPONENT_H__523D1B46_3335_4E21_B954_897B1EF96A64
#define __SKINNEDMESHCOMPONENT_H__523D1B46_3335_4E21_B954_897B1EF96A64

#include "MeshComponent.h"

BEG_XE_NAMESPACE

class RENDER_API SkinnedMeshComponent : public XE::MeshComponent
{
	OBJECT( SkinnedMeshComponent, MeshComponent )

public:
	SkinnedMeshComponent();

	~SkinnedMeshComponent();
};

END_XE_NAMESAPCE

#endif // __SKINNEDMESHCOMPONENT_H__523D1B46_3335_4E21_B954_897B1EF96A64
