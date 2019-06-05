#include "Shader.h"

USING_XE

BEG_META(Shader)
END_META()

XE::Shader::Shader()
{

}

XE::Shader::~Shader()
{

}

XE::ShaderHandle XE::Shader::GetHandle() const
{
    return _Handle;
}

XE::Variant Shader::GetVariable( const String &val ) const
{
	auto it = _Variables.find(val);
	
	if(it != _Variables.end())
	{
		return it->second;
	}
	
	return Variant();
}

void Shader::SetVariable( const String &name, const Variant &val )
{
	_Variables[name] = val;
}
