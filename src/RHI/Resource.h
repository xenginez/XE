/*!
 * \file   Resource.h
 *
 * \author ZhengYuanQing
 * \date   2019/05/25
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __RESOURCE_H__B97CEE0F_82C7_4B34_A226_3C364B80F5D8
#define __RESOURCE_H__B97CEE0F_82C7_4B34_A226_3C364B80F5D8

#include "Type.h"

BEG_XE_NAMESPACE

class RHI_API Resource : public std::enable_shared_from_this< Resource >
{
	OBJECT(Resource)

public:
	Resource();

	virtual ~Resource();

public:
	virtual bool Prepare() = 0;

public:
	DevicePtr GetDevice() const;

	void SetDevice( const DevicePtr & val );

public:
	ResourceHandle GetHandle() const;

protected:
	XE::basic_memory_view<XE::uint8> Map( XE::uint32 sub_resource, XE::uint64 begin, XE::uint64 end, XE::uint8 * read_data );

	void Unmap( XE::uint32 sub_resource, XE::uint64 begin, XE::uint64 end );

private:
	DevicePtr _Device;
	ResourceHandle _Handle;
};

END_XE_NAMESPACE

#endif // __RESOURCE_H__B97CEE0F_82C7_4B34_A226_3C364B80F5D8
