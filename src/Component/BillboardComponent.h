/*!
 * \file   BillboardComponent.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/19
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __BILLBOARDCOMPONENT_H__88F31186_2404_497D_8FC6_B6F7FF1C9C56
#define __BILLBOARDCOMPONENT_H__88F31186_2404_497D_8FC6_B6F7FF1C9C56

#include "Scene/SceneComponent.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API BillboardComponent : public XE::SceneComponent
{
	OBJECT( BillboardComponent, SceneComponent )

public:
	BillboardComponent();

	~BillboardComponent();
};

END_XE_NAMESPACE

#endif // __BILLBOARDCOMPONENT_H__88F31186_2404_497D_8FC6_B6F7FF1C9C56
