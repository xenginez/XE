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
DECL_ALLOCATOR_POLL( ProfilerFrame );

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

END_XE_NAMESPACE

#endif // __TYPE_H__FF3D8A9E_5172_4F88_873F_0CAF1E5289F6
