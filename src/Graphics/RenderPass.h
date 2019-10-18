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

class XE_API RenderPass : public std::enable_shared_from_this< RenderPass >
{
	OBJECT( RenderPass )

public:
	RenderPass();

	virtual ~RenderPass();

public:
	virtual void Startup() = 0;

	virtual void Render() = 0;

	virtual void Clearup() = 0;

};

END_XE_NAMESPACE

#endif // RENDERPASS_H__7B98DD0C_EC15_4ADE_8690_80F577FAE14C
