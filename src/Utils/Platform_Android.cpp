#include "Platform.h"

#if PLATFORM_OS == OS_ANDROID

#include <dlfcn.h>

USING_XE

void * Platform::dlopen( const String& val )
{
	return reinterpret_cast<uint64>(::dlopen( (val.ToStdString() + ".so").c_str(), RTLD_NOW ));
}

void * Platform::dlsym( void * handle, const String& val )
{
	return ::dlsym( reinterpret_cast<void*>(handle), val.ToCString() );
}

bool Platform::dlclose( void * handle )
{
	return reinterpret_cast<bool>(::dlclose( handle ));
}

XE::Language Platform::get_default_language()
{
	return Language::ENGLISH;
}

#endif