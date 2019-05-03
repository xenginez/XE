/*!
 * \file   Type.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TYPE_H__FF3D8A9E_5172_4F88_873F_0CAF1E5289F6
#define __TYPE_H__FF3D8A9E_5172_4F88_873F_0CAF1E5289F6

#include "Global.h"

BEG_XE_NAMESPACE

DECL_PTR( ProfilerFrame );

enum class Language
{
	ENGLISH,
	CHINESESIMPLIFIED,
	CHINESETRADITIONAL,
	AFRIKAANS,
	ARABIC,
	BASQUE,
	BELARUSIAN,
	BULGARIAN,
	CATALAN,
	CZECH,
	DANISH,
	DUTCH,
	ESTONIAN,
	FAROESE,
	FINNISH,
	FRENCH,
	GERMAN,
	GREEK,
	HEBREW,
	ICELANDIC,
	INDONESIAN,
	ITALIAN,
	JAPANESE,
	KOREAN,
	LATVIAN,
	LITHUANIAN,
	NORWEGIAN,
	POLISH,
	PORTUGUESE,
	ROMANIAN,
	RUSSIAN,
	SERBOCROATIAN,
	SLOVAK,
	SLOVENIAN,
	SPANISH,
	SWEDISH,
	THAI,
	TURKISH,
	UKRAINIAN,
	VIETNAMESE,
	HUNGARIAN,
	UNKNOWN,
};
DECL_META_ENUM( UTILS_API, Language );
	
enum WindowFlags
{
	FULLSCREEN 			= 1 << 0,            /**< fullscreen window */
	SHOWN 				= 1 << 1,                /**< window is visible */
	HIDDEN 				= 1 << 2,                /**< window is not visible */
	BORDERLESS 			= 1 << 3,            /**< no window decoration */
	RESIZABLE 			= 1 << 4,            /**< window can be resized */
	MINIMIZED 			= 1 << 5,            /**< window is minimized */
	MAXIMIZED 			= 1 << 6,            /**< window is maximized */
	INPUT_GRABBED 		= 1 << 7,        /**< window has grabbed input focus */
	INPUT_FOCUS 		= 1 << 8,            /**< window has input focus */
	MOUSE_FOCUS 		= 1 << 9,            /**< window has mouse focus */
	FOREIGN 			= 1 << 10,                /**< window not created by SDL */
	ALLOW_HIGHDPI 		= 1 << 11,        /**< window should be created in high-DPI mode if supported */
	MOUSE_CAPTURE 		= 1 << 12,        /**< window has mouse captured (unrelated to INPUT_GRABBED) */
	ALWAYS_ON_TOP 		= 1 << 13,        /**< window should always be above others */
	SKIP_TASKBAR 		= 1 << 14,        /**< window should not be added to the taskbar */
	UTILITY 			= 1 << 15,            /**< window should be treated as a utility window */
	TOOLTIP 			= 1 << 16,            /**< window should be treated as a tooltip */
	POPUP_MENU 			= 1 << 17,            /**< window should be treated as a popup menu */
	VULKAN 				= 1 << 18,            /**< window usable for Vulkan surface */
};
DECL_META_ENUM( UTILS_API, WindowFlags);

END_XE_NAMESAPCE

#endif // __TYPE_H__FF3D8A9E_5172_4F88_873F_0CAF1E5289F6
