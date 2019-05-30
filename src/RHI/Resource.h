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

class RHI_API Resource
{
	OBJECT(Resource)

public:
	Resource();

	virtual ~Resource();

public:
	virtual bool PreInit() = 0;
};

END_XE_NAMESAPCE

#endif // __RESOURCE_H__B97CEE0F_82C7_4B34_A226_3C364B80F5D8
