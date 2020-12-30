/*!
 * \file	Global.h
 *
 * \author	ZhengYuanQing
 * \date	2020/12/30
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GLOBAL_H__27C75190_EA1E_44EA_8159_D70152BB0A3A
#define GLOBAL_H__27C75190_EA1E_44EA_8159_D70152BB0A3A

#include <XE.h>

#ifdef NPR_EXPORT
#define NPR_API DLL_EXPORT
#else
#define NPR_API DLL_IMPORT
#endif // NPR_EXPORT

#define BEG_NPR_NAMESPACE namespace NPR {
#define END_NPR_NAMESPACE }

#endif // GLOBAL_H__27C75190_EA1E_44EA_8159_D70152BB0A3A
