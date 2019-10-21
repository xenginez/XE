/*!
 * \file	RenderTechnique.h
 *
 * \author	ZhengYuanQing
 * \date	2019/10/21
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RENDERTECHNIQUE_H__60B964E9_BB61_41A1_B657_6B3552D50BAB
#define RENDERTECHNIQUE_H__60B964E9_BB61_41A1_B657_6B3552D50BAB

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API RenderTechnique : public XE::Object
{
	OBJECT( RenderTechnique, Object )

public:
	RenderTechnique();

	~RenderTechnique() override;

public:
	virtual void Startup() = 0;

	virtual void Render() = 0;

	virtual void Clearup() = 0;

};

END_XE_NAMESPACE

#endif // RENDERTECHNIQUE_H__60B964E9_BB61_41A1_B657_6B3552D50BAB
