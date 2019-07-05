/*!
 * \file    UnorderedAccess.h
 *
 * \author  ZhengYuanQing
 * \date    2019-06-01
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __XE_UNORDEREDACCESS_H__
#define __XE_UNORDEREDACCESS_H__

#include "Type.h"

BEG_XE_NAMESPACE

class RHI_API UnorderedAccess
{
public:
	UnorderedAccess();
	
	~UnorderedAccess();

public:
	ResourcePtr GetResource();

private:
	ResourcePtr _Resource;
};

END_XE_NAMESPACE

#endif //__XE_UNORDEREDACCESS_H__
