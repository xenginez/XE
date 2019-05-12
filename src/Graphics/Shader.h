/*!
 * \file   Shader.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __SHADER_H__FEC0B518_0E1A_4C32_BAC7_92C2BBF67FD8
#define __SHADER_H__FEC0B518_0E1A_4C32_BAC7_92C2BBF67FD8

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API Shader : public XE::Object
{
	OBJECT(Shader, Object);
	
public:
	Shader();

	Shader( const MemoryView * _mem );

	Shader( const EmbeddedShader * _es, const String& name );

	Shader( ShaderHandle hndl );

	~Shader();

public:
	ShaderHandle GetHandle() const;

	XE::uint64 GetUniformCount() const;

	UniformPtr GetUniform( XE::uint64 val ) const;

	const Array<UniformPtr>& GetUniforms() const;

private:
	ShaderHandle _Handle;

	Array<UniformPtr> _Uniforms;
};

END_XE_NAMESAPCE

#endif // __SHADER_H__FEC0B518_0E1A_4C32_BAC7_92C2BBF67FD8
