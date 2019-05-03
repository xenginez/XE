/*!
 * \file   Global.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __GLOBAL_H__397ADE88_7898_4FDF_B98E_B1C39DB69FEA
#define __GLOBAL_H__397ADE88_7898_4FDF_B98E_B1C39DB69FEA

#include <set>
#include <map>
#include <list>
#include <cmath>
#include <array>
#include <stack>
#include <queue>
#include <deque>
#include <regex>
#include <mutex>
#include <memory>
#include <atomic>
#include <thread>
#include <vector>
#include <string>
#include <cassert>
#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>
#include <functional>
#include <type_traits>
#include <unordered_set>
#include <unordered_map>
#include <condition_variable>

#include "Config.h"
#if PLATFORM_OS == OS_MAC
#include <boost/filesystem.hpp>
namespace std{namespace filesystem = boost::filesystem;}
#endif

#ifdef BASE_EXPORT
#define BASE_API DLL_EXPORT
#else
#define BASE_API DLL_IMPORT
#define LIB_NAME "Base"
#include <Base/AutoLink.h>
#endif

#endif // __GLOBAL_H__397ADE88_7898_4FDF_B98E_B1C39DB69FEA
