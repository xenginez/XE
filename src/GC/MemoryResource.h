#ifndef MEMORYRESOURCE_H__84074448_45AA_41EC_A082_4E1DA59DFEC6
#define MEMORYRESOURCE_H__84074448_45AA_41EC_A082_4E1DA59DFEC6

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API MemoryResource
{
public:
	static std::pmr::memory_resource * GetStackMemoryResource();

	static std::pmr::memory_resource * GetObjectMemoryResource();

	static std::pmr::memory_resource * GetDefaultMemoryResource();

};

END_XE_NAMESPACE

#endif // MEMORYRESOURCE_H__84074448_45AA_41EC_A082_4E1DA59DFEC6
