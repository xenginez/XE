#include "Texture.h"

#include "Gfx.h"

USING_XE

BEG_META( Texture )
type->Property( "Width", &Texture::_Width );
type->Property( "Height", &Texture::_Height );
type->Property( "Depth", &Texture::_Depth );
type->Property( "NumLayers", &Texture::_NumLayers);
type->Property( "NumMips", &Texture::_NumMips );
type->Property( "Data", &Texture::_Data, IMetaProperty::NoDesign );
END_META()

XE::Texture::Texture()
	:_Width( 0 ), _Height( 0 ), _Depth( 0 ), _NumLayers( 0 ), _NumMips( 0 )
{

}

XE::Texture::~Texture()
{

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

const Buffer & Texture::GetData() const
{
	return _Data;
}

void Texture::SetData( const Buffer & val )
{
	_Data = val;
}

void XE::Texture::AssetLoad()
{

}

void XE::Texture::AssetUnload()
{

}
