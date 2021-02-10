/*!
 * \file   RenderTexture.h
 *
 * \author ZhengYuanQing
 * \date   2021/02/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef RENDERTEXTURE_H__6D94BF3D_23CB_44D4_8789_359A2731D5B9
#define RENDERTEXTURE_H__6D94BF3D_23CB_44D4_8789_359A2731D5B9

#include "Interface/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API RenderTexture : public XE::Object
{
    OBJECT( RenderTexture, Object )

public:
    RenderTexture();

    ~RenderTexture();
};

END_XE_NAMESPACE

#endif // RENDERTEXTURE_H__6D94BF3D_23CB_44D4_8789_359A2731D5B9
