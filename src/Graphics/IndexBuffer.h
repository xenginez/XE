/*!
 * \file   IndexBuffer.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __INDEXBUFFER_H__62E15EE7_406E_474B_93F4_0066F15B7384
#define __INDEXBUFFER_H__62E15EE7_406E_474B_93F4_0066F15B7384

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API IndexBuffer : public std::enable_shared_from_this<IndexBuffer>
{
public:
	IndexBuffer();

	IndexBuffer( const MemoryView * _mem, std::uint16_t _flags = BGFX_BUFFER_NONE );

	~IndexBuffer();

public:
	IndexBufferHandle GetHandle() const;

private:
	IndexBufferHandle _Handle;
};

END_XE_NAMESAPCE

#endif // __INDEXBUFFER_H__62E15EE7_406E_474B_93F4_0066F15B7384
