#ifndef STACKMEMORYRESOURCE_H__3E18A533_B4D4_4F49_8CD2_B7C89E802478
#define STACKMEMORYRESOURCE_H__3E18A533_B4D4_4F49_8CD2_B7C89E802478

#include "Type.h"

BEG_XE_NAMESPACE

class StackMemoryResource : public std::pmr::memory_resource
{
public:
	StackMemoryResource();

	~StackMemoryResource() noexcept override;

private:
	void * do_allocate( size_t _Bytes, size_t _Align ) override;

	void do_deallocate( void * _Ptr, size_t _Bytes, size_t _Align ) override;

	bool do_is_equal( const std::pmr::memory_resource & _That ) const noexcept override;

private:
	void * _Beg;
	void * _Ptr;
	std::size_t _Space;
};

END_XE_NAMESPACE

#endif // STACKMEMORYRESOURCE_H__3E18A533_B4D4_4F49_8CD2_B7C89E802478
