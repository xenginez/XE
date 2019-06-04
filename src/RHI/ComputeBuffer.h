/*!
 * \file    ComputeBuffer.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-29
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __COMPUTEBUFFER_H__F4D4602F_2026_496B_B457_3ED949376D95
#define __COMPUTEBUFFER_H__F4D4602F_2026_496B_B457_3ED949376D95

#include "Buffer.h"

BEG_XE_NAMESPACE

class RHI_API ComputeBuffer : public Buffer
{
	OBJECT(ComputeBuffer, Buffer)
	
public:
	ComputeBuffer();
	
	~ComputeBuffer() override;
	
	
};

END_XE_NAMESPACE

#endif //__COMPUTEBUFFER_H__F4D4602F_2026_496B_B457_3ED949376D95
