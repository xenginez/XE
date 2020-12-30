/*!
 * \file	Global.h
 *
 * \author	ZhengYuanQing
 * \date	2020/12/30
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GLOBAL_H__07BB62A7_8948_4D00_A6A2_DB2A08F1327A
#define GLOBAL_H__07BB62A7_8948_4D00_A6A2_DB2A08F1327A

#include <XE.h>

#ifdef GUI_EXPORT
#define GUI_API DLL_EXPORT
#else
#define GUI_API DLL_IMPORT
#endif // GUI_EXPORT

#define BEG_GUI_NAMESPACE namespace GUI {
#define END_GUI_NAMESPACE }

#endif // GLOBAL_H__07BB62A7_8948_4D00_A6A2_DB2A08F1327A
