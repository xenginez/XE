#ifndef OBJECTMEMORYRESOURCE_H__9F9E1858_9283_4C26_9A2C_9B739DE1CC7B
#define OBJECTMEMORYRESOURCE_H__9F9E1858_9283_4C26_9A2C_9B739DE1CC7B

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API ObjectMemoryResource : public std::pmr::memory_resource
{
private:
	struct Private;

public:
	ObjectMemoryResource();

	~ObjectMemoryResource() noexcept override;

private:
	void * do_allocate( size_t _Bytes, size_t _Align ) override;

	void do_deallocate( void * _Ptr, size_t _Bytes, size_t _Align ) override;

	bool do_is_equal( const std::pmr::memory_resource & _That ) const noexcept override;

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // OBJECTMEMORYRESOURCE_H__9F9E1858_9283_4C26_9A2C_9B739DE1CC7B
