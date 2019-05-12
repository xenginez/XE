#include "Shader.h"

#include "Uniform.h"
#include "GFX.h"

USING_XE

BEGIN_META(Shader)
END_META()

XE::Shader::Shader()
{

}

XE::Shader::Shader( const MemoryView * _mem )
{
	_Handle = GFX::CreateShader(_mem);
}

XE::Shader::Shader( const EmbeddedShader * _es, const String& name )
{
	_Handle = GFX::CreateEmbeddedShader(_es, GFX::GetRendererType(), name);
}

XE::Shader::Shader( ShaderHandle hndl )
{
	_Handle = hndl;

	auto uniform_count = GFX::GetShaderUniforms(_Handle);
	if ( uniform_count > 0 )
	{
		Array<UniformHandle> uniforms_handles( uniform_count );
		GFX::GetShaderUniforms(_Handle, &uniforms_handles[0], uniform_count);
		_Uniforms.reserve( uniform_count );
		for ( auto& uni : uniforms_handles )
		{
			_Uniforms.emplace_back( XE::make_shared<Uniform>( uni ) );
		}
	}
}

XE::Shader::~Shader()
{
	if ( _Handle.idx != UINT16_MAX )
	{
		GFX::Destroy(_Handle);
	}
}

XE::ShaderHandle XE::Shader::GetHandle() const
{
	return _Handle;
}

XE::uint64 XE::Shader::GetUniformCount() const
{
	return _Uniforms.size();
}

XE::UniformPtr XE::Shader::GetUniform( XE::uint64 val ) const
{
	return _Uniforms[val];
}

const XE::Array<XE::UniformPtr>& XE::Shader::GetUniforms() const
{
	return _Uniforms;
}
