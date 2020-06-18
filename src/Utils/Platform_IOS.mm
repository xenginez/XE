#include "Platform.h"
#if PLATFORM_OS & OS_IOS



XE::Language XE::Platform::GetDefaultLanguage()
{
	return Language::ENGLISH;
}

#endif