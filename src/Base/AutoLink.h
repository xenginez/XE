/*!
 * \file   AutoLink.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */

#include "Config.h"

#if PLATFORM_OS == OS_WINDOWS
	#ifdef LIB_NAME
		#pragma comment(lib, LIB_NAME ".lib")
		#pragma message ("linking to lib file: " LIB_NAME ".lib")
		#undef LIB_NAME
	#endif // LIB_NAME
#else
	#ifdef LIB_NAME
		#undef LIB_NAME
	#endif // LIB_NAME
#endif
