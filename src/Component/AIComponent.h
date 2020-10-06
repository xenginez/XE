/*!
 * \file   AIComponent.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/12
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __AICOMPONENT_H__5B311461_A156_4393_B2B3_7A1587EF3F08
#define __AICOMPONENT_H__5B311461_A156_4393_B2B3_7A1587EF3F08

#include "Scene/BehaviorComponent.h"
#include "AI/AIModule.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API AIComponent : public XE::BehaviorComponent
{
	OBJECT( AIComponent, BehaviorComponent )

public:
	AIComponent();

	~AIComponent();

protected:
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::float32 dt ) override;

	virtual void OnClearup() override;

private:
	Array< AIModulePtr > _AIModules;
};

END_XE_NAMESPACE

#endif // __AICOMPONENT_H__5B311461_A156_4393_B2B3_7A1587EF3F08
