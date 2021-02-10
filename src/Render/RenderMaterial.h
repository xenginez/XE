/*!
 * \file   RenderMaterial.h
 *
 * \author ZhengYuanQing
 * \date   2021/02/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef RENDERMATERIAL_H__1FE7A840_78C1_4381_913C_2154BF2B5A6E
#define RENDERMATERIAL_H__1FE7A840_78C1_4381_913C_2154BF2B5A6E

#include "Interface/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API RenderMaterial : public XE::Object
{
    OBJECT( RenderMaterial, Object )

public:
    RenderMaterial();

    ~RenderMaterial();

};

END_XE_NAMESPACE

#endif // RENDERMATERIAL_H__1FE7A840_78C1_4381_913C_2154BF2B5A6E
