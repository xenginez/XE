#include "RenderTarget.h"

USING_XE

BEG_META(RenderTarget)
END_META()

XE::RenderTarget::RenderTarget()
{

}

XE::RenderTarget::~RenderTarget()
{

}

bool XE::RenderTarget::GetWriteRed() const
{
	return _WriteRed;
}

void XE::RenderTarget::SetWriteRed( bool WriteRed )
{
	_WriteRed = WriteRed;
}

bool XE::RenderTarget::GetWriteGreen() const
{
	return _WriteGreen;
}

XE::RenderTargetHandle XE::RenderTarget::Handle() const
{
	return _Handle;
}

void XE::RenderTarget::SetWriteGreen( bool val )
{
	_WriteGreen = val;
}

bool XE::RenderTarget::GetWriteBlue() const
{
	return _WriteBlue;
}

void XE::RenderTarget::SetWriteBlue( bool val )
{
	_WriteBlue = val;
}

bool XE::RenderTarget::GetWriteAlpha() const
{
	return _WriteAlpha;
}

void XE::RenderTarget::SetWriteAlpha( bool val )
{
	_WriteAlpha = val;
}

bool XE::RenderTarget::GetBlendEnabled() const
{
	return _BlendEnabled;
}

void XE::RenderTarget::SetBlendEnabled( bool val )
{
	_BlendEnabled = val;
}

XE::BlendFactor XE::RenderTarget::GetSrcRgbFunc() const
{
	return _SrcRgbFunc;
}

void XE::RenderTarget::SetSrcRgbFunc( const XE::BlendFactor &val )
{
	_SrcRgbFunc = val;
}

XE::BlendFactor XE::RenderTarget::GetSrcAlphaFunc() const
{
	return _SrcAlphaFunc;
}

void XE::RenderTarget::SetSrcAlphaFunc( const XE::BlendFactor &val )
{
	_SrcAlphaFunc = val;
}

XE::BlendFactor XE::RenderTarget::GetDstRgbFunc() const
{
	return _DstRgbFunc;
}

void XE::RenderTarget::SetDstRgbFunc( const XE::BlendFactor &val )
{
	_DstRgbFunc = val;
}

XE::BlendFactor XE::RenderTarget::GetDstAlphaFunc() const
{
	return _DstAlphaFunc;
}

void XE::RenderTarget::SetDstAlphaFunc( const XE::BlendFactor &val )
{
	_DstAlphaFunc = val;
}

XE::BlendOperation XE::RenderTarget::GetRgbBlendOp() const
{
	return _RgbBlendOp;
}

void XE::RenderTarget::SetRgbBlendOp( const BlendOperation &val )
{
	_RgbBlendOp = val;
}

XE::BlendOperation XE::RenderTarget::GetAlphaBlendOp() const
{
	return _AlphaBlendOp;
}

void XE::RenderTarget::SetAlphaBlendOp( const BlendOperation &val )
{
	_AlphaBlendOp = val;
}
