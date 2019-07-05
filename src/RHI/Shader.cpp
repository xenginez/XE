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

const XE::String & XE::Shader::GetEntry() const
{
	return _Entry;
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

BEG_META( HullShader )
END_META()

XE::HullShader::HullShader()
{

}

XE::HullShader::~HullShader()
{

}

BEG_META( PixelShader )
END_META()

XE::PixelShader::PixelShader()
{

}

XE::PixelShader::~PixelShader()
{

}

BEG_META( VertexShader )
END_META()

XE::VertexShader::VertexShader()
{

}

XE::VertexShader::~VertexShader()
{

}

BEG_META( DomainShader )
END_META()

XE::DomainShader::DomainShader()
{

}

XE::DomainShader::~DomainShader()
{

}

BEG_META( ComputeShader )
END_META()

XE::ComputeShader::ComputeShader()
{

}

XE::ComputeShader::~ComputeShader()
{

}

BEG_META( GeometryShader )
END_META()

XE::GeometryShader::GeometryShader()
{

}

XE::GeometryShader::~GeometryShader()
{

}
