#include "Program.h"

#include "Shader.h"
#include "Uniform.h"
#include "Texture.h"
#include "GFX.h"
#include "FrameBuffer.h"

USING_XE

XE::Program::Program()
{

}

XE::Program::Program( ShaderPtr compute_shader )
{
	if ( compute_shader )
	{
		_Handle = GFX::CreateProgram(compute_shader->GetHandle());

		for ( auto& uniform : compute_shader->GetUniforms() )
		{
			_Uniforms[uniform->GetInfo().name] = uniform;
		}
	}
}

XE::Program::Program( ShaderPtr vertex_shader, ShaderPtr fragment_shader )
{
	if ( vertex_shader && fragment_shader )
	{
		_Handle = GFX::CreateProgram(vertex_shader->GetHandle(), fragment_shader->GetHandle());

		for ( auto& uniform : vertex_shader->GetUniforms() )
		{
			_Uniforms[uniform->GetInfo().name] = uniform;
		}

		for ( auto& uniform : fragment_shader->GetUniforms() )
		{
			_Uniforms[uniform->GetInfo().name] = uniform;
		}
	}
}

XE::Program::~Program()
{
	if ( _Handle.idx != UINT16_MAX )
	{
		GFX::Destroy(_Handle);
	}
}

XE::ProgramHandle XE::Program::GetHandle() const
{
	return _Handle;
}

void XE::Program::SetTexture( uint8 _stage, const String& _sampler, FrameBufferPtr frameBuffer, uint8 _attachment /*= 0*/, uint32 _flags /*= std::numeric_limits<uint32>::max() */ )
{
	if ( frameBuffer == nullptr )
	{
		return;
	}
	
	GFX::SetTexture(_stage, GetUniform(_sampler, true)->GetHandle(), frameBuffer->GetTexture(_attachment)->GetHandle(), _flags);
}

void XE::Program::SetTexture( uint8 _stage, const String& _sampler, TexturePtr _texture, uint32 _flags /*= std::numeric_limits<uint32>::max() */ )
{
	if ( _texture == nullptr )
	{
		return;
	}
	
	GFX::SetTexture(_stage, GetUniform(_sampler, true)->GetHandle(), _texture->GetHandle(), _flags);
}

void XE::Program::SetUniform( const String& _name, const void* _value, uint16 _num /*= 1 */ )
{
	auto uniform = GetUniform( _name );

	if ( uniform )
	{
		GFX::SetUniform(uniform->GetHandle(), _value, _num);
	}
}

XE::UniformPtr XE::Program::GetUniform( const String& _name, bool texture /*= false */ )
{
	UniformPtr hUniform;
	auto it = _Uniforms.find( _name );
	if ( it != _Uniforms.end() )
	{
		hUniform = it->second;
	}
	else
	{
		if ( texture )
		{
			hUniform = XE::make_shared<Uniform>( _name, UniformType::Sampler, 1 );
			_Uniforms[_name] = hUniform;
		}
	}

	return hUniform;
}
