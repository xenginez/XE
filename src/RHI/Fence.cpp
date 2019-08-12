#include "Fence.h"

#include "RenderContext.h"

XE::Fence::Fence()
{

}

XE::Fence::~Fence()
{

}

XE::uint64 XE::Fence::GetCompletedValue()
{
	return _Context->GetCompletedValue( _Handle );
}

bool XE::Fence::Wait( XE::uint64 val )
{
	return _Context->Wait( _Handle, val );
}

bool XE::Fence::Signal( XE::uint64 val )
{
	return _Context->Signal( _Handle, val );
}

XE::FenceHandle XE::Fence::GetHandle() const
{
	return _Handle;
}
