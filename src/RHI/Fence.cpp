#include "Fence.h"

#include "Context.h"

XE::Fence::Fence()
{

}

XE::Fence::~Fence()
{

}

XE::uint64 XE::Fence::GetCompletedValue()
{
	return _Device->GetCompletedValue( _Handle );
}

bool XE::Fence::Wait( XE::uint64 val )
{
	return _Device->Wait( _Handle, val );
}

bool XE::Fence::Signal( XE::uint64 val )
{
	return _Device->Signal( _Handle, val );
}

XE::FenceHandle XE::Fence::GetHandle() const
{
	return _Handle;
}
