/*!
 * \file	RenderShader.h
 *
 * \author	ZhengYuanQing
 * \date	2020/01/02
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RENDERSHADER_H__5EA4B130_8B78_469F_954B_3FAFFDE11A77
#define RENDERSHADER_H__5EA4B130_8B78_469F_954B_3FAFFDE11A77

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API RenderShader : public XE::Object
{
	OBJECT( RenderShader, Object )

public:
	RenderShader();

	~RenderShader() override;

public:
	XE::ShaderHandle GetHandle() const;

	void SetHandle( XE::ShaderHandle val );

	const XE::Buffer & GetBuffer() const;

	void SetBuffer( const XE::Buffer & val );

public:
	void AssetLoad() override;

	void AssetUnload() override;

private:
	XE::Buffer _Data;
	XE::String _Source;
	XE::ShaderHandle _Handle;
};

END_XE_NAMESPACE

#endif // RENDERSHADER_H__5EA4B130_8B78_469F_954B_3FAFFDE11A77
