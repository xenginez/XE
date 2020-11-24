/*!
 * \file	DefaultMemoryResource.h
 *
 * \author	ZhengYuanQing
 * \date	2020/11/24
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef DEFAULTMEMORYRESOURCE_H__1DAA4948_67F8_4B1C_A818_7ED747B62F41
#define DEFAULTMEMORYRESOURCE_H__1DAA4948_67F8_4B1C_A818_7ED747B62F41

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API DefaultMemoryResource : public std::pmr::memory_resource
{
private:
	struct Private;

public:
	DefaultMemoryResource();

	~DefaultMemoryResource() noexcept override;

private:
	void * do_allocate( size_t _Bytes, size_t _Align ) override;

	void do_deallocate( void * _Ptr, size_t _Bytes, size_t _Align ) override;

	bool do_is_equal( const std::pmr::memory_resource & _That ) const noexcept override;

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // DEFAULTMEMORYRESOURCE_H__1DAA4948_67F8_4B1C_A818_7ED747B62F41
