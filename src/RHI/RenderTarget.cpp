

bool RenderTarget::WriteRed() const
{
    return _WriteRed;
}

void RenderTarget::setWriteRed(bool WriteRed)
{
    _WriteRed = WriteRed;
}

bool RenderTarget::WriteGreen() const
{
    return _WriteGreen;
}

RenderTargetHandle RenderTarget::Handle() const
{
    return _Handle;
}

void RenderTarget::setWriteGreen(bool WriteGreen)
{
    _WriteGreen = WriteGreen;
}

bool RenderTarget::WriteBlue() const
{
    return _WriteBlue;
}

void RenderTarget::setWriteBlue(bool WriteBlue)
{
    _WriteBlue = WriteBlue;
}

bool RenderTarget::WriteAlpha() const
{
    return _WriteAlpha;
}

void RenderTarget::setWriteAlpha(bool WriteAlpha)
{
    _WriteAlpha = WriteAlpha;
}

bool RenderTarget::BlendEnabled() const
{
    return _BlendEnabled;
}

void RenderTarget::setBlendEnabled(bool BlendEnabled)
{
    _BlendEnabled = BlendEnabled;
}

BlendFactor RenderTarget::SrcRgbFunc() const
{
    return _SrcRgbFunc;
}

void RenderTarget::setSrcRgbFunc(const BlendFactor &SrcRgbFunc)
{
    _SrcRgbFunc = SrcRgbFunc;
}

BlendFactor RenderTarget::SrcAlphaFunc() const
{
    return _SrcAlphaFunc;
}

void RenderTarget::setSrcAlphaFunc(const BlendFactor &SrcAlphaFunc)
{
    _SrcAlphaFunc = SrcAlphaFunc;
}

BlendFactor RenderTarget::DstRgbFunc() const
{
    return _DstRgbFunc;
}

void RenderTarget::setDstRgbFunc(const BlendFactor &DstRgbFunc)
{
    _DstRgbFunc = DstRgbFunc;
}

BlendFactor RenderTarget::DstAlphaFunc() const
{
    return _DstAlphaFunc;
}

void RenderTarget::setDstAlphaFunc(const BlendFactor &DstAlphaFunc)
{
    _DstAlphaFunc = DstAlphaFunc;
}

BlendOperation RenderTarget::RgbBlendOp() const
{
    return _RgbBlendOp;
}

void RenderTarget::setRgbBlendOp(const BlendOperation &RgbBlendOp)
{
    _RgbBlendOp = RgbBlendOp;
}

BlendOperation RenderTarget::AlphaBlendOp() const
{
    return _AlphaBlendOp;
}

void RenderTarget::setAlphaBlendOp(const BlendOperation &AlphaBlendOp)
{
    _AlphaBlendOp = AlphaBlendOp;
}

#include "RenderTarget.h"