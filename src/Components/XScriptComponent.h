/*!
 * \file	XScriptComponent.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/09
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef XSCRIPTCOMPONENT_H__90289E18_5D9B_4C56_A0AA_3D0659B65BB9
#define XSCRIPTCOMPONENT_H__90289E18_5D9B_4C56_A0AA_3D0659B65BB9

#include "Type.h"

BEG_XE_NAMESPACE

class COMPONENTS_API XScriptComponent : XE::BehaviorComponent
{
	OBJECT( XScriptComponent, BehaviorComponent )

public:
	XScriptComponent();

	~XScriptComponent();

protected:
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::real dt ) override;

	virtual void OnClearup() override;

private:
	Variant _Script;
	IMetaClassPtr _Class;
	IMetaMethodPtr _OnStartup;
	IMetaMethodPtr _OnUpdate;
	IMetaMethodPtr _OnClearup;
};

END_XE_NAMESPACE

#endif // XSCRIPTCOMPONENT_H__90289E18_5D9B_4C56_A0AA_3D0659B65BB9
