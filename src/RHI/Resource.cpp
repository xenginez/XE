#include "Resource.h"

#include "Device.h"

USING_XE

BEG_META(Resource)
END_META()

XE::Resource::Resource()
{

}

XE::Resource::~Resource()
{

}

XE::DevicePtr XE::Resource::GetDevice() const
{
	return _Device;
}

void XE::Resource::SetDevice( const DevicePtr & val )
{
	_Device = val;
}

XE::ResourceHandle XE::Resource::GetHandle() const
{
	return _Handle;
}

XE::basic_memory_view<XE::uint8> XE::Resource::Map( XE::uint32 sub_resource, XE::uint64 begin, XE::uint64 end, XE::uint8 * read_data )
{
	return _Device->Map( _Handle, sub_resource, begin, end, read_data );
}

void XE::Resource::Unmap( XE::uint32 sub_resource, XE::uint64 begin, XE::uint64 end )
{
	_Device->Unmap( _Handle, sub_resource, begin, end );
}
