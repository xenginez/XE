/*!
 * \file	RenderService.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/12
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RENDERSERVICE_H__F3DCE8EF_155B_4D6E_8551_76E5ABB05DDD
#define RENDERSERVICE_H__F3DCE8EF_155B_4D6E_8551_76E5ABB05DDD

#include "Type.h"

BEG_XE_NAMESPACE

class CORE_API RenderService : public XE::IRenderService
{
	OBJECT( RenderService, IRenderService )

private:
	struct Private;

public:
	RenderService();

	~RenderService() override;

public:
	void Prepare() override;

	bool Startup() override;

	void Update() override;

	void Clearup() override;

public:
	ContextPtr GetContext() const override;

	WindowHandle GetMainWindow() const override;

public:
	void RegisterLight( const LightPtr & val ) override;

	void UnregisterLight( const LightPtr & val ) override;

	void RegisterCamera( const CameraPtr & val ) override;

	void UnregisterCamera( const CameraPtr & val ) override;

	void RegisterRenderable( const RenderablePtr & val ) override;

	void UnregisterRenderable( const RenderablePtr & val ) override;

public:
	const Array<LightPtr> & GetLights() const override;

	const Array<CameraPtr> & GetCameras() const override;

	const Array<RenderablePtr> & GetRenderables() const override;

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // RENDERSERVICE_H__F3DCE8EF_155B_4D6E_8551_76E5ABB05DDD
