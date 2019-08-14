/*!
 * \file	RenderPass.h
 *
 * \author	ZhengYuanQing
 * \date	2019/07/13
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RENDERPASS_H__7B98DD0C_EC15_4ADE_8690_80F577FAE14C
#define RENDERPASS_H__7B98DD0C_EC15_4ADE_8690_80F577FAE14C

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API RenderPass : public std::enable_shared_from_this< RenderPass >
{
	OBJECT( RenderPass )

public:
	friend class Technique;

public:
	RenderPass();

	virtual ~RenderPass();

public:
	TechniquePtr GetTechnuque() const;

public:
	virtual void Startup( RenderContextPtr & context ) = 0;

	virtual void Render( RenderContextPtr & context ) = 0;

	virtual void Clearup( RenderContextPtr & context ) = 0;

private:
	TechniqueWPtr _Technique;
};

END_XE_NAMESPACE

#endif // RENDERPASS_H__7B98DD0C_EC15_4ADE_8690_80F577FAE14C
