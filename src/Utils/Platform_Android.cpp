#include "Platform.h"

#if PLATFORM_OS & OS_ANDROID



XE::Language XE::Platform::GetDefaultLanguage()
{
	return Language::ENGLISH;
}

#endif