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
	const String & GetName() const;

	void SetName( const String & val );

	TextureHandle GetBaseColorTexture() const;

	void SetBaseColorTexture( TextureHandle val );

	TextureHandle GetSpecularTexture() const;

	void SetSpecularTexture( TextureHandle val );

	TextureHandle GetEmissiveTexture() const;

	void SetEmissiveTexture( TextureHandle val );

public:
	TextureHandle GetNormalMap() const;

	void SetNormalMap( TextureHandle val );

	TextureHandle GetOcclusionMap() const;

	void SetOcclusionMap( TextureHandle val );

	TextureHandle GetLightMap() const;

	void SetLightMap( TextureHandle val );

	TextureHandle GetHeightMap() const;

	void SetHeightMap( TextureHandle val );

public:
	XE::uint32 GetShadingModel() const;

	void SetShadingModel( XE::uint32 val );

	XE::uint32 GetAlphaMode() const;

	void SetAlphaMode( XE::uint32 val );

	XE::float32 GetAlphaThreshold() const;

	void SetAlphaThreshold( XE::float32 val );

	bool GetDoubleSided() const;

	void SetDoubleSided( bool val );

	const Vec4 & GetBaseColor() const;

	void SetBaseColor( const Vec4 & val );

	const Vec4 & GetSpecularParams() const;

	void SetSpecularParams( const Vec4 & val );

	const Vec3 & GetEmGetsiveColor() const;

	void SetEmGetsiveColor( const Vec3 & val );

	XE::float32 GetHeightScale() const;

	void SetHeightScale( XE::float32 val );

	XE::float32 GetHeightOffset() const;

	void SetHeightOffset( XE::float32 val );

	void SetIndexOfRefraction( XE::float32 val );

	XE::float32 GetIndexOfRefraction() const;

private:

};

END_XE_NAMESPACE

#endif // RENDERMATERIAL_H__FA845E10_334A_4ED0_84F1_C269D27F002D
