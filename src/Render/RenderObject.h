/*!
 * \file   RenderObject.h
 *
 * \author ZhengYuanQing
 * \date   2021/02/11
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef RENDEROBJECT_H__87D5B39C_8E1C_470E_A272_FA45B8C47FCE
#define RENDEROBJECT_H__87D5B39C_8E1C_470E_A272_FA45B8C47FCE

#include "Interface/Object.h"

BEG_XE_NAMESPACE

class XE_API RenderObject : public XE::Object
{
    OBJECT( RenderObject, Object )

public:
    RenderObject();

    ~RenderObject();


};

END_XE_NAMESPACE

#endif // RENDEROBJECT_H__87D5B39C_8E1C_470E_A272_FA45B8C47FCE
