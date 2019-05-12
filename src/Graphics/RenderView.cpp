#include "RenderView.h"

#include "Texture.h"
#include "GFX.h"
#include "FrameBuffer.h"

USING_XE

BEGIN_META(RenderView)
END_META()

XE::TexturePtr XE::RenderView::GetTexture( const String& id, XE::uint64 _width, XE::uint64 _height, bool _hasMips, uint16 _numLayers, TextureFormat _format, uint64 _flags, const MemoryView * _mem /*= nullptr */ )
{
	TextureKey key;
	GFX::CalcTextureSize(key.Info, ( uint16 ) _width, ( uint16 ) _height, 1, false, _hasMips, _numLayers, _format);

	key.ID = id;
	key.Flags = _flags;
	key.Ratio = BackbufferRatio::Count;

	TexturePtr tex;
	auto it = textures_.find( key );
	if ( it != textures_.end() )
	{
		tex = it->second.first;
		it->second.second = true;
	}
	else
	{
		tex = XE::make_shared<Texture>( (uint16)_width, (uint16)_height, _hasMips, _numLayers, _format, _flags, _mem );
		textures_[key] = std::make_pair( tex, true );
	}

	return tex;
}

XE::TexturePtr XE::RenderView::GetTexture( const String& id, BackbufferRatio _ratio, bool _hasMips, uint16 _numLayers, TextureFormat _format, uint64 _flags )
{
	TextureKey key;
	uint16 _width = 0;
	uint16 _height = 0;
	GFX::GetSizeFromRatio(_ratio, _width, _height);
	GFX::CalcTextureSize(key.Info, _width, _height, 1, false, _hasMips, _numLayers, _format);

	key.ID = id;
	key.Flags = _flags;
	key.Ratio = _ratio;

	TexturePtr tex;
	auto it = textures_.find( key );
	if ( it != textures_.end() )
	{
		tex = it->second.first;
		it->second.second = true;
	}
	else
	{
		tex = XE::make_shared<Texture>( _width, _height, _hasMips, _numLayers, _format, _flags );
		textures_[key] = std::make_pair( tex, true );
	}

	return tex;
}

XE::TexturePtr XE::RenderView::GetTexture( const String& id, XE::uint64 _width, XE::uint64 _height, uint16 _depth, bool _hasMips, TextureFormat _format, uint64 _flags, const MemoryView * _mem /*= nullptr */ )
{
	TextureKey key;
	GFX::CalcTextureSize(key.Info, ( uint16 ) _width, ( uint16 ) _height, _depth, false, _hasMips, 1, _format);

	key.ID = id;
	key.Flags = _flags;
	key.Ratio = BackbufferRatio::Count;

	TexturePtr tex;
	auto it = textures_.find( key );
	if ( it != textures_.end() )
	{
		tex = it->second.first;
		it->second.second = true;
	}
	else
	{
		tex = XE::make_shared<Texture>( (uint16)_width, (uint16)_height, _depth, _hasMips, _format, _flags, _mem );
		textures_[key] = std::make_pair( tex, true );
	}

	return tex;
}

XE::TexturePtr XE::RenderView::GetTexture( const String& id, uint16 _size, bool _hasMips, uint16 _numLayers, TextureFormat _format, uint64 _flags, const MemoryView * _mem /*= nullptr */ )
{
	TextureKey key;
	GFX::CalcTextureSize(key.Info, _size, _size, _size, false, _hasMips, _numLayers, _format);

	key.ID = id;
	key.Flags = _flags;
	key.Ratio = BackbufferRatio::Count;

	TexturePtr tex;
	auto it = textures_.find( key );
	if ( it != textures_.end() )
	{
		tex = it->second.first;
		it->second.second = true;
	}
	else
	{
		tex = XE::make_shared<Texture>( _size, _hasMips, _numLayers, _format, _flags, _mem );
		textures_[key] = std::make_pair( tex, true );
	}

	return tex;
}

XE::FrameBufferPtr XE::RenderView::GetFBO( const String& id, const Array<TexturePtr>& bind_textures )
{
	FBOKey key;

	key.ID = id;
	key.Textures = bind_textures;

	FrameBufferPtr tex;
	auto it = fbos_.find( key );
	if ( it != fbos_.end() )
	{
		tex = it->second.first;
		it->second.second = true;
	}
	else
	{
		tex = XE::make_shared<FrameBuffer>( bind_textures );
		fbos_[key] = std::make_pair( tex, true );
	}

	return tex;
}

XE::TexturePtr XE::RenderView::GetDepthStencilBuffer( XE::uint64 _width, XE::uint64 _height )
{
	static auto format = GFX::GetBestFormat(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER,
											( uint32 ) FormatSearchFlags::REQUIRES_DEPTH |
											( uint32 ) FormatSearchFlags::REQUIRES_STENCIL);
	return GetTexture( "DEPTH_STENCIL", _width, _height, false, 1, format, GFX::GetDefaultRtSamplerFlags() );
}

XE::TexturePtr XE::RenderView::GetDepthBuffer( XE::uint64 _width, XE::uint64 _height )
{
	static auto format = GFX::GetBestFormat(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER, ( uint32 ) FormatSearchFlags::REQUIRES_DEPTH);
	return GetTexture( "DEPTH", _width, _height, false, 1, format, GFX::GetDefaultRtSamplerFlags() );
}

XE::TexturePtr XE::RenderView::GetOutputBuffer( XE::uint64 _width, XE::uint64 _height )
{
	static auto format = GFX::GetBestFormat(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER,
											( uint32 ) FormatSearchFlags::FOUR_CHANNELS |
											( uint32 ) FormatSearchFlags::REQUIRES_ALPHA);
	return GetTexture( "OUTPUT", _width, _height, false, 1, format, GFX::GetDefaultRtSamplerFlags() );
}

XE::FrameBufferPtr XE::RenderView::GetOutput( XE::uint64 _width, XE::uint64 _height )
{
	return GetFBO( "OUTPUT", { GetOutputBuffer( _width, _height ), GetDepthBuffer( _width, _height ) } );
}

XE::FrameBufferPtr XE::RenderView::GetGBuffer( XE::uint64 _width, XE::uint64 _height )
{
	static auto format = GFX::GetBestFormat(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER,
											( uint32 ) FormatSearchFlags::FOUR_CHANNELS |
											( uint32 ) FormatSearchFlags::REQUIRES_ALPHA);
	static auto normal_format = GFX::GetBestFormat(BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER,
												   ( uint32 ) FormatSearchFlags::FOUR_CHANNELS |
												   ( uint32 ) FormatSearchFlags::REQUIRES_ALPHA |
												   ( uint32 ) FormatSearchFlags::HALF_PRECISION_FLOAT);
	auto depth_buffer = GetDepthBuffer( _width, _height );
	auto buffer0 = GetTexture( "GBUFFER0", _width, _height, false, 1, format, GFX::GetDefaultRtSamplerFlags() );
	auto buffer1 =
		GetTexture( "GBUFFER1", _width, _height, false, 1, normal_format, GFX::GetDefaultRtSamplerFlags() );
	auto buffer2 = GetTexture( "GBUFFER2", _width, _height, false, 1, format, GFX::GetDefaultRtSamplerFlags() );
	auto buffer3 = GetTexture( "GBUFFER3", _width, _height, false, 1, format, GFX::GetDefaultRtSamplerFlags() );
	return GetFBO( "GBUFFER", { buffer0, buffer1, buffer2, buffer3, depth_buffer } );
}

void XE::RenderView::ReleaseUnusedResources()
{
	auto check_resources = [] ( auto& associativie_container )
	{
		for ( auto it = associativie_container.begin(); it != associativie_container.end();)
		{
			auto& item = it->second.first;
			bool& used_last_frame = it->second.second;

			if ( !used_last_frame && item.use_count() == 1 )
			{
				it = associativie_container.erase( it );
			}
			else
			{
				used_last_frame = false;
				it++;
			}
		}
	};

	check_resources( fbos_ );
	check_resources( textures_ );
}
