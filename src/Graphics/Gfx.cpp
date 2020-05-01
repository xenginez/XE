#include "Gfx.h"

#include "RendererContext.h"

struct XE::Gfx::Private
{
	RenderContext * _Context;
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

#if PLATFORM_OS & (OS_WINDOWS | OS_XBOXONE)
	ret.push_back( XE::ContextType::DIRECT3D12 );
	ret.push_back( XE::ContextType::VULKAN );
#elif PLATFORM_OS & (OS_MAC | OS_IOS)
	ret.push_back( XE::ContextType::METAL );
#elif PLATFORM_OS & (OS_ANDROID | OS_LINUX)
	ret.push_back( XE::ContextType::VULKAN );
#endif

	ret.push_back( XE::ContextType::NOOP );

	return ret;
}
