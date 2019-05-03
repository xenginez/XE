/*!
 * \file   AudioListenerComponent.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/09
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __AUDIOLISTENERCOMPONENT_H__8A4FA2D5_82FE_4116_87AB_C7D3E41D74D4
#define __AUDIOLISTENERCOMPONENT_H__8A4FA2D5_82FE_4116_87AB_C7D3E41D74D4

#include "Type.h"

BEG_XE_NAMESPACE

class AUDIO_API AudioListenerComponent : public SceneComponent
{
	OBJECT( AudioListenerComponent, SceneComponent )

public:
	AudioListenerComponent();

	~AudioListenerComponent();

protected:
	virtual void OnUpdate( float dt ) override;

};

END_XE_NAMESAPCE

#endif // __AUDIOLISTENERCOMPONENT_H__8A4FA2D5_82FE_4116_87AB_C7D3E41D74D4
