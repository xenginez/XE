#include "Texture.h"

#include "Gfx.h"

USING_XE

BEG_META( Texture )
END_META()

XE::Texture::Texture()
	:_Type( XE::TextureType::TEXTURE2D ), _Format( XE::TextureFormat::RGBA8 ), _Width( 0 ), _Height( 0 ), _Depth( 0 ), _NumLayers( 0 ), _NumMips( 0 )
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

const Array<XE::uint8> & Texture::GetData() const
{
	return _Data;
}

void Texture::SetData( const Array<XE::uint8> & val )
{
	_Data = val;
}

XE::TextureHandle XE::Texture::GetHandle()
{
	return _Handle;
}

void XE::Texture::AssetLoad()
{
	switch( _Type )
	{
	case XE::TextureType::TEXTURE2D:
		//Gfx::createTexture2D();
		break;
	case XE::TextureType::TEXTURE3D:
		//Gfx::createTexture3D();
		break;
	case XE::TextureType::TEXTURECUBE:
		//Gfx::createTextureCube();
		break;
	case XE::TextureType::TEXTUREARRAY:
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
