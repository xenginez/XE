#include "Shader.h"

USING_XE

BEG_META(Shader)
END_META()

ShaderHandle Shader::GetHandle() const
{
    return _Handle;
}
