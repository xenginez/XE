#include <utility>

#include "Material.h"

#include "GPUProgram.h"

USING_XE

BEGIN_META(Material)
END_META()

XE::Material::Material()
{

}

XE::Material::~Material()
{

}

bool XE::Material::IsValid() const
{
	return false;
}

void
XE::Material::SetTexture( std::uint8_t _stage, const std::string &_sampler, XE::FrameBufferPtr _handle, uint8_t _attachment, uint32_t _flags )
{
	_Program->SetTexture(_stage, _sampler, std::move(_handle), _attachment, _flags);
}

void
XE::Material::SetTexture( std::uint8_t _stage, const std::string &_sampler, XE::TexturePtr _texture, uint32_t _flags )
{
	_Program->SetTexture(_stage, _sampler, std::move(_texture), _flags);
}

void XE::Material::SetUniform( const std::string &_name, const void * _value, uint16_t _num )
{
	_Program->SetUniform(_name, _value, _num);
}

XE::CullType XE::Material::GetCullType() const
{
	return _CullType;
}

void XE::Material::SetCullType( XE::CullType val )
{
	_CullType = val;
}

const Color &Material::GetBaseColor() const
{
	return _BaseColor;
}

void Material::SetBaseColor( const Color &val )
{
	_BaseColor = val;
}

const Color &Material::GetEmissiveColor() const
{
	return _EmissiveColor;
}

void Material::SetEmissiveColor( const Color &val )
{
	_EmissiveColor = val;
}

const Color &Material::GetSubsurfaceColor() const
{
	return _SubsurfaceColor;
}

void Material::SetSubsurfaceColor( const Color &val )
{
	_SubsurfaceColor = val;
}

const Vec2 &Material::GetTiling() const
{
	return _Tiling;
}

void Material::SetTiling( const Vec2 &val )
{
	_Tiling = val;
}

const Vec2 &Material::GetDitherThreshold() const
{
	return _DitherThreshold;
}

void Material::SetDitherThreshold( const Vec2 &val )
{
	_DitherThreshold = val;
}

const Vec4 &Material::GetSurfaceData() const
{
	return _SurfaceData;
}

void Material::SetSurfaceData( const Vec4 &val )
{
	_SurfaceData = val;
}

float Material::GetRoughness() const
{
	return _SurfaceData.x;
}

void Material::SetRoughness( float val )
{
	_SurfaceData.x = val;
}

float Material::GetMetalness() const
{
	return _SurfaceData.y;
}

void Material::SetMetalness( float val )
{
	_SurfaceData.y = val;
}

float Material::GetBumpiness() const
{
	return _SurfaceData.z;
}

void Material::SetBumpiness( float val )
{
	_SurfaceData.z = val;
}

float Material::GetAlphaTest() const
{
	return _SurfaceData.w;
}

void Material::SetAlphaTest( float val )
{
	_SurfaceData.w = val;
}

TexturePtr Material::GetAOTexture() const
{
	return _AOTexture;
}

void Material::SetAOTexture( const TexturePtr &val )
{
	_AOTexture = val;
}

TexturePtr Material::GetAlbedoTexture() const
{
	return _AlbedoTexture;
}

void Material::SetAlbedoTexture( const TexturePtr &val )
{
	_AlbedoTexture = val;
}

TexturePtr Material::GetNormalTexture() const
{
	return _NormalTexture;
}

void Material::SetNormalTexture( const TexturePtr &val )
{
	_NormalTexture = val;
}

TexturePtr Material::GetRoughnessTexture() const
{
	return _RoughnessTexture;
}

void Material::SetRoughnessTexture( const TexturePtr &val )
{
	_RoughnessTexture = val;
}

TexturePtr Material::GetMetalnessTexture() const
{
	return _MetalnessTexture;
}

void Material::SetMetalnessTexture( const TexturePtr &val )
{
	_MetalnessTexture = val;
}

XE::GPUProgramPtr XE::Material::GetProgram() const
{
	return _Program;
}

std::uint64_t XE::Material::GetRenderStates( bool apply_cull, bool depth_write, bool depth_test ) const
{
	std::uint64_t states = BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_MSAA;
	
	if( depth_write )
		states |= BGFX_STATE_WRITE_Z;
	
	if( depth_test )
		states |= BGFX_STATE_DEPTH_TEST_LESS;
	
	if( apply_cull )
	{
		auto cullType = _CullType;
		if( cullType == CullType::COUNTER_CLOCKWISE )
			states |= BGFX_STATE_CULL_CCW;
		if( cullType == CullType::CLOCKWISE )
			states |= BGFX_STATE_CULL_CW;
	}
	
	return states;
}

void XE::Material::Submit()
{
	_Program->SetUniform("base_color", _BaseColor.d);
	_Program->SetUniform("subsurface_color", _SubsurfaceColor.d);
	_Program->SetUniform("emissive_color", _EmissiveColor.d);
	_Program->SetUniform("surface_data", _SurfaceData.d);
	_Program->SetUniform("tiling", _Tiling.d);
	_Program->SetUniform("dither_threshold", _DitherThreshold.d);
	
	_Program->SetTexture(0, "texture_color", _AlbedoTexture);
	_Program->SetTexture(1, "texture_normal", _NormalTexture);
	_Program->SetTexture(2, "texture_roughness", _RoughnessTexture);
	_Program->SetTexture(3, "texture_metalness", _MetalnessTexture);
	_Program->SetTexture(4, "texture_ao", _AOTexture);
}
