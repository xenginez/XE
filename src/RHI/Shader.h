/*!
 * \file   Shader.h
 *
 * \author ZhengYuanQing
 * \date   2019/06/05
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __SHADER_H__AF709312_F028_4D0A_9FF7_6BD896C33200
#define __SHADER_H__AF709312_F028_4D0A_9FF7_6BD896C33200

#include "Resource.h"

BEG_XE_NAMESPACE

class RHI_API Shader : Resource
{
    OBJECT(Shader, Resource)

public:
    Shader();

    ~Shader() override;

public:
    ShaderHandle GetHandle() const;

public:
    Variant GetVariable( const String& val ) const;

    void SetVariable( const String& name, const Variant& val );

private:
    ShaderHandle _Handle;

    String _Entry;
    Map<String, Variant> _Variables;
};

END_XE_NAMESPACE

#endif // __SHADER_H__AF709312_F028_4D0A_9FF7_6BD896C33200
