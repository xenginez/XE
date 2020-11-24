#ifndef MEMORYRESOURCE_H__84074448_45AA_41EC_A082_4E1DA59DFEC6
#define MEMORYRESOURCE_H__84074448_45AA_41EC_A082_4E1DA59DFEC6

#include "Type.h"
#include "StackMemoryResource.h"
#include "ObjectMemoryResource.h"
#include "DefaultMemoryResource.h"

BEG_XE_NAMESPACE

class XE_API MemoryResource
{
public:
	static XE::StackMemoryResource * GetStackMemoryResource();

	static XE::ObjectMemoryResource * GetObjectMemoryResource();

	static XE::DefaultMemoryResource * GetDefaultMemoryResource();

};

END_XE_NAMESPACE

#endif // MEMORYRESOURCE_H__84074448_45AA_41EC_A082_4E1DA59DFEC6
