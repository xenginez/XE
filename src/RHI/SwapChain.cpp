#include "SwapChain.h"

#include "RenderContext.h"

XE::SwapChain::SwapChain( RenderContextPtr device, WindowHandle handle )
	:_Context( device )
{
	//_Handle = _Device->CreateSwapChain( handle );
}

XE::SwapChain::~SwapChain()
{
	_Context->DestroySwapChain( _Handle );
}

XE::SwapChainHandle XE::SwapChain::GetHandle() const
{
	return _Handle;
}
