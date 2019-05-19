/*!
 * \file    Renderer.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-15
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __RENDERER_H__110C5558_6667_4730_BB09_61799EF40CE0
#define __RENDERER_H__110C5558_6667_4730_BB09_61799EF40CE0

#include "Type.h"

BEG_XE_NAMESPACE

class RHI_API Renderer : public XE::Object
{
	OBJECT(Renderer, Object)
	
public:
	Renderer();
	
	~Renderer() override;

public:
	virtual void Startup() = 0;
	
	virtual void Clearup() = 0;

public:
	virtual RendererType GetType() const = 0;

public:
	virtual WindowHandle CreateWindow( uint64 native_handle ) = 0;
	
	virtual WindowHandle CreateWindow( const String &title, const Rect &rect ) = 0;
	
	virtual void DestroyWindow( const WindowHandle &handle ) = 0;
	
	virtual void ShowWindow( const WindowHandle &handle ) = 0;
	
	virtual void HideWindow( const WindowHandle &handle ) = 0;
	
	virtual void MinimizeWindow( const WindowHandle &handle ) = 0;
	
	virtual void MaximizeWindow( const WindowHandle &handle ) = 0;
	
	virtual void FullscreenWindow( const WindowHandle &handle ) = 0;
	
	virtual bool GetWindowGrab( const WindowHandle &handle ) = 0;
	
	virtual void SetWindowGrab( const WindowHandle &handle, bool grab ) = 0;
	
	virtual Rect GetWindowRect( const WindowHandle &handle ) = 0;
	
	virtual void SetWindowRect( const WindowHandle &handle, const Rect &rect ) = 0;
	
	virtual Vec2 GetWindowSize( const WindowHandle &handle ) = 0;
	
	virtual void SetWindowSize( const WindowHandle &handle, const Vec2 &size ) = 0;
	
	virtual Vec2 GetWindowPosition( const WindowHandle &handle ) = 0;
	
	virtual void SetWindowPosition( const WindowHandle &handle, const Vec2 &pos ) = 0;
	
	virtual String GetWindowIcon( const WindowHandle &handle ) = 0;
	
	virtual void SetWindowIcon( const WindowHandle &handle, const String &Icon ) = 0;
	
	virtual String GetWindowTitle( const WindowHandle &handle ) = 0;
	
	virtual void SetWindowTitle( const WindowHandle &handle, const String &title ) = 0;
	
public:
	virtual IndexBufferHandle CreateIndexBuffer( const Array < uint8 > &val ) = 0;
	
	virtual VertexBufferHandle CreateVertexBuffer( const Array < uint8 > &val ) = 0;
	
	virtual DynamicIndexBufferHandle CreateDynamicIndexBuffer( uint64 size ) = 0;
	
	virtual DynamicVertexBufferHandle CreateDynamicVertexBuffer( uint64 size ) = 0;
	
	virtual DynamicIndexBufferHandle CreateDynamicIndexBuffer( const Array < uint8 > &val ) = 0;
	
	virtual DynamicVertexBufferHandle CreateDynamicVertexBuffer( const Array < uint8 > &val ) = 0;
	
	virtual HullShaderHandle CreateHullShader( const Array < uint8 > &val ) = 0;
	
	virtual HullShaderHandle CreateHullShader( const std::filesystem::path &val ) = 0;
	
	virtual PixelShaderHandle CreatePixelShader( const Array < uint8 > &val ) = 0;
	
	virtual PixelShaderHandle CreatePixelShader( const std::filesystem::path &val ) = 0;
	
	virtual VertexShaderHandle CreateVertexShader( const Array < uint8 > &val ) = 0;
	
	virtual VertexShaderHandle CreateVertexShader( const std::filesystem::path &val ) = 0;
	
	virtual DomainShaderHandle CreateDomainShader( const Array < uint8 > &val ) = 0;
	
	virtual DomainShaderHandle CreateDomainShader( const std::filesystem::path &val ) = 0;
	
	virtual ComputeShaderHandle CreateComputeShader( const Array < uint8 > &val ) = 0;
	
	virtual ComputeShaderHandle CreateComputeShader( const std::filesystem::path &val ) = 0;
	
	virtual TessellationShaderHandle CreateTessellationShader( const Array < uint8 > &val ) = 0;
	
	virtual TessellationShaderHandle CreateTessellationShader( const std::filesystem::path &val ) = 0;
	
	virtual ProgramHandle CreateProgram( const ComputeShaderHandle &cs ) = 0;
	
	virtual ProgramHandle CreateProgram( const VertexShaderHandle &vs, const PixelShaderHandle &ps ) = 0;
	
	virtual UniformHandle CreateUniform( const ProgramHandle& program, const String& val ) = 0;
	
	virtual TextureHandle CreateTexture2D( const Vec2 &size, uint16 mips, uint16 players, TextureFormat format ) = 0;
	
	virtual TextureHandle CreateTexture3D( const Vec3 &size, uint16 mips, uint16 players, TextureFormat format ) = 0;
	
	virtual TextureHandle CreateTextureCube( uint16 size, uint16 mips, uint16 players, TextureFormat format ) = 0;
	
	virtual FrameBufferHandle CreateFrameBuffer( const Vec2 &size, TextureHandle texture, TextureHandle depth ) = 0;
	
	virtual ViewportHandle
	CreateViewport( const Rect &rect, const FrameBufferHandle &frame, const Color &clear_color ) = 0;
	
};

END_XE_NAMESAPCE

#endif //__RENDERER_H__110C5558_6667_4730_BB09_61799EF40CE0
