#include "Gfx.h"

#include "Encoder.h"
#include "Structs.h"
#include "RendererContext.h"
#include "RendererContextGLES2.h"
#include "RendererContextGLES3.h"
#include "RendererContextMetal.h"
#include "RendererContextOpenGL.h"
#include "RendererContextVulkan.h"
#include "RendererContextSoftware.h"
#include "RendererContextDirectX11.h"
#include "RendererContextDirectX12.h"

struct XE::Gfx::Private
{
	RendererContext * _Context = nullptr;
};

XE::Gfx::Gfx()
	:_p( new Private )
{

}

XE::Gfx::~Gfx()
{
	delete _p;
}

XE::Caps XE::Gfx::GetCaps()
{
	return _p->_Context->GetCaps();
}

XE::RendererContextType XE::Gfx::GetContextType()
{
	return _p->_Context->GetType();
}

XE::Array<XE::RendererContextType> XE::Gfx::GetSupportedContext()
{
	XE::Array<XE::RendererContextType> ret;

#if PLATFORM_OS & (OS_WINDOWS)
	ret.push_back( XE::RendererContextType::DIRECT3D12 );
	ret.push_back( XE::RendererContextType::DIRECT3D11 );
	ret.push_back( XE::RendererContextType::VULKAN );
	ret.push_back( XE::RendererContextType::OPENGL );
#elif PLATFORM_OS & (OS_XBOXONE)
	ret.push_back( XE::RendererContextType::DIRECT3D12 );
#elif PLATFORM_OS & (OS_MAC)
	ret.push_back( XE::RendererContextType::METAL );
	ret.push_back( XE::RendererContextType::OPENGL );
#elif PLATFORM_OS & (OS_IOS)
	ret.push_back( XE::RendererContextType::METAL );
	ret.push_back( XE::RendererContextType::GLES2 );
#elif PLATFORM_OS & (OS_ANDROID)
	ret.push_back( XE::RendererContextType::VULKAN );
	ret.push_back( XE::RendererContextType::GLES3 );
	ret.push_back( XE::RendererContextType::GLES2 );
#elif PLATFORM_OS & (OS_LINUX)
	ret.push_back( XE::RendererContextType::VULKAN );
	ret.push_back( XE::RendererContextType::OPENGL );
#endif

	ret.push_back( XE::RendererContextType::SOFTWARE );

	return ret;
}

void XE::Gfx::Init( const XE::InitInfo & val )
{
	auto type = val.type;

	if( type == RendererContextType::NOOP )
	{
		type = GetSupportedContext().front();
	}

	switch( type )
	{
	case XE::RendererContextType::METAL:
		_p->_Context = CreateRendererContextMetal();
		break;
	case XE::RendererContextType::VULKAN:
		_p->_Context = CreateRendererContextVulkan();
		break;
	case XE::RendererContextType::GLES2:
		_p->_Context = CreateRendererContextGLES2();
		break;
	case XE::RendererContextType::GLES3:
		_p->_Context = CreateRendererContextGLES3();
		break;
	case XE::RendererContextType::OPENGL:
		_p->_Context = CreateRendererContextOpenGL();
		break;
	case XE::RendererContextType::DIRECT3D11:
		_p->_Context = CreateRendererContextDirectX11();
		break;
	case XE::RendererContextType::DIRECT3D12:
		_p->_Context = CreateRendererContextDirectX12();
		break;
	case XE::RendererContextType::SOFTWARE:
		_p->_Context = CreateRendererContextSoftware();
		break;
	default:
		break;
	}

	XE_ASSERT( _p->_Context == nullptr );

	_p->_Context->Init( val );
}

void XE::Gfx::Shutdown()
{
	if( _p->_Context )
	{
		_p->_Context->Shutdown();

		delete _p->_Context;
	}
}
