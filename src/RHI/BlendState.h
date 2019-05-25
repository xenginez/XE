/*!
 * \file   BlendState.h
 *
 * \author ZhengYuanQing
 * \date   2019/05/25
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __BLENDSTATE_H__796DF817_62A3_4D30_A394_2EA0B9934725
#define __BLENDSTATE_H__796DF817_62A3_4D30_A394_2EA0B9934725

#include "Resource.h"

BEG_XE_NAMESPACE

class RHI_API BlendState : public Resource
{
	OBJECT(BlendState, Resource)

public:
	BlendState();

	~BlendState() override;

public:
	BlendStateHandle GetHandle() const;

private:
	BlendStateHandle _Handle;
};

END_XE_NAMESAPCE

#endif // __BLENDSTATE_H__796DF817_62A3_4D30_A394_2EA0B9934725
