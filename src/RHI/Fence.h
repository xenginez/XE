/*!
 * \file   Fence.h
 *
 * \author ZhengYuanQing
 * \date   2019/05/29
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __FENCE_H__5252F013_3DDF_4436_8C30_ADECECF4B1B5
#define __FENCE_H__5252F013_3DDF_4436_8C30_ADECECF4B1B5

#include "Resource.h"

BEG_XE_NAMESPACE

class RHI_API Fence : public std::enable_shared_from_this<Fence>
{
	OBJECT(Fence)

public:
	Fence();
	
	~Fence();

public:
	XE::uint64 GetValue() const;
	
	void ResetValue( XE::uint64 val );
};

END_XE_NAMESPACE


#endif // __FENCE_H__5252F013_3DDF_4436_8C30_ADECECF4B1B5
