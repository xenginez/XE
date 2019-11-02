/*!
 * \file	PBRRenderer.h
 *
 * \author	ZhengYuanQing
 * \date	2019/10/21
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef PBRRENDERER_H__F758732B_877A_4011_9CDD_EB6D88994B9D
#define PBRRENDERER_H__F758732B_877A_4011_9CDD_EB6D88994B9D

#include "Type.h"

BEG_XE_NAMESPACE

class PBRRenderer : public XE::Renderer
{
	OBJECT( PBRRenderer, Renderer )

public:
	PBRRenderer();

	~PBRRenderer() override;
};

END_XE_NAMESPACE

#endif // PBRRENDERER_H__F758732B_877A_4011_9CDD_EB6D88994B9D
