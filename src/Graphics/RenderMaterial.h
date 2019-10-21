/*!
 * \file	RenderMaterial.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/01
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RENDERMATERIAL_H__FA845E10_334A_4ED0_84F1_C269D27F002D
#define RENDERMATERIAL_H__FA845E10_334A_4ED0_84F1_C269D27F002D

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API RenderMaterial : public XE::Object
{
	OBJECT( RenderMaterial, Object )

public:
	RenderMaterial();

	~RenderMaterial() override;

public:
	const XE::String & GetName() const;

	void SetName( const XE::String & val );

	const RenderTechniquePtr & GetRenderTechnique() const;

	void SetRenderTechnique( const RenderTechniquePtr & val );

public:
	void AssetLoad() override;

	void AssetUnload() override;

private:
	XE::String _Name;
	RenderTechniquePtr _Technique;
};

END_XE_NAMESPACE

#endif // RENDERMATERIAL_H__FA845E10_334A_4ED0_84F1_C269D27F002D
