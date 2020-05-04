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
	std::array<XE::Frame, 3> _Frames;
	XE::Array<XE::Encoder *> _Encoders;
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

XE::ContextType XE::Gfx::GetContextType()
{
	return _p->_Context->GetContextType();
}

XE::Array<XE::ContextType> XE::Gfx::GetSupportedContext()
{
	XE::Array<XE::ContextType> ret;

#if PLATFORM_OS & (OS_WINDOWS)
	ret.push_back( XE::ContextType::DIRECT3D12 );
	ret.push_back( XE::ContextType::DIRECT3D11 );
	ret.push_back( XE::ContextType::VULKAN );
	ret.push_back( XE::ContextType::OPENGL );
#elif PLATFORM_OS & (OS_XBOXONE)
	ret.push_back( XE::ContextType::DIRECT3D12 );
#elif PLATFORM_OS & (OS_MAC)
	ret.push_back( XE::ContextType::METAL );
	ret.push_back( XE::ContextType::OPENGL );
#elif PLATFORM_OS & (OS_IOS)
	ret.push_back( XE::ContextType::METAL );
	ret.push_back( XE::ContextType::GLES2 );
#elif PLATFORM_OS & (OS_ANDROID)
	ret.push_back( XE::ContextType::VULKAN );
	ret.push_back( XE::ContextType::GLES3 );
	ret.push_back( XE::ContextType::GLES2 );
#elif PLATFORM_OS & (OS_LINUX)
	ret.push_back( XE::ContextType::VULKAN );
	ret.push_back( XE::ContextType::OPENGL );
#endif

	ret.push_back( XE::ContextType::SOFTWARE );

	return ret;
}

void XE::Gfx::Init( const XE::InitInfo & val )
{
	auto type = val.type;

	if( type == ContextType::NOOP )
	{
		type = GetSupportedContext().front();
	}

	switch( type )
	{
	case XE::ContextType::METAL:
		_p->_Context = CreateRendererContextMetal();
		break;
	case XE::ContextType::VULKAN:
		_p->_Context = CreateRendererContextVulkan();
		break;
	case XE::ContextType::GLES2:
		_p->_Context = CreateRendererContextGLES2();
		break;
	case XE::ContextType::GLES3:
		_p->_Context = CreateRendererContextGLES3();
		break;
	case XE::ContextType::OPENGL:
		_p->_Context = CreateRendererContextOpenGL();
		break;
	case XE::ContextType::DIRECT3D11:
		_p->_Context = CreateRendererContextDirectX11();
		break;
	case XE::ContextType::DIRECT3D12:
		_p->_Context = CreateRendererContextDirectX12();
		break;
	case XE::ContextType::SOFTWARE:
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
