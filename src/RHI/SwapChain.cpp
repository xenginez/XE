#include "SwapChain.h"

#include "Context.h"

XE::SwapChain::SwapChain( ContextPtr device, WindowHandle handle )
	:_Device( device )
{
	//_Handle = _Device->CreateSwapChain( handle );
}

XE::SwapChain::~SwapChain()
{
	_Device->DestroySwapChain( _Handle );
}

XE::SwapChainHandle XE::SwapChain::GetHandle() const
{
	return _Handle;
}
