/*!
 * \file   Buffer.h
 *
 * \author ZhengYuanQing
 * \date   2019/06/03
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __BUFFER_H__D9EB5BDB_5A01_4C5C_8262_008E86007DFD
#define __BUFFER_H__D9EB5BDB_5A01_4C5C_8262_008E86007DFD

#include "Resource.h"

BEG_XE_NAMESPACE

class RHI_API Buffer : public Resource
{
	OBJECT(Buffer, Resource)
	
public:
    Buffer();

    ~Buffer() override;

public:
    BufferHandle GetHandle() const;

public:
    MemoryView Map(AccessType val);

    void Unmap();

    uint64 GetSize() const;

    uint64 GetGPUAddress() const;

    AccessType GetCPUAccess() const;

private:
    MemoryView _Data;
    AccessType _CPUAccess;

    BufferHandle _Handle;
};

END_XE_NAMESAPCE

#endif // __BUFFER_H__D9EB5BDB_5A01_4C5C_8262_008E86007DFD
