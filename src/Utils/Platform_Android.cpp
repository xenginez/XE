#include "Platform.h"

#if PLATFORM_OS == OS_ANDROID

USING_XE

XE::Language Platform::get_default_language()
{
	return Language::ENGLISH;
}

#endif