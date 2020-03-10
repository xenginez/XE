#include "Library.h"

USING_XE

struct XE::Library::Private
{
	XE::Set<XE::String> _Env;
};

XE::Library::Library()
	:_p( new Private )
{

}

XE::Library::~Library()
{
	delete _p;
}

void XE::Library::RegisterEnvPath( const XE::String & path )
{
	Instance()->_p->_Env.insert( path );
}


#if PLATFORM_OS & OS_WINDOWS

#include <Windows.h>

XE::LibraryHandle XE::Library::Open( const String & val )
{
	HMODULE module = ::LoadLibrary( val.ToCString() );
	if( module != nullptr )
	{
		return ( XE::uint64 )( module );
	}

	for( const auto & p : Instance()->_p->_Env )
	{
		HMODULE module = ::LoadLibrary( ( p + "\\" + val ).ToCString() );
		if( module != nullptr )
		{
			return ( XE::uint64 )( module );
		}
	}

	return LibraryHandle::Invalid;
}

void * XE::Library::Symbol( XE::LibraryHandle handle, const String & name )
{
	return ::GetProcAddress( (HMODULE )( handle.GetValue() ), name.ToCString() );
}

bool XE::Library::Close( XE::LibraryHandle handle )
{
	return ::FreeLibrary( (HMODULE )( handle.GetValue() ) );
}
#else

#include <dlfcn.h>

XE::LibraryHandle XE::Library::Open( const String & val )
{
	void * module = ::dlopen( val.ToCString(), RTLD_NOW );
	if( module != nullptr )
	{
		return reinterpret_cast< XE::uint64 >( module );
	}

	for( const auto & p : Instance()->_p->_Env )
	{
		HMODULE module = ::dlopen( ( p + "/" + val ).ToCString() );
		if( module != nullptr )
		{
			return ( XE::uint64 )( module );
		}
	}

	return LibraryHandle::Invalid;
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
