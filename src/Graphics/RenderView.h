/*!
 * \file   RenderView.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __RENDERVIEW_H__01ED7EBE_EF2D_4A72_BE16_818009488F75
#define __RENDERVIEW_H__01ED7EBE_EF2D_4A72_BE16_818009488F75

#include "RenderKey.h"

BEG_XE_NAMESPACE

class GRAPHICS_API RenderView : public std::enable_shared_from_this<RenderView>
{
public:
	TexturePtr GetTexture( const String& id, XE::uint64 _width, XE::uint64 _height, bool _hasMips, uint16 _numLayers, TextureFormat _format, uint64 _flags, const MemoryView * _mem = nullptr );

	TexturePtr GetTexture( const String& id, BackbufferRatio _ratio, bool _hasMips, uint16 _numLayers, TextureFormat _format, uint64 _flags );

	TexturePtr GetTexture( const String& id, XE::uint64 _width, XE::uint64 _height, uint16 _depth, bool _hasMips, TextureFormat _format, uint64 _flags, const MemoryView * _mem = nullptr );

	TexturePtr GetTexture( const String& id, uint16 _size, bool _hasMips, uint16 _numLayers, TextureFormat _format, uint64 _flags, const MemoryView * _mem = nullptr );

	FrameBufferPtr GetFBO( const String& id, const Array<TexturePtr>& bind_textures );

	TexturePtr GetDepthStencilBuffer( XE::uint64 _width, XE::uint64 _height );

	TexturePtr GetDepthBuffer( XE::uint64 _width, XE::uint64 _height );

	TexturePtr GetOutputBuffer( XE::uint64 _width, XE::uint64 _height );

	FrameBufferPtr GetOutput( XE::uint64 _width, XE::uint64 _height );

	FrameBufferPtr GetGBuffer( XE::uint64 _width, XE::uint64 _height );

	void ReleaseUnusedResources();

private:
	UnorderedMap<FBOKey, Pair<FrameBufferPtr, bool>> fbos_;
	UnorderedMap<TextureKey, Pair<TexturePtr, bool>> textures_;
};

END_XE_NAMESAPCE

#endif // __RENDERVIEW_H__01ED7EBE_EF2D_4A72_BE16_818009488F75
