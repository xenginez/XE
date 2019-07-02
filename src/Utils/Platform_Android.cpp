#include "Platform.h"

#if PLATFORM_OS == OS_ANDROID

USING_XE

XE::Language Platform::GetDefaultLanguage()
{
	return Language::ENGLISH;
}

#endif