/*!
 * \file   Platform.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __PLATFORM_H__BDD7C650_EC23_41CF_A4EA_7CDBFE3B0135
#define __PLATFORM_H__BDD7C650_EC23_41CF_A4EA_7CDBFE3B0135

#include "Handle.h"

BEG_XE_NAMESPACE

class UTILS_API Platform
{
public:
	static uint64 dlopen( const String& name );

	static void * dlsym( uint64 handle, const String& name );

	static bool dlclose( uint64 handle );

public:
	static Language get_default_language();

};

END_XE_NAMESAPCE

#endif // __PLATFORM_H__BDD7C650_EC23_41CF_A4EA_7CDBFE3B0135
