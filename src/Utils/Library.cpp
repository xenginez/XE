#include "Library.h"

USING_XE

#if PLATFORM_OS & OS_WINDOWS

#include <Windows.h>

XE::LibraryHandle XE::Library::Open( const String & val )
{
	return reinterpret_cast< XE::uint64 >( ::LoadLibrary( val.ToCString() ) );
}

void * XE::Library::Symbol( XE::LibraryHandle handle, const String & name )
{
	return ::GetProcAddress( reinterpret_cast< HMODULE >( handle.GetValue() ), name.ToCString() );
}

bool XE::Library::Close( XE::LibraryHandle handle )
{
	return ::FreeLibrary( reinterpret_cast< HMODULE >( handle.GetValue() ) );
}
#else

#include <dlfcn.h>

XE::LibraryHandle XE::Library::Open( const String & val )
{
	return reinterpret_cast< XE::uint64 >( ::dlopen( val.ToCString(), RTLD_NOW ) );
}

void * XE::Library::Symbol( XE::LibraryHandle handle, const String & name )
{
	return ::dlsym( reinterpret_cast< void * >( handle.GetValue() ), val.ToCString() );
}

bool XE::Library::Close( XE::LibraryHandle handle )
{
	return static_cast< bool >( ::dlclose( reinterpret_cast< void * >( handle.GetValue() ) ) );
}
#endif
