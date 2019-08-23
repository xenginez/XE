/*!
 * \file    Renderable.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-31
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __RENDERABLE_H__8DB83893_AC3A_4B1B_84CB_C62700378348
#define __RENDERABLE_H__8DB83893_AC3A_4B1B_84CB_C62700378348

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API Renderable : public XE::Object
{
	OBJECT( Renderable, Object )
	
public:
	Renderable();
	
	virtual ~Renderable();

public:
	virtual void Startup( RenderContextPtr & context );

	virtual void Render( RenderContextPtr & context, RenderQueuePtr & queue );

	virtual void Clearup( RenderContextPtr & context );

protected:
	virtual void OnStartup( RenderContextPtr & context ) = 0;

	virtual void OnRender( RenderContextPtr & context, RenderQueuePtr & queue ) = 0;

	virtual void OnClearup( RenderContextPtr & context ) = 0;

public:
	const Mat4 & GetTransform() const;

	void SetTransform( const Mat4 & val );

private:
	Mat4 _Transform;
};

END_XE_NAMESPACE

#endif //__RENDERABLE_H__8DB83893_AC3A_4B1B_84CB_C62700378348
