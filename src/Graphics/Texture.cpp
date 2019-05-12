#include "Texture.h"

#include "GFX.h"

USING_XE

BEGIN_META(Texture)
END_META()

XE::Texture::Texture()
{

}

XE::Texture::Texture( const MemoryView * _mem, uint64 _flags /*= BGFX_TEXTURE_NONE*/, uint8 _skip /*= 0*/, TextureInfo * _info /*= nullptr */ )
{
	TextureInfo * pInfo = _info;
	if ( pInfo == nullptr )
	{
		pInfo = &_Info;
	}

	_Handle = GFX::CreateTexture(_mem, _flags, _skip, pInfo);

	if ( pInfo != nullptr )
	{
		_Info = *pInfo;
	}

	_Flags = _flags;
	_BBRatio = BackbufferRatio::Count;
}

XE::Texture::Texture( uint16 _width, uint16 _height, bool _hasMips, uint16 _numLayers, TextureFormat _format, uint64 _flags /*= BGFX_TEXTURE_NONE*/, const MemoryView * _mem /*= nullptr */ )
{
	_Handle = GFX::CreateTexture2D(_width, _height, _hasMips, _numLayers, _format, _flags, _mem);
	
	GFX::CalcTextureSize(_Info, _width, _height, 1, false, _hasMips, _numLayers, _format);

	_Flags = _flags;
	_BBRatio = BackbufferRatio::Count;
}

XE::Texture::Texture( BackbufferRatio _ratio, bool _hasMips, uint16 _numLayers, TextureFormat _format, uint64 _flags /*= BGFX_TEXTURE_NONE */ )
{
	_Handle = GFX::CreateTexture2D(_ratio, _hasMips, _numLayers, _format, _flags);

	uint16 _width = 0;
	uint16 _height = 0;
	GFX::GetSizeFromRatio(_ratio, _width, _height);
	GFX::CalcTextureSize(_Info, _width, _height, 1, false, _hasMips, _numLayers, _format);

	_Flags = _flags;
	_BBRatio = BackbufferRatio::Count;
}

XE::Texture::Texture( uint16 _width, uint16 _height, uint16 _depth, bool _hasMips, TextureFormat _format, uint64 _flags /*= BGFX_TEXTURE_NONE*/, const MemoryView * _mem /*= nullptr */ )
{
	_Handle = GFX::CreateTexture3D(_width, _height, _depth, _hasMips, _format, _flags, _mem);
	
	GFX::CalcTextureSize(_Info, _width, _height, _depth, false, _hasMips, 1, _format);

	_Flags = _flags;
	_BBRatio = BackbufferRatio::Count;
}

XE::Texture::Texture( uint16 _size, bool _hasMips, uint16 _numLayers, TextureFormat _format, uint64 _flags /*= BGFX_TEXTURE_NONE*/, const MemoryView * _mem /*= nullptr */ )
{
	_Handle = GFX::CreateTextureCube(_size, _hasMips, _numLayers, _format, _flags, _mem);
	
	GFX::CalcTextureSize(_Info, _size, _size, _size, false, _hasMips, _numLayers, _format);

	_Flags = _flags;
	_BBRatio = BackbufferRatio::Count;
}

XE::Texture::~Texture()
{
	if (_Handle.idx != UINT16_MAX)
	{
		GFX::Destroy(_Handle);
	}
}

XE::TextureHandle XE::Texture::GetHandle() const
{
	return _Handle;
}

XE::uint64 XE::Texture::GetFlags() const
{
	return _Flags;
}

XE::uint64 XE::Texture::GetWidth() const
{
	if ( _BBRatio == BackbufferRatio::Count )
	{
		return _Info.width;
	}

	uint16 width;
	uint16 height;
	GFX::GetSizeFromRatio(_BBRatio, width, height);

	return width;
}

XE::uint64 XE::Texture::getHeight() const
{
	if ( _BBRatio == BackbufferRatio::Count )
	{
		return _Info.height;
	}

	uint16 width;
	uint16 height;
	GFX::GetSizeFromRatio(_BBRatio, width, height);

	return height;
}

XE::BackbufferRatio XE::Texture::GetBackbufferRatio() const
{
	return _BBRatio;
}

bool XE::Texture::IsRenderTarget() const
{
	return 0 != ( _Flags & BGFX_TEXTURE_RT_MASK );
}
