/*!
 * \file   RenderComponent.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __RENDERCOMPONENT_H__C324655A_7B4F_47F9_B71D_94616F6C9FFE
#define __RENDERCOMPONENT_H__C324655A_7B4F_47F9_B71D_94616F6C9FFE

#include "SceneComponent.h"

BEG_XE_NAMESPACE

class WORLD_API RenderComponent : public SceneComponent
{
	OBJECT( RenderComponent, SceneComponent )

public:
	friend class GameObject;

public:
	RenderComponent();

	~RenderComponent();

public:
	virtual AABB GetAABB() const;

private:
	void Render();

protected:
	virtual void OnRender();
};

END_XE_NAMESPACE

#endif // __RENDERCOMPONENT_H__C324655A_7B4F_47F9_B71D_94616F6C9FFE
