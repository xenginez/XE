#include "MemoryResource.h"

XE::StackMemoryResource * XE::MemoryResource::GetStackMemoryResource()
{
	thread_local XE::StackMemoryResource resource;

	return &resource;
}

XE::ObjectMemoryResource * XE::MemoryResource::GetObjectMemoryResource()
{
	static ObjectMemoryResource resource;
	
	return &resource;
}

XE::DefaultMemoryResource * XE::MemoryResource::GetDefaultMemoryResource()
{
	static DefaultMemoryResource resource;

	return &resource;
}
