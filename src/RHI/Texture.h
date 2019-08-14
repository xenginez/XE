/*!
 * \file   Texture.h
 *
 * \author ZhengYuanQing
 * \date   2019/05/29
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TEXTURE_H__6DB7FD0A_1D06_48FC_9F35_B690DC44BD81
#define __TEXTURE_H__6DB7FD0A_1D06_48FC_9F35_B690DC44BD81

#include "Resource.h"

BEG_XE_NAMESPACE

class RHI_API Texture : public Resource
{
	OBJECT( Texture, Resource )

public:
	Texture();

	~Texture() override;

public:
	TextureFormat GetFormat() const;

protected:
	TextureFormat _Format;
};

class RHI_API Texture2D : public Texture
{
	OBJECT( Texture2D, Texture )

public:
	Texture2D();

	~Texture2D() override;

public:
	XE::uint32 GetMipCount() const;

	XE::uint32 GetWidth( XE::uint32 mip = 1 ) const;

	XE::uint32 GetHeight( XE::uint32 mip = 1 ) const;

protected:
	XE::uint32 _Width;
	XE::uint32 _Height;
	XE::uint32 _MipLevel;
};

class RHI_API Texture3D : public Texture2D
{
	OBJECT( Texture3D, Texture2D )

public:
	Texture3D();

	~Texture3D() override;

public:
	XE::uint32 GetDepth( XE::uint32 mip = 1 ) const;

private:
	XE::uint32 _Depth;
};

class RHI_API TextureCube : public Texture2D
{
	OBJECT( TextureCube, Texture2D )

public:
	TextureCube();

	~TextureCube() override;

public:
	XE::uint32 GetSize() const;

private:
	XE::uint32 _Size;
};

class RHI_API Texture2DArray : public Texture2D
{
	OBJECT( Texture2DArray, Texture2D )

public:
	Texture2DArray();

	~Texture2DArray() override;

public:
	XE::uint32 GetSize() const;

private:
	XE::uint32 _Size;
};

END_XE_NAMESPACE

#endif // __TEXTURE_H__6DB7FD0A_1D06_48FC_9F35_B690DC44BD81
