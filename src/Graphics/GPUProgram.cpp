#include "GPUProgram.h"

#include "Shader.h"
#include "Program.h"
#include "FrameBuffer.h"

USING_XE

XE::GPUProgram::GPUProgram( ShaderPtr compute_shader )
{
	attach_shader( compute_shader );
	populate();
}

XE::GPUProgram::GPUProgram( ShaderPtr vertex_shader, ShaderPtr fragment_shader )
{
	attach_shader( vertex_shader );
	attach_shader( fragment_shader );
	populate();
}

XE::ProgramHandle XE::GPUProgram::GetHandle() const
{
	return _Program->GetHandle();
}

bool XE::GPUProgram::Begin()
{
	bool repopulate = false;
	for ( XE::uint64 i = 0; i < _ShadersCached.size(); ++i )
	{
		auto shader_ptr = _Shaders[i];
		if ( !shader_ptr )
			continue;

		if ( _ShadersCached[i] != shader_ptr->GetHandle().idx )
		{
			repopulate = true;
			break;
		}
	}

	if ( repopulate )
		populate();

	return _Program->GetHandle().idx != UINT16_MAX;
}

void XE::GPUProgram::End()
{

}

void XE::GPUProgram::SetTexture( uint8 _stage, const String& _sampler, FrameBufferPtr _frameBuffer, uint8 _attachment /*= 0*/, uint32 _flags /*= std::numeric_limits<uint32>::max() */ )
{
	_Program->SetTexture( _stage, _sampler, _frameBuffer, _attachment, _flags );
}

void XE::GPUProgram::SetTexture( uint8 _stage, const String& _sampler, TexturePtr _texture, uint32 _flags /*= std::numeric_limits<uint32>::max() */ )
{
	_Program->SetTexture( _stage, _sampler, _texture, _flags );
}

void XE::GPUProgram::SetUniform( const String& _name, const Vec2& _value, uint16 _num /*= 1 */ )
{
	SetUniform( _name, Vec4( _value.x, _value.y, 0, 0 ), _num );
}

void XE::GPUProgram::SetUniform( const String& _name, const Vec3& _value, uint16 _num /*= 1 */ )
{
	SetUniform( _name, Vec4( _value.x, _value.y, _value.z, 0 ), _num );
}

void XE::GPUProgram::SetUniform( const String& _name, const Vec4& _value, uint16 _num /*= 1 */ )
{
	SetUniform( _name, _value.d, _num );
}

void XE::GPUProgram::SetUniform( const String& _name, const void* _value, uint16 _num /*= 1 */ )
{
	_Program->SetUniform( _name, _value, _num );
}

XE::UniformPtr XE::GPUProgram::GetUniform( const String& _name, bool texture /*= false */ )
{
	return _Program->GetUniform( _name, texture );
}

const XE::Array<XE::ShaderPtr>& XE::GPUProgram::GetShaders() const
{
	return _Shaders;
}

void XE::GPUProgram::populate()
{
	bool all_valid = std::all_of( std::begin( _Shaders ), std::end( _Shaders ),
								  [] ( auto& shader ) { return shader && shader->GetHandle().idx != UINT16_MAX; } );

	if ( all_valid )
	{
		if ( _Shaders.size() == 1 )
		{
			auto compute_shader = _Shaders[0];
			_Program = XE::make_shared<Program>( compute_shader );
		}
		else if ( _Shaders.size() == 2 )
		{
			auto vertex_shader = _Shaders[0];
			auto fragment_shader = _Shaders[1];
			_Program = XE::make_shared<Program>( vertex_shader, fragment_shader );
		}

		_ShadersCached.clear();
		for ( const auto& shader : _Shaders )
		{
			_ShadersCached.push_back( shader->GetHandle().idx );
		}
	}
}

void XE::GPUProgram::attach_shader( ShaderPtr shader )
{
	if ( !shader )
	{
		_ShadersCached.push_back( UINT16_MAX );
		_Shaders.push_back( shader );
		return;
	}

	_ShadersCached.push_back( shader->GetHandle().idx );
	_Shaders.push_back( shader );
}
