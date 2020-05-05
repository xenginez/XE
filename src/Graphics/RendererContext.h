/*!
 * \file	RendererContext.h
 *
 * \author	ZhengYuanQing
 * \date	2020/04/05
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RENDERERCONTEXT_H__759BB776_4331_4BA8_AAB0_8AA62934A3A5
#define RENDERERCONTEXT_H__759BB776_4331_4BA8_AAB0_8AA62934A3A5

#include "Type.h"

BEG_XE_NAMESPACE

class RendererContext
{
private:
	struct Private;

public:
	RendererContext();

	virtual ~RendererContext();

public:
	virtual XE::Caps GetCaps() = 0;

	virtual XE::RendererContextType GetType() = 0;

public:
	virtual void Init( const InitInfo & val ) = 0;

	virtual void Shutdown() = 0;

	void Reset( XE::uint32 width, XE::uint32 height, XE::Flags<XE::ResetFlag> flags = XE::ResetFlag::NONE, XE::TextureFormat format = XE::TextureFormat::COUNT );

public:
	XE::Encoder * Begin( bool forthread = false );

	void End( XE::Encoder * val );

	XE::uint32 Frame( bool capture = false );

public:
	void SetDebug( XE::Flags<XE::DebugFlag> flags = XE::DebugFlag::NONE );

	void DebugTextClear();

	void DebugTextPrint( XE::uint32 x, XE::uint32 y, const XE::Color & color, const std::string & text );

public:
	XE::Array<UniformHandle> GetShaderUniforms( ShaderHandle handle );

	XE::uint8 * GetDirectAccess( TextureHandle handle );

	TextureHandle GetTexture( FrameBufferHandle handle, XE::uint8 attachment = 0 );

	const UniformInfo & GetUniformInfo( UniformHandle handle );

	OcclusionQueryResult GetOcclusionQueryResult( OcclusionQueryHandle handle );

	std::optional<XE::uint32> GetOcclusionQueryValue( OcclusionQueryHandle handle );

public:
	void SetViewName( ViewHandle handle, const XE::String & name );

	void SetViewRect( ViewHandle handle, const XE::Rect & rect );

	void SetViewScissor( ViewHandle handle, const XE::Rect & scissor );

	void SetViewClear( ViewHandle handle,
					   std::optional<XE::Color> color = std::nullopt,
					   std::optional<XE::float32> depth = std::nullopt,
					   std::optional<XE::uint8> stencil = std::nullopt );

	void SetViewMode( ViewHandle handle, XE::ViewMode mode = ViewMode::Default );

	void SetViewFrameBuffer( ViewHandle handle, FrameBufferHandle frame );

	void SetViewTransform( ViewHandle handle, const XE::Mat4 & transform );

	void SetViewOrder( ViewHandle handle, const XE::Array<ViewHandle> & remap );

	void ResetView( ViewHandle handle );

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // RENDERERCONTEXT_H__759BB776_4331_4BA8_AAB0_8AA62934A3A5
