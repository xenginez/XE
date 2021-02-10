/*!
 * \file   RenderShader.h
 *
 * \author ZhengYuanQing
 * \date   2021/02/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef RENDERSHADER_H__979C25BC_7975_44B1_B6D5_2A1033D93256
#define RENDERSHADER_H__979C25BC_7975_44B1_B6D5_2A1033D93256

#include "Interface/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API RenderShader : public XE::Object
{
    OBJECT( RenderShader, Object )

public:
    RenderShader();

    ~RenderShader();
};

END_XE_NAMESPACE

#endif // RENDERSHADER_H__979C25BC_7975_44B1_B6D5_2A1033D93256
