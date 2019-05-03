#include "FrameBuffer.h"

#include "Texture.h"
#include "GFX.h"

USING_XE

XE::FrameBuffer::FrameBuffer()
	:_CacheWidth( 0 ), _CacheHeight( 0 ), _BBRatio( BackbufferRatio::Equal )
{

}

XE::FrameBuffer::FrameBuffer( uint16 _width, uint16 _height, TextureFormat _format, uint32 _texture_flags /*= BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP */ )
	:_CacheWidth( 0 ), _CacheHeight( 0 ), _BBRatio( BackbufferRatio::Equal )
{
	Array<TexturePtr> textures
	{
		XE::make_shared<Texture>( _width, _height, false, 1, _format, _texture_flags ),
	};

	Array<FBOAttachment> texDescs;
	texDescs.reserve( textures.size() );
	for ( auto& tex : textures )
	{
		FBOAttachment texDesc;
		texDesc.Texture = tex;
		texDescs.push_back( texDesc );
	}

	populate( texDescs );
}

XE::FrameBuffer::FrameBuffer( BackbufferRatio _ratio, TextureFormat _format, uint32 _textureFlags /*= BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP */ )
	: _CacheWidth( 0 ), _CacheHeight( 0 ), _BBRatio( BackbufferRatio::Equal )
{
	Array<TexturePtr> textures
	{
		XE::make_shared<Texture>( _ratio, false, 1, _format, _textureFlags ),
	};

	Array<FBOAttachment> texDescs;
	texDescs.reserve( textures.size() );
	for ( auto& tex : textures )
	{
		FBOAttachment texDesc;
		texDesc.Texture = tex;
		texDescs.push_back( texDesc );
	}

	populate( texDescs );
}

XE::FrameBuffer::FrameBuffer( const Array<TexturePtr>& textures )
	: _CacheWidth( 0 ), _CacheHeight( 0 ), _BBRatio( BackbufferRatio::Equal )
{
	Array<FBOAttachment> texDescs;
	texDescs.reserve( textures.size() );
	for ( auto& tex : textures )
	{
		FBOAttachment texDesc;
		texDesc.Texture = tex;
		texDescs.push_back( texDesc );
	}

	populate( texDescs );
}

XE::FrameBuffer::FrameBuffer( const Array<FBOAttachment>& textures )
	: _CacheWidth( 0 ), _CacheHeight( 0 ), _BBRatio( BackbufferRatio::Equal )
{
	populate( textures );
}

XE::FrameBuffer::FrameBuffer( void* _nwh, uint16 _width, uint16 _height, TextureFormat _format /*= TextureFormat::Count*/, TextureFormat _depth_format /*= TextureFormat::Count */ )
	: _CacheWidth( _width ), _CacheHeight( _height ), _BBRatio( BackbufferRatio::Count )
{
	_Handle = GFX::CreateFrameBuffer(_nwh, _width, _height, _format, _depth_format);
}

XE::FrameBuffer::~FrameBuffer()
{
	if (_Handle.idx != UINT16_MAX)
	{
		GFX::Destroy(_Handle);
	}
}

XE::FrameBufferHandle XE::FrameBuffer::GetHandle() const
{
	return _Handle;
}

void XE::FrameBuffer::populate( const Array<FBOAttachment>& textures )
{
	std::vector<Attachment> buffer;
	buffer.reserve( textures.size() );

	XE::uint64 width = 0;
	XE::uint64 height = 0;
	auto ratio = BackbufferRatio::Count;
	for ( auto& tex : textures )
	{
		ratio = tex.Texture->GetBackbufferRatio();
		width = tex.Texture->GetWidth();
		height = tex.Texture->getHeight();

		Attachment att;
		att.init( tex.Texture->GetHandle(), Access::Write, tex.Layer, tex.Mips );
		buffer.push_back( att );
	}
	_Textures = textures;

	_Handle = GFX::CreateFrameBuffer(static_cast<std::uint8_t>( buffer.size()), &buffer[0], false);

	if ( ratio == BackbufferRatio::Count )
	{
		_BBRatio = ratio;
		_CacheWidth = width;
		_CacheHeight = height;
	}
	else
	{
		_BBRatio = ratio;
		_CacheWidth = 0;
		_CacheHeight = 0;
	}
}

XE::uint64 XE::FrameBuffer::GetWidth() const
{
	if ( _BBRatio == BackbufferRatio::Count )
	{
		return _CacheWidth;
	}

	uint16 width;
	uint16 height;
	GFX::GetSizeFromRatio(_BBRatio, width, height);

	return width;
}

XE::uint64 XE::FrameBuffer::GetHeight() const
{
	if ( _BBRatio == BackbufferRatio::Count )
	{
		return _CacheHeight;
	}

	uint16 width;
	uint16 height;
	GFX::GetSizeFromRatio(_BBRatio, width, height);

	return height;
}

XE::uint64 XE::FrameBuffer::GetAttchmentCount() const
{
	return _Textures.size();
}

const XE::TexturePtr& XE::FrameBuffer::GetTexture( XE::uint64 val ) const
{
	return _Textures[val].Texture;
}

const XE::FrameBuffer::FBOAttachment& XE::FrameBuffer::GetAttchment( XE::uint64 val ) const
{
	return _Textures[val];
}
