#include "Platform.h"
#if PLATFORM_OS == OS_IOS

#include <dlfcn.h>

USING_XE

uint64 Platform::dlopen( const String &val )
{
	return reinterpret_cast<uint64>(::dlopen(( val.ToStdString() + ".dylib" ).c_str(), RTLD_NOW));
}

void * Platform::dlsym( uint64 handle, const String &val )
{
	return ::dlsym(reinterpret_cast<void *>(handle), val.ToCString());
}

bool Platform::dlclose( uint64 handle )
{
	return static_cast<bool>(::dlclose(( void * ) handle));
}

#endif