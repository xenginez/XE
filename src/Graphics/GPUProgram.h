/*!
 * \file   GPUProgram.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __GPUPROGRAM_H__CAD13593_C1BE_4E5F_BDF7_6D356D361DF7
#define __GPUPROGRAM_H__CAD13593_C1BE_4E5F_BDF7_6D356D361DF7

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API GPUProgram : public XE::Object
{
	OBJECT(GPUProgram, Object)
	
public:
	GPUProgram();
	
	GPUProgram( ShaderPtr compute_shader );

	GPUProgram( ShaderPtr vertex_shader, ShaderPtr fragment_shader );

public:
	ProgramHandle GetHandle() const;

public:
	bool Begin();

	void End();

public:
	void SetTexture( uint8 _stage, const String& _sampler, FrameBufferPtr _frameBuffer, uint8 _attachment = 0,  uint32 _flags = std::numeric_limits<uint32>::max() );

	void SetTexture( uint8 _stage, const String& _sampler, TexturePtr _texture, uint32 _flags = std::numeric_limits<uint32>::max() );

	void SetUniform( const String& _name, const Vec2& _value, uint16 _num = 1 );

	void SetUniform( const String& _name, const Vec3& _value, uint16 _num = 1 );

	void SetUniform( const String& _name, const Vec4& _value, uint16 _num = 1 );

	void SetUniform( const String& _name, const void* _value, uint16 _num = 1 );

	UniformPtr GetUniform( const String& _name, bool texture = false );

	const Array<ShaderPtr>& GetShaders() const;

private:
	void populate();

	void attach_shader( ShaderPtr shader );

	ProgramPtr _Program;
	Array<ShaderPtr> _Shaders;
	Array<uint16> _ShadersCached;
};

END_XE_NAMESAPCE

#endif // __GPUPROGRAM_H__CAD13593_C1BE_4E5F_BDF7_6D356D361DF7
