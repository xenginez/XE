#include "Gfx.h"

#include "Structs.h"
#include "RendererContext.h"

struct XE::Gfx::Private
{
	RenderContext * _Context = nullptr;
	std::array<XE::Frame, 3> _Frames;
	XE::Array<XE::Encoder> _Encoders;
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
	ret.push_back( XE::ContextType::GLES2 );
#elif PLATFORM_OS & (OS_IOS)
	ret.push_back( XE::ContextType::METAL );
	ret.push_back( XE::ContextType::OPENGL );
#elif PLATFORM_OS & (OS_ANDROID)
	ret.push_back( XE::ContextType::VULKAN );
	ret.push_back( XE::ContextType::GLES2 );
	ret.push_back( XE::ContextType::GLES3 );
#elif PLATFORM_OS & (OS_LINUX)
	ret.push_back( XE::ContextType::VULKAN );
	ret.push_back( XE::ContextType::OPENGL );
#endif

	ret.push_back( XE::ContextType::SOFTWARE );
	ret.push_back( XE::ContextType::NOOP );

	return ret;
}
