/*!
 * \file   Texture.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TEXTURE_H__7C9C646C_5F5F_4282_88B5_F4F9CFA7CC12
#define __TEXTURE_H__7C9C646C_5F5F_4282_88B5_F4F9CFA7CC12

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API Texture : public std::enable_shared_from_this<Texture>
{
public:
	Texture();

	Texture( const MemoryView * _mem, uint64 _flags = BGFX_TEXTURE_NONE, uint8 _skip = 0, TextureInfo * _info = nullptr );

	Texture( uint16 _width, uint16 _height, bool _hasMips, uint16 _numLayers, TextureFormat _format, uint64 _flags = BGFX_TEXTURE_NONE, const MemoryView * _mem = nullptr );

	Texture( BackbufferRatio _ratio, bool _hasMips, uint16 _numLayers, TextureFormat _format, uint64 _flags = BGFX_TEXTURE_NONE );

	Texture( uint16 _width, uint16 _height, uint16 _depth, bool _hasMips, TextureFormat _format, uint64 _flags = BGFX_TEXTURE_NONE, const MemoryView * _mem = nullptr );

	Texture( uint16 _size, bool _hasMips, uint16 _numLayers, TextureFormat _format, uint64 _flags = BGFX_TEXTURE_NONE, const MemoryView * _mem = nullptr );

	~Texture();

public:
	TextureHandle GetHandle() const;

public:
	uint64 GetFlags() const;

	XE::uint64 GetWidth() const;

	XE::uint64 getHeight() const;

	BackbufferRatio GetBackbufferRatio() const;

public:
	bool IsRenderTarget() const;

private:
	TextureHandle _Handle;

	uint64 _Flags;
	TextureInfo _Info;
	BackbufferRatio _BBRatio = BackbufferRatio::Count;
};

END_XE_NAMESAPCE

#endif // __TEXTURE_H__7C9C646C_5F5F_4282_88B5_F4F9CFA7CC12
