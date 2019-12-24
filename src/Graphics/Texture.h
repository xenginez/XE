/*!
 * \file	Texture.h
 *
 * \author	ZhengYuanQing
 * \date	2019/10/23
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef TEXTURE_H__4257A2FC_3685_4263_AB51_8E50E8D1D874
#define TEXTURE_H__4257A2FC_3685_4263_AB51_8E50E8D1D874

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API Texture : public XE::Object
{
	OBJECT( Texture, Object )

public:
	Texture();

	~Texture() override;

public:
	XE::TextureType GetType() const;

	void SetType( XE::TextureType val );

	XE::TextureFormat GetFormat() const;

	void SetFormat( XE::TextureFormat val );

	XE::uint16 GetWidth() const;

	void SetWidth( XE::uint16 val );

	XE::uint16 GetHeight() const;

	void SetHeight( XE::uint16 val );

	XE::uint16 GetDepth() const;

	void SetDepth( XE::uint16 val );

	XE::uint16 GetNumLayers() const;

	void SetNumLayers( XE::uint16 val );

	XE::uint8 GetNumMips() const;

	void SetNumMips( XE::uint8 val );

	const Array<XE::uint8> & GetData() const;

	void SetData( const Array<XE::uint8> & val );

public:
	TextureHandle GetHandle();

public:
	void AssetLoad() override;

	void AssetUnload() override;

private:
	TextureType _Type;
	TextureFormat _Format;
	XE::uint16 _Width;
	XE::uint16 _Height;
	XE::uint16 _Depth;
	XE::uint16 _NumLayers;
	XE::uint8 _NumMips;
	TextureHandle _Handle;
	Array<XE::uint8> _Data;
};

END_XE_NAMESPACE

#endif // TEXTURE_H__4257A2FC_3685_4263_AB51_8E50E8D1D874
