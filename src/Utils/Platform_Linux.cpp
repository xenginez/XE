#include "Platform.h"
#if PLATFORM_OS & OS_LINUX



XE::Language XE::Platform::GetDefaultLanguage()
{
	return Language::ENGLISH;
}

#endif