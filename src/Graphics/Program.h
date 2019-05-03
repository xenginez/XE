/*!
 * \file   Program.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __PROGRAM_H__E9CBA0E6_48BB_4FEB_AE60_A30A61848883
#define __PROGRAM_H__E9CBA0E6_48BB_4FEB_AE60_A30A61848883

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API Program : public std::enable_shared_from_this<Program>
{
public:
	Program();

	Program( ShaderPtr compute_shader );

	Program( ShaderPtr vertex_shader, ShaderPtr fragment_shader );

	~Program();

public:
	ProgramHandle GetHandle() const;

public:
	void SetTexture( uint8 _stage, const String& _sampler, FrameBufferPtr _frameBuffer,  uint8 _attachment = 0, uint32 _flags = std::numeric_limits<uint32>::max() );

	void SetTexture( uint8 _stage, const String& _sampler, TexturePtr _texture, uint32 _flags = std::numeric_limits<uint32>::max() );

	void SetUniform( const String& _name, const void* _value, uint16 _num = 1 );

	UniformPtr GetUniform( const String& _name, bool texture = false );

private:
	ProgramHandle _Handle;

	UnorderedMap<String, UniformPtr> _Uniforms;
};

END_XE_NAMESAPCE

#endif // __PROGRAM_H__E9CBA0E6_48BB_4FEB_AE60_A30A61848883
