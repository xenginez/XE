#include "RenderShader.h"

#include "Gfx.h"

USING_XE

BEG_META( RenderShader )
type->Property( "Data", &RenderShader::_Data );
type->Property( "Source", &RenderShader::_Source );
END_META()

RenderShader::RenderShader()
{

}

RenderShader::~RenderShader()
{

}

XE::ShaderHandle RenderShader::GetHandle() const
{
	return _Handle;
}

void RenderShader::SetHandle( XE::ShaderHandle val )
{
	_Handle = val;
}

const XE::Buffer & RenderShader::GetBuffer() const
{
	return _Data;
}

void RenderShader::SetBuffer( const XE::Buffer & val )
{
	_Data = val;
}

void RenderShader::AssetLoad()
{
	if( _Data.size() > 0 )
	{
		_Handle = Gfx::createShader( _Data.GetView() );
	}
}

void RenderShader::AssetUnload()
{
	if( _Handle != ShaderHandle::Invalid )
	{
		Gfx::destroy( _Handle );
	}
}
