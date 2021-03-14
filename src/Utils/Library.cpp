#include "Library.h"



struct XE::Library::Private
{
	XE::Set<std::filesystem::path> _Env;
};

XE::Library::Library()
	:_p( new Private )
{

}

XE::Library::~Library()
{
	delete _p;
}

void XE::Library::RegisterEnvPath( const std::filesystem::path & path )
{
	Instance()->_p->_Env.insert( path );
}


#if PLATFORM_OS & OS_WINDOWS

#include <Windows.h>

XE::LibraryHandle XE::Library::Open( const String & val )
{
	HMODULE module = ::LoadLibrary( XE::string_convert<utf8_encode, ansi_encode>::convert( val.c_str() ).c_str() );
	if( module != nullptr )
	{
		return XE::HandleCast< XE::Library >( ( XE::uint64 )( module ) );
	}

	for( const auto & p : Instance()->_p->_Env )
	{
		HMODULE module = ::LoadLibrary( XE::string_convert<utf8_encode, ansi_encode>::convert( ( p / val.c_str() ).u8string() ).c_str() );
		if( module != nullptr )
		{
			return XE::HandleCast< XE::Library >( ( XE::uint64 )( module ) );
		}
	}

	return LibraryHandle::Invalid;
}

void * XE::Library::Symbol( XE::LibraryHandle handle, const String & name )
{
	return ::GetProcAddress( (HMODULE )( handle.GetValue() ), name.c_str() );
}

bool XE::Library::Close( XE::LibraryHandle handle )
{
	return ::FreeLibrary( (HMODULE )( handle.GetValue() ) );
}
#else

#include <dlfcn.h>

XE::LibraryHandle XE::Library::Open( const String & val )
{
	void * module = ::dlopen( val.c_str(), RTLD_NOW );
	if( module != nullptr )
	{
		return reinterpret_cast< XE::uint64 >( module );
	}

	for( const auto & p : Instance()->_p->_Env )
	{
		HMODULE module = ::dlopen( ( p / val.c_str() ).u8string().c_str() );
		if( module != nullptr )
		{
			return ( XE::uint64 )( module );
		}
	}

	return LibraryHandle::Invalid;
}

void * XE::Library::Symbol( XE::LibraryHandle handle, const String & name )
{
	return ::dlsym( reinterpret_cast< void * >( handle.GetValue() ), val.c_str() );
}

bool XE::Library::Close( XE::LibraryHandle handle )
{
	return static_cast< bool >( ::dlclose( reinterpret_cast< void * >( handle.GetValue() ) ) );
}
#endif
