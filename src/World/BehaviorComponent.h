/*!
 * \file   BehaviorComponent.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __BEHAVIORCOMPONENT_H__E954875B_F87F_4716_87E4_BE15F284BD22
#define __BEHAVIORCOMPONENT_H__E954875B_F87F_4716_87E4_BE15F284BD22

#include "Component.h"

BEG_XE_NAMESPACE

class WORLD_API BehaviorComponent : public Component
{
	OBJECT( BehaviorComponent, Component )

public:
	friend class GameObject;

public:
	BehaviorComponent();

	~BehaviorComponent();

};

END_XE_NAMESAPCE

#endif // __BEHAVIORCOMPONENT_H__E954875B_F87F_4716_87E4_BE15F284BD22
