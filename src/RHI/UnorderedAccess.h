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

#include "Resource.h"

BEG_XE_NAMESPACE

class RHI_API UnorderedAccess : public Resource
{
	OBJECT( UnorderedAccess, Resource )

public:
	UnorderedAccess();
	
	~UnorderedAccess() override;

};

END_XE_NAMESPACE

#endif //__XE_UNORDEREDACCESS_H__
