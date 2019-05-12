/*!
 * \file   FrameBuffer.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __FRAMEBUFFER_H__7902A496_9476_482C_BA63_C1E6B5F683BF
#define __FRAMEBUFFER_H__7902A496_9476_482C_BA63_C1E6B5F683BF

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API FrameBuffer : public XE::Object
{
	OBJECT(FrameBuffer, Object)
	
public:
	struct FBOAttachment
	{
		TexturePtr Texture;
		uint16 Mips;
		uint16 Layer;
	};

public:
	FrameBuffer();

	FrameBuffer( uint16 _width, uint16 _height, TextureFormat _format, uint32 _texture_flags = BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP );

	FrameBuffer( BackbufferRatio _ratio, TextureFormat _format, uint32 _textureFlags = BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP );

	FrameBuffer( const Array<TexturePtr>& textures );

	FrameBuffer( const Array<FBOAttachment>& textures );

	FrameBuffer( void* _nwh, uint16 _width, uint16 _height, TextureFormat _format = TextureFormat::Count, TextureFormat _depth_format = TextureFormat::Count );

	virtual ~FrameBuffer();

public:
	FrameBufferHandle GetHandle() const;

public:
	void populate( const Array<FBOAttachment>& textures );

public:
	XE::uint64 GetWidth() const;

	XE::uint64 GetHeight() const;

	XE::uint64 GetAttchmentCount() const;

	const TexturePtr& GetTexture( XE::uint64 val ) const;

	const FBOAttachment& GetAttchment( XE::uint64 val ) const;

private:
	FrameBufferHandle _Handle;
	
	XE::uint64 _CacheWidth;
	XE::uint64 _CacheHeight;
	BackbufferRatio _BBRatio;
	Array<FBOAttachment> _Textures;
};

END_XE_NAMESAPCE

#endif // __FRAMEBUFFER_H__7902A496_9476_482C_BA63_C1E6B5F683BF
