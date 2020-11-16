#include "NavigationService.h"

#include <tbb/concurrent_queue.h>
#include <tbb/concurrent_hash_map.h>

#include <recastnavigation/DetourCrowd.h>
#include <recastnavigation/DetourNavMesh.h>
#include <recastnavigation/DetourTileCache.h>
#include <recastnavigation/DetourNavMeshQuery.h>

#include "Interface/IThreadService.h"
#include "Interface/IAssetsService.h"

BEG_META( XE::NavigationService )
END_META()

struct XE::NavigationService::Private
{
	tbb::concurrent_queue<dtNavMesh *> _FreeMeshs;
	tbb::concurrent_hash_map< XE::uint64, dtNavMesh * > _NavMeshs;
};

XE::NavigationService::NavigationService()
{

}

XE::NavigationService::~NavigationService()
{

}

void XE::NavigationService::Prepare()
{
}

bool XE::NavigationService::Startup()
{
	for( int i = 0; i < 9; ++i )
	{
		_p->_FreeMeshs.push( new dtNavMesh );
	}

	return true;
}

void XE::NavigationService::Update()
{

}

void XE::NavigationService::Clearup()
{
	dtNavMesh * mesh = nullptr;
	while( _p->_FreeMeshs.try_pop( mesh ) )
	{
		delete mesh;
	}

	for( auto it : _p->_NavMeshs )
	{
		delete it.second;
	}
	_p->_NavMeshs.clear();
}

XE::Array< XE::Vec3f > XE::NavigationService::FindRoute( const XE::OBB & geometry, const XE::Vec3f & start, const XE::Vec3f & end )
{
	dtNavMeshQuery query;

	return {};
}

XE::Array< XE::Vec3f > XE::NavigationService::FindRoute( const XE::AABB & geometry, const XE::Vec3f & start, const XE::Vec3f & end )
{
	dtNavMeshQuery query;

	return {};
}

XE::Array< XE::Vec3f > XE::NavigationService::FindRoute( const XE::Capsule & geometry, const XE::Vec3f & start, const XE::Vec3f & end )
{
	dtNavMeshQuery query;

	return {};
}

XE::NavMeshHandle XE::NavigationService::AddNavMeshTile( const XE::FileSystem::Path & val )
{
	static std::atomic< XE::uint64 > g_handle = 0;

	XE::uint64 handle = g_handle++;

	dtNavMesh * mesh = nullptr;

	if( !_p->_FreeMeshs.try_pop( mesh ) )
	{
		mesh = new dtNavMesh;
	}

	GetFramework()->GetThreadService()->PostTask( ThreadType::IO, [this, handle, mesh, val]()
												  {
													  auto view = GetFramework()->GetAssetsService()->Load( val );

													  mesh->init( reinterpret_cast< unsigned char * >( const_cast< char * >( view.data() ) ), view.size(), 0 );

													  _p->_NavMeshs.insert( { handle, mesh } );
												  } );

	return { handle };
}

void XE::NavigationService::RemvoeNavMesh( XE::NavMeshHandle val )
{
	tbb::concurrent_hash_map< XE::uint64, dtNavMesh * >::accessor it;
	if( _p->_NavMeshs.find( it, val.GetValue() ) )
	{
		it->second->~dtNavMesh();
		_p->_FreeMeshs.push( it->second );
		while( !_p->_NavMeshs.erase( it ) );
	}
}

XE::NavObstacleHandle XE::NavigationService::AddObstacle( const XE::OBB & geometry )
{
	for( auto it : _p->_NavMeshs )
	{
		const dtNavMeshParams * param = it.second->getParams();

		XE::AABB box( XE::Vec3f( param->orig[0], param->orig[1] - ( param->orig[1] / 2 ), param->orig[2] ),
					  XE::Vec3f( param->orig[0] + ( param->maxTiles * param->tileWidth ), param->orig[1] + ( param->orig[1] / 2 ), param->orig[2] + ( param->maxTiles * param->tileHeight ) ) );

		if( box.Intersect( geometry ) )
		{
			it.second;
		}
	}

	return {};
}

XE::NavObstacleHandle XE::NavigationService::AddObstacle( const XE::AABB & geometry )
{
	return {};
}

void XE::NavigationService::RemoveObstacle( XE::NavObstacleHandle handle )
{

}
