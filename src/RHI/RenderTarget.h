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

class RHI_API RenderTarget : Resource
{
	OBJECT(RenderTarget, Resource)
	
public:
    RenderTarget();

    ~RenderTarget() override;

public:
    RenderTargetHandle Handle() const;

public:
    bool GetWriteRed() const;

    void SetWriteRed(bool WriteRed);

    bool GetWriteGreen() const;

    void SetWriteGreen(bool WriteGreen);

    bool GetWriteBlue() const;

    void SetWriteBlue(bool WriteBlue);

    bool GetWriteAlpha() const;

    void SetWriteAlpha(bool WriteAlpha);

    bool GetBlendEnabled() const;

    void SetBlendEnabled(bool BlendEnabled);

    BlendFactor GetSrcRgbFunc() const;

    void SetSrcRgbFunc(const BlendFactor &SrcRgbFunc);

    BlendFactor GetSrcAlphaFunc() const;

    void SetSrcAlphaFunc(const BlendFactor &SrcAlphaFunc);

    BlendFactor GetDstRgbFunc() const;

    void SetDstRgbFunc(const BlendFactor &DstRgbFunc);

    BlendFactor GetDstAlphaFunc() const;

    void SetDstAlphaFunc(const BlendFactor &DstAlphaFunc);

    BlendOperation GetRgbBlendOp() const;

    void SetRgbBlendOp(const BlendOperation &RgbBlendOp);

    BlendOperation GetAlphaBlendOp() const;

    void SetAlphaBlendOp(const BlendOperation &AlphaBlendOp);

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

    RenderTargetHandle _Handle;
};

END_XE_NAMESPACE

#endif // __RENDERTARGET_H__E417A3B2_CAFF_4125_990A_87B4D2CA876D
