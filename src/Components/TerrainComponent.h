/*!
 * \file   TerrainComponent.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/19
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TERRAINCOMPONENT_H__C73FFF8B_F6DD_4CA4_A4E8_EA452D866499
#define __TERRAINCOMPONENT_H__C73FFF8B_F6DD_4CA4_A4E8_EA452D866499

#include "Type.h"

BEG_XE_NAMESPACE

class COMPONENTS_API TerrainComponent : public XE::SceneComponent
{
	OBJECT( TerrainComponent, SceneComponent )

public:
	TerrainComponent();

	~TerrainComponent();
};

END_XE_NAMESPACE

#endif // __TERRAINCOMPONENT_H__C73FFF8B_F6DD_4CA4_A4E8_EA452D866499
