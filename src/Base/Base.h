/*!
 * \file	Base.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/21
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef BASE_H__89974031_381A_446E_A835_7C7B6E1FD961
#define BASE_H__89974031_381A_446E_A835_7C7B6E1FD961

#include "Config.h"
#include "String.h"
#include "mstream.hpp"
#include "Exception.h"
#include "StringUtils.h"
#include "Singleton.hpp"

#define SINGLETON( TYPE ) friend class XE::Singleton< TYPE >;

#endif // BASE_H__89974031_381A_446E_A835_7C7B6E1FD961
