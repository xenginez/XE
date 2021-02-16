#include "AssetsService.h"

#include <fstream>

#include <tbb/concurrent_hash_map.h>
#define TBB_PREVIEW_CONCURRENT_LRU_CACHE 1
#include <tbb/concurrent_lru_cache.h>

#include "Utils/Zipper.h"
#include "Utils/Logger.h"

BEG_META( XE::AssetsService )
END_META()

struct XE::AssetsService::Private
{
	XE::Array< std::ifstream > _Streams;
	XE::Array< XE::Unzipper > _Packages;
	tbb::concurrent_hash_map<XE::String, XE::ObjectWPtr, StringHashCompare > _ObjectCache;
	tbb::concurrent_lru_cache<XE::String, XE::MemoryStream> _MemoryCache = { []( XE::String )->XE::MemoryStream {return {};}, 1000 };
};

XE::AssetsService::AssetsService()
	:_p( new Private )
{

}

XE::AssetsService::~AssetsService()
{
	delete _p;
}

void XE::AssetsService::Prepare()
{
}

bool XE::AssetsService::Startup()
{
	std::filesystem::recursive_directory_iterator beg( GetFramework()->GetAssetsPath() );
	std::filesystem::recursive_directory_iterator end;
	for( ; beg != end; ++beg )
	{
		auto path = beg->path();
		if( path.extension() == ".assets" )
		{
			std::ifstream ifs( path, std::ios::binary );
			if( ifs.is_open() )
			{
				_p->_Packages.push_back( { _p->_Streams.emplace_back( std::move( ifs ) ) } );
			}
			else
			{
				XE_LOG( LoggerLevel::Error, "%1 open failed!", path );
			}
		}
	}

	return true;
}

void XE::AssetsService::Update()
{
	for( auto it = _p->_ObjectCache.begin(); it != _p->_ObjectCache.end(); ++it )
	{
		if( it->second.expired() )
		{
			_p->_ObjectCache.erase( it->first );
		}
	}
}

void XE::AssetsService::Clearup()
{
	_p->_ObjectCache.clear();
	_p->_Packages.clear();
	_p->_Streams.clear();
}

XE::MemoryView XE::AssetsService::Load( const XE::String & path )
{
	auto list = XE::StringUtils::Split( path, ":" );

	auto handle = _p->_MemoryCache[list[1]];
	if( handle && handle.value().view() )
	{
		return handle.value().view();
	}

	auto fullpath( GetFramework()->GetAssetsPath() / list[0] );

	if( std::filesystem::exists( fullpath ) )
	{
		std::ifstream ifs( fullpath.u8string() );
		if( ifs.is_open() )
		{
			handle.value().clear();
			char buf[2048];

			while( !ifs.eof() )
			{
				auto sz = ifs.readsome( buf, 2048 );
				handle.value().write( buf, sz );
			}

			return handle.value().view();
		}
	}

	for( auto & zip : _p->_Packages )
	{
		if( zip.ExtractEntiy( list[1] ) )
		{
			handle.value().clear();
			zip.GetEntryData( path, handle.value() );
			return handle.value().view();
		}
	}

	XE_LOG( LoggerLevel::Error, "not find file %1.", path );

	return nullptr;
}

void XE::AssetsService::AsyncLoad( const XE::String & path, const LoadFinishCallback & callback )
{
	CHECK_THREAD( ThreadType::IO ) ? callback( Load( path ) ) : GetFramework()->GetServiceT< XE::IThreadService >()->PostTask( ThreadType::IO, [=]()
																											  {
																												  callback( Load( path ) );
																											  } );
}

XE::ObjectPtr XE::AssetsService::LoadObject( const XE::String & path )
{
	tbb::concurrent_hash_map<XE::String, XE::ObjectWPtr, StringHashCompare >::accessor it;
	if( _p->_ObjectCache.find( it, path ) )
	{
		if( !it->second.expired() )
		{
			return it->second.lock();
		}
	}

	if( auto mem = Load( path ) )
	{
		XE::BinaryLoadArchive load( mem );

		XE::ObjectPtr obj;

		load & obj;

		obj->AssetLoad();

		_p->_ObjectCache.insert( { path, obj } );

		return obj;
	}

	return nullptr;
}

void XE::AssetsService::AsyncLoadObject( const XE::String & path, const LoadObjectFinishCallback & callback )
{
	CHECK_THREAD( ThreadType::IO ) ? callback( LoadObject( path ) ) : GetFramework()->GetServiceT< XE::IThreadService >()->PostTask( ThreadType::IO, [=]()
																													{
																														callback( LoadObject( path ) );
																													} );
}
