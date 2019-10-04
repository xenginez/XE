/*!
 * \file   AudioSourceComponent.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/09
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __AUDIOSOURCECOMPONENT_H__A844B4A3_B849_4C4A_BE4F_3A21DD762972
#define __AUDIOSOURCECOMPONENT_H__A844B4A3_B849_4C4A_BE4F_3A21DD762972

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API AudioSourceComponent : public SceneComponent
{
	OBJECT( AudioSourceComponent, SceneComponent )

public:
	AudioSourceComponent();

	~AudioSourceComponent();

};

END_XE_NAMESPACE

#endif // __AUDIOSOURCECOMPONENT_H__A844B4A3_B849_4C4A_BE4F_3A21DD762972
