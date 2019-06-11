#include "Library.h"

#include "Platform.h"

USING_XE


#if PLATFORM_OS == OS_WINDOWS
#include <Windows.h>

XE::uint64 dlopen( const String& name )
{
	return reinterpret_cast<XE::uint64>( ::LoadLibrary( (name.ToStdString() + ".dll").c_str() ) );
}

void * dlsym( XE::uint64 handle, const String& name )
{
	return ::GetProcAddress( reinterpret_cast<HMODULE>( handle ), name.ToCString() );
}

bool dlclose( XE::uint64 handle )
{
	return ::FreeLibrary( reinterpret_cast<HMODULE>( handle ) );
}
#else
#include <dlfcn.h>

#if PLATFORM_OS == OS_IOS || PLATFORM_OS == OS_MAC
#define LIB_EXT ".dylib"
#else
#define LIB_EXT ".so"
#endif

namespace XE
{
	XE::uint64 dlopen( const String &val )
	{
		return reinterpret_cast<XE::uint64>(::dlopen(( val.ToStdString() + LIB_EXT ).c_str(), RTLD_NOW));
	}
	
	void * dlsym( XE::uint64 handle, const String &val )
	{
		return ::dlsym(reinterpret_cast<void *>(handle), val.ToCString());
	}
	
	bool dlclose( XE::uint64 handle )
	{
		return static_cast<bool>(::dlclose(( void * ) handle));
	}
}

#endif

struct XE::Library::Private
{
	Array < Pair < XE::uint64, String > > Librarys;
	Array < std::filesystem::path > SearchPaths;
};

XE::Library::Library()
		:_p(new Private)
{
	_p->Librarys.push_back(std::make_pair(0, ""));
}

XE::Library::~Library()
{
	for( const auto &lib : _p->Librarys )
	{
		XE::dlclose(lib.first);
	}
	
	delete _p;
}

XE::uint64 XE::Library::Open( const String &val )
{
	for( int i = 0; i < This()->_p->Librarys.size(); ++i )
	{
		if( This()->_p->Librarys[i].second == val )
		{
			return static_cast<XE::uint64>(i);
		}
	}
	
	for( const auto &it : This()->_p->SearchPaths )
	{
		auto h = XE::dlopen(( it / val.ToCString()).string());
		if( h != 0 )
		{
			This()->_p->Librarys.push_back(std::make_pair(h, val));
			return This()->_p->Librarys.size() - 1;
		}
	}
	
	return 0;
}

void * XE::Library::Symbol( XE::uint64 index, const String &name )
{
	if( auto lib = This()->_p->Librarys[index].first )
	{
		return XE::dlsym(lib, name);
	}
	
	return nullptr;
}

void XE::Library::Close( XE::uint64 index )
{
	if( auto lib = This()->_p->Librarys[index].first )
	{
		XE::dlclose(lib);
		
		This()->_p->Librarys[index].first = 0;
		This()->_p->Librarys[index].second = "";
	}
}

XE::String XE::Library::Name( XE::uint64 index )
{
	return This()->_p->Librarys[index].second;
}

void XE::Library::InsertSearchPath( const std::filesystem::path &val )
{
	This()->_p->SearchPaths.push_back(val);
}

const XE::Array < std::filesystem::path > &XE::Library::GetSearchPaths() const
{
	return This()->_p->SearchPaths;
}
