#include "MemoryResource.h"

#include "StackMemoryResource.h"
#include "ObjectMemoryResource.h"

std::pmr::memory_resource * XE::MemoryResource::GetStackMemoryResource()
{
	thread_local XE::StackMemoryResource resource;

	return &resource;
}

std::pmr::memory_resource * XE::MemoryResource::GetObjectMemoryResource()
{
	static ObjectMemoryResource resource;
	
	return &resource;
}

std::pmr::memory_resource * XE::MemoryResource::GetDefaultMemoryResource()
{
	return std::pmr::get_default_resource();
}
