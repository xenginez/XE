/*!
 * \file   Material.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/29
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __MATERIAL_H__DA1798CB_BC0C_4DB6_A9E4_C9D890E75DD6
#define __MATERIAL_H__DA1798CB_BC0C_4DB6_A9E4_C9D890E75DD6

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API Material : public Object
{
	OBJECT( Material, Object )
	
public:
	Material();
	
	~Material();

public:
	bool IsValid() const;
	
	void SetTexture( std::uint8_t _stage, const std::string &_sampler, FrameBufferPtr _handle, uint8_t _attachment = 0, std::uint32_t _flags = std::numeric_limits < std::uint32_t >::max());
	
	void SetTexture( std::uint8_t _stage, const std::string &_sampler, TexturePtr _texture, std::uint32_t _flags = std::numeric_limits < std::uint32_t >::max());
	
	void SetUniform( const std::string &_name, const void * _value, std::uint16_t _num = 1 );

public:
	CullType GetCullType() const;
	
	void SetCullType( CullType val );
	
	const Color& GetBaseColor() const;
	
	void SetBaseColor( const Color& val );
	
	const Color& GetEmissiveColor() const;
	
	void SetEmissiveColor( const Color& val );
	
	const Color& GetSubsurfaceColor() const;
	
	void SetSubsurfaceColor( const Color& val );
	
	const Vec2& GetTiling() const;
	
	void SetTiling( const Vec2& val );
	
	const Vec2& GetDitherThreshold() const;
	
	void SetDitherThreshold( const Vec2& val );
	
	const Vec4& GetSurfaceData() const;
	
	void SetSurfaceData( const Vec4& val );
	
	float GetRoughness() const;
	
	void SetRoughness( float val );
	
	float GetMetalness() const;
	
	void SetMetalness( float val );
	
	float GetBumpiness() const;
	
	void SetBumpiness( float val );
	
	float GetAlphaTest() const;
	
	void SetAlphaTest( float val );
	
	TexturePtr GetAOTexture() const;
	
	void SetAOTexture( const TexturePtr& val );
	
	TexturePtr GetAlbedoTexture() const;
	
	void SetAlbedoTexture( const TexturePtr& val );
	
	TexturePtr GetNormalTexture() const;
	
	void SetNormalTexture( const TexturePtr& val );
	
	TexturePtr GetRoughnessTexture() const;
	
	void SetRoughnessTexture( const TexturePtr& val );
	
	TexturePtr GetMetalnessTexture() const;
	
	void SetMetalnessTexture( const TexturePtr& val );

public:
	GPUProgramPtr GetProgram() const;
	
	std::uint64_t GetRenderStates( bool apply_cull = true, bool depth_write = true, bool depth_test = true ) const;

public:
	void Submit();

private:
	GPUProgramPtr _Program;
	
	Color _BaseColor;
	Color _EmissiveColor;
	Color _SubsurfaceColor;
	
	Vec2 _Tiling;
	Vec2 _DitherThreshold;
	
	Vec4 _SurfaceData;
	
	TexturePtr _AOTexture;
	TexturePtr _AlbedoTexture;
	TexturePtr _NormalTexture;
	TexturePtr _RoughnessTexture;
	TexturePtr _MetalnessTexture;
	
	CullType _CullType = CullType::COUNTER_CLOCKWISE;
};

END_XE_NAMESAPCE

#endif // __MATERIAL_H__DA1798CB_BC0C_4DB6_A9E4_C9D890E75DD6
