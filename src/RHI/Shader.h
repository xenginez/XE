/*!
 * \file   Shader.h
 *
 * \author ZhengYuanQing
 * \date   2019/06/05
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __SHADER_H__AF709312_F028_4D0A_9FF7_6BD896C33200
#define __SHADER_H__AF709312_F028_4D0A_9FF7_6BD896C33200

#include "Resource.h"

BEG_XE_NAMESPACE

class RHI_API Shader : public Resource
{
	OBJECT( Shader, Resource )

public:
	Shader();

	~Shader() override;

public:
	ShaderHandle GetHandle() const;

	const String & GetEntry() const;

public:
	Variant GetVariable( const String & val ) const;

	void SetVariable( const String & name, const Variant & val );

private:
	String _Entry;
	ShaderHandle _Handle;
	Map<String, Variant> _Variables;
};

class RHI_API HullShader : public Shader
{
	OBJECT( HullShader, Shader )

public:
	HullShader();

	~HullShader() override;
};

class RHI_API PixelShader : public Shader
{
	OBJECT( PixelShader, Shader )

public:
	PixelShader();

	~PixelShader() override;
};

class RHI_API VertexShader : public Shader
{
	OBJECT( VertexShader, Shader )

public:
	VertexShader();

	~VertexShader() override;
};

class RHI_API DomainShader : public Shader
{
	OBJECT( DomainShader, Shader )

public:
	DomainShader();

	~DomainShader() override;
};

class RHI_API ComputeShader : public Shader
{
	OBJECT( ComputeShader, Shader )

public:
	ComputeShader();

	~ComputeShader() override;
};

class RHI_API GeometryShader : public Shader
{
	OBJECT( GeometryShader, Shader )

public:
	GeometryShader();

	~GeometryShader() override;
};

END_XE_NAMESPACE

#endif // __SHADER_H__AF709312_F028_4D0A_9FF7_6BD896C33200
