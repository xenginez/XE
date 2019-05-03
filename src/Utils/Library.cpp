#include "Library.h"

#include "Platform.h"

USING_XE

struct XE::Library::Private
{
	Array < Pair < uint64, String > > Librarys;
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
		Platform::dlclose(lib.first);
	}
	
	delete _p;
}

XE::uint64 XE::Library::Open( const String &val )
{
	for( int i = 0; i < This()->_p->Librarys.size(); ++i )
	{
		if( This()->_p->Librarys[i].second == val )
		{
			return static_cast<uint64>(i);
		}
	}
	
	for( const auto &it : This()->_p->SearchPaths )
	{
		auto h = Platform::dlopen(( it / val.ToCString()).string());
		if( h != 0 )
		{
			This()->_p->Librarys.push_back(std::make_pair(h, val));
			return This()->_p->Librarys.size() - 1;
		}
	}
	
	return 0;
}

void * XE::Library::Symbol( uint64 index, const String &name )
{
	if( auto lib = This()->_p->Librarys[index].first )
	{
		return Platform::dlsym(lib, name);
	}
	
	return nullptr;
}

void XE::Library::Close( uint64 index )
{
	if( auto lib = This()->_p->Librarys[index].first )
	{
		Platform::dlclose(lib);
		
		This()->_p->Librarys[index].first = 0;
		This()->_p->Librarys[index].second = "";
	}
}

XE::String XE::Library::Name( uint64 index )
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
