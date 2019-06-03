#include "Buffer.h"

USING_XE

BEG_META(Buffer)
END_META()

XE::Buffer::Buffer()
{

}

XE::Buffer::~Buffer()
{

}

XE::BufferHandle XE::Buffer::GetHandle() const
{
	return _Handle;
}

XE::MemoryView XE::Buffer::Map( XE::AccessType val )
{
	return _Data;
}

void XE::Buffer::Unmap()
{

}

XE::uint64 XE::Buffer::GetSize() const
{
	return _Data.Size();
}

XE::uint64 XE::Buffer::GetGPUAddress() const
{
	return (uint64)_Data.Data();
}

XE::AccessType XE::Buffer::GetCPUAccess() const
{
	return _CPUAccess;
}
