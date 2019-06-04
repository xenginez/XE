/*!
 * \file   ParticleComponent.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/19
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __PARTICLECOMPONENT_H__2F6A8D8A_2498_4C80_A8DE_B8DD4C1F3CB2
#define __PARTICLECOMPONENT_H__2F6A8D8A_2498_4C80_A8DE_B8DD4C1F3CB2

#include "Type.h"

BEG_XE_NAMESPACE

class RENDER_API ParticleComponent : public XE::RenderComponent
{
	OBJECT( ParticleComponent, RenderComponent )

public:
	ParticleComponent();

	~ParticleComponent();
};

END_XE_NAMESPACE

#endif // __PARTICLECOMPONENT_H__2F6A8D8A_2498_4C80_A8DE_B8DD4C1F3CB2
