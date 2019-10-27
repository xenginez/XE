#include "Texture.h"

#include "Gfx.h"

USING_XE

BEG_META( Texture )
END_META()

XE::Texture::Texture()
{

}

XE::Texture::~Texture()
{

}

XE::TextureType XE::Texture::GetType() const
{
	return _Type;
}

void XE::Texture::SetType( XE::TextureType val )
{
	_Type = val;
}

XE::TextureFormat XE::Texture::GetFormat() const
{
	return _Format;
}

void XE::Texture::SetFormat( XE::TextureFormat val )
{
	_Format = val;
}

XE::uint32 XE::Texture::GetStorageSize() const
{
	return _StorageSize;
}

void XE::Texture::SetStorageSize( XE::uint32 val )
{
	_StorageSize = val;
}

XE::uint16 XE::Texture::GetWidth() const
{
	return _Width;
}

void XE::Texture::SetWidth( XE::uint16 val )
{
	_Width = val;
}

XE::uint16 XE::Texture::GetHeight() const
{
	return _Height;
}

void XE::Texture::SetHeight( XE::uint16 val )
{
	_Height = val;
}

XE::uint16 XE::Texture::GetDepth() const
{
	return _Depth;
}

void XE::Texture::SetDepth( XE::uint16 val )
{
	_Depth = val;
}

XE::uint16 XE::Texture::GetNumLayers() const
{
	return _NumLayers;
}

void XE::Texture::SetNumLayers( XE::uint16 val )
{
	_NumLayers = val;
}

XE::uint8 XE::Texture::GetNumMips() const
{
	return _NumMips;
}

void XE::Texture::SetNumMips( XE::uint8 val )
{
	_NumMips = val;
}

XE::uint8 XE::Texture::GetBitsPerPixel() const
{
	return _BitsPerPixel;
}

void XE::Texture::SetBitsPerPixel( XE::uint8 val )
{
	_BitsPerPixel = val;
}

bool XE::Texture::GetCubeMap() const
{
	return _CubeMap;
}

void XE::Texture::SetCubeMap( bool val )
{
	_CubeMap = val;
}

XE::TextureHandle XE::Texture::GetHandle()
{
	return _Handle;
}

void XE::Texture::AssetLoad()
{
	switch( _Type )
	{
	case XE::TextureType::TEXTURE:
		//Gfx::createTexture();
		break;
	case XE::TextureType::TEXTURE2D:
		//Gfx::createTexture2D();
		break;
	case XE::TextureType::TEXTURE3D:
		//Gfx::createTexture3D();
		break;
	case XE::TextureType::TEXTURECUBE:
		//Gfx::createTextureCube();
		break;
	default:
		break;
	}
}

void XE::Texture::AssetUnload()
{
	if( _Handle )
	{
		Gfx::destroy( _Handle );
	}
}
