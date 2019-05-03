/*!
 * \file   Exception.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __EXCEPTION_H__F46ED19F_D50F_495C_9BD6_1ADAFEBA5700
#define __EXCEPTION_H__F46ED19F_D50F_495C_9BD6_1ADAFEBA5700

#include "Type.h"

BEG_XE_NAMESPACE

class BASE_API Exception
{
public:
	Exception();

	virtual ~Exception();

public:
	virtual const char * What() const;
};

class BASE_API RuntimeException : public Exception
{
public:
	RuntimeException();

	virtual ~RuntimeException();

public:
	virtual const char * What() const;
};

END_XE_NAMESAPCE

#endif // __EXCEPTION_H__F46ED19F_D50F_495C_9BD6_1ADAFEBA5700
