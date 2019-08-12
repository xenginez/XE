/*!
 * \file   RenderTarget.h
 *
 * \author ZhengYuanQing
 * \date   2019/06/03
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __RENDERTARGET_H__E417A3B2_CAFF_4125_990A_87B4D2CA876D
#define __RENDERTARGET_H__E417A3B2_CAFF_4125_990A_87B4D2CA876D

#include "Resource.h"

BEG_XE_NAMESPACE

class RHI_API RenderTarget : std::enable_shared_from_this< RenderTarget >
{
	OBJECT( RenderTarget )

public:
	RenderTarget();

	virtual ~RenderTarget();

public:
	RenderTargetHandle GetHandle() const;

public:
	bool GetWriteRed() const;

	void SetWriteRed( bool WriteRed );

	bool GetWriteGreen() const;

	void SetWriteGreen( bool WriteGreen );

	bool GetWriteBlue() const;

	void SetWriteBlue( bool WriteBlue );

	bool GetWriteAlpha() const;

	void SetWriteAlpha( bool WriteAlpha );

	bool GetBlendEnabled() const;

	void SetBlendEnabled( bool BlendEnabled );

	BlendFactor GetSrcRgbFunc() const;

	void SetSrcRgbFunc( const BlendFactor & SrcRgbFunc );

	BlendFactor GetSrcAlphaFunc() const;

	void SetSrcAlphaFunc( const BlendFactor & SrcAlphaFunc );

	BlendFactor GetDstRgbFunc() const;

	void SetDstRgbFunc( const BlendFactor & DstRgbFunc );

	BlendFactor GetDstAlphaFunc() const;

	void SetDstAlphaFunc( const BlendFactor & DstAlphaFunc );

	BlendOperation GetRgbBlendOp() const;

	void SetRgbBlendOp( const BlendOperation & RgbBlendOp );

	BlendOperation GetAlphaBlendOp() const;

	void SetAlphaBlendOp( const BlendOperation & AlphaBlendOp );

public:
	void ClearColor( const Color & val );

	ViewportPtr GetViewport( XE::uint64 val )const;

	const Array<ViewportPtr> & GetViewports() const;

	void SetViewports( const Array<ViewportPtr> & val );

private:
	bool _WriteRed;
	bool _WriteGreen;
	bool _WriteBlue;
	bool _WriteAlpha;
	bool _BlendEnabled;
	BlendFactor _SrcRgbFunc;
	BlendFactor _SrcAlphaFunc;
	BlendFactor _DstRgbFunc;
	BlendFactor _DstAlphaFunc;
	BlendOperation _RgbBlendOp;
	BlendOperation _AlphaBlendOp;

	Array<ViewportPtr> _Viewports;

	RenderContextPtr _Context;
	RenderTargetHandle _Handle;
};

class RHI_API RenderWindow : public RenderTarget
{
	OBJECT( RenderWindow, RenderTarget )

public:
	RenderWindow();

	~RenderWindow() override;

public:
	void Show();

	void Hide();

	void Focus();

	void Minimize();

	void Maximize();

	void Fullscreen();

public:
	bool IsShow() const;

	bool IsHide() const;

	bool IsFocus() const;

	bool IsFullscreen() const;

public:
	XE::uint32 GetPosX() const;

	void SetPosX( XE::uint32 x );

	XE::uint32 GetPosY() const;

	void SetPosY( XE::uint32 y );

	XE::uint32 GetWidth() const;

	void SetWidth( XE::uint32 w );

	XE::uint32 GetHeight() const;

	void SetHeight( XE::uint32 h );

	Vec2 GetSize() const;

	void SetSize( const Vec2 & val );

	Vec2 GetPosition() const;

	void SetPosition( const Vec2 & val );

	const Rect & GetRect() const;

	void SetRect( const Rect & val );

	const String & GetTitle() const;

	void SetTitle( const String & val );

public:
	WindowHandle GetWindowHandle() const;

private:
	bool _Show = true;
	bool _Fullscreen = false;

	Rect _Rect = { 0, 0, 800, 600 };
	String _Title = "XE";

	WindowHandle _Handle;
};

class RHI_API RenderTexture2D : public RenderTarget
{
	OBJECT( RenderTexture2D, RenderTarget )
public:
	RenderTexture2D();

	~RenderTexture2D() override;

public:
	Texture2DPtr GetTexture2D() const;

	void SetTexture2D( const Texture2DPtr & val );

private:
	Texture2DPtr _Texture;
};


END_XE_NAMESPACE

#endif // __RENDERTARGET_H__E417A3B2_CAFF_4125_990A_87B4D2CA876D
