#include "Type.h"

#include <bgfx/defines.h>

USING_XE

XE::uint64 XE::StateDefault()
{
	return BGFX_STATE_DEFAULT;
}

XE::uint64 XE::StateAlphaRef( uint64 val )
{
	return BGFX_STATE_ALPHA_REF( val );
}

XE::uint64 XE::StatePointSize( uint64 val )
{
	return BGFX_STATE_POINT_SIZE( val );
}

XE::uint64 XE::StateStencilFuncRef( uint64 val )
{
	return BGFX_STENCIL_FUNC_REF( val );
}

XE::uint64 XE::StateStencilFuncRMask( uint64 val )
{
	return BGFX_STENCIL_FUNC_RMASK( val );
}

XE::uint64 XE::SamplerBorderColor( uint64 val )
{
	return BGFX_SAMPLER_BORDER_COLOR( val );
}

XE::uint64 XE::BlendFunctionSeparate( StateBlendFunc srcRGB, StateBlendFunc dstRGB, StateBlendFunc srcA, StateBlendFunc dstA )
{
	return BGFX_STATE_BLEND_FUNC_SEPARATE( ( XE::uint64 )srcRGB, ( XE::uint64 )dstRGB, ( XE::uint64 )srcA, ( XE::uint64 )dstA );
}

XE::uint64 XE::BlendEquationSeparate( StateBlendEquation rgb, StateBlendEquation a )
{
	return BGFX_STATE_BLEND_EQUATION_SEPARATE( ( XE::uint64 )rgb, ( XE::uint64 )a );
}

XE::uint64 XE::BlendAdditive()
{
	return BGFX_STATE_BLEND_ADD;
}

XE::uint64 XE::BlendAlpha()
{
	return BGFX_STATE_BLEND_ALPHA;
}

XE::uint64 XE::BlendDarken()
{
	return BGFX_STATE_BLEND_DARKEN;
}

XE::uint64 XE::BlendLighten()
{
	return BGFX_STATE_BLEND_LIGHTEN;
}

XE::uint64 XE::BlendMultiply()
{
	return BGFX_STATE_BLEND_MULTIPLY;
}

XE::uint64 XE::BlendNormal()
{
	return BGFX_STATE_BLEND_NORMAL;
}

XE::uint64 XE::BlendScreen()
{
	return BGFX_STATE_BLEND_SCREEN;
}

XE::uint64 XE::BlendLinearBurn()
{
	return BGFX_STATE_BLEND_LINEAR_BURN;
}

XE::uint64 XE::BlendFuncRT1( StateBlendFunc src, StateBlendFunc dst )
{
	return BGFX_STATE_BLEND_FUNC_RT_1( ( XE::uint64 )src, ( XE::uint64 )dst );
}

XE::uint64 XE::BlendFuncRT2( StateBlendFunc src, StateBlendFunc dst )
{
	return BGFX_STATE_BLEND_FUNC_RT_1( ( XE::uint64 )src, ( XE::uint64 )dst );
}

XE::uint64 XE::BlendFuncRT3( StateBlendFunc src, StateBlendFunc dst )
{
	return BGFX_STATE_BLEND_FUNC_RT_2( ( XE::uint64 )src, ( XE::uint64 )dst );
}

XE::uint64 XE::BlendFuncRT1E( StateBlendFunc src, StateBlendFunc dst, StateBlendEquation equation )
{
	return BGFX_STATE_BLEND_FUNC_RT_1E( ( XE::uint64 )src, ( XE::uint64 )dst, ( XE::uint64 )equation );
}

XE::uint64 XE::BlendFuncRT2E( StateBlendFunc src, StateBlendFunc dst, StateBlendEquation equation )
{
	return BGFX_STATE_BLEND_FUNC_RT_2E( ( XE::uint64 )src, ( XE::uint64 )dst, ( XE::uint64 )equation );
}

XE::uint64 XE::BlendFuncRT3E( StateBlendFunc src, StateBlendFunc dst, StateBlendEquation equation )
{
	return BGFX_STATE_BLEND_FUNC_RT_3E( ( XE::uint64 )src, ( XE::uint64 )dst, ( XE::uint64 )equation );
}
