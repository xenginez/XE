/*!
 * \file   IRenderService.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __IRENDERSERVICE_H__4551F5BB_7CED_4EB1_938F_813FF61A70AC
#define __IRENDERSERVICE_H__4551F5BB_7CED_4EB1_938F_813FF61A70AC

#include "IService.h"

BEG_XE_NAMESPACE

DECL_PTR( Light );
DECL_PTR( Camera );
DECL_PTR( Renderable );

class XE_API IRenderService : public IService
{
	OBJECT( IRenderService, IService )

public:
	IRenderService();

	~IRenderService() override;

public:
	virtual void RegisterLight( const LightPtr & val ) = 0;

	virtual void UnregisterLight( const LightPtr & val ) = 0;

	virtual void RegisterCamera( const CameraPtr & val ) = 0;

	virtual void UnregisterCamera( const CameraPtr & val ) = 0;

	virtual void RegisterRenderable( const RenderablePtr & val ) = 0;

	virtual void UnregisterRenderable( const RenderablePtr & val ) = 0;

public:
	virtual const Array<LightPtr> & GetLights() const = 0;

	virtual const Array<CameraPtr> & GetCameras() const = 0;

	virtual const Array<RenderablePtr> & GetRenderables() const = 0;

};

END_XE_NAMESPACE

#endif // __IRENDERSERVICE_H__4551F5BB_7CED_4EB1_938F_813FF61A70AC
