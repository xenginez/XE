#include "RenderService.h"

#include <tbb/parallel_for.h>

USING_XE

BEG_META( RenderService )
END_META()

struct XE::RenderService::Private
{
	RenderContextPtr _Context;

	Array<LightPtr> _Lights;
	Array<XE::CameraPtr> _Cameras;
	Array<XE::RenderablePtr> _Renderables;
};

XE::RenderService::RenderService()
	:_p( new Private )
{

}

XE::RenderService::~RenderService()
{
	delete _p;
}

void XE::RenderService::Prepare()
{

}

bool XE::RenderService::Startup()
{
	IMetaClassPtr cls;
	ClassID<XE::RenderContext>::Get()->VisitDerivedClass( [&]( IMetaClassPtr val )
														  {
															  cls = val;
														  } );

	if( cls != nullptr )
	{
		if( _p->_Context = SP_CAST<RenderContext>( cls->ConstructPtr().DetachPtr() ) )
		{
			_p->_Context->Startup();
			return true;
		}
	}

	return false;
}

void XE::RenderService::Update()
{
	tbb::parallel_for( XE::uint64( 0 ), _p->_Cameras.size(), [&]( XE::uint64 i )
					   {
						   //_p->_Cameras[i]->GetRenderer()->Render( _p->_Context, _p->_Cameras[i] );
					   } );

	_p->_Context->Present();
}

void XE::RenderService::Clearup()
{
	_p->_Lights.clear();
	_p->_Cameras.clear();
	_p->_Renderables.clear();

	_p->_Context->Clearup();
}

XE::RenderContextPtr XE::RenderService::GetRenderContext() const
{
	return _p->_Context;
}

void XE::RenderService::RegisterLight( const LightPtr & val )
{
	auto it = std::find( _p->_Lights.begin(), _p->_Lights.end(), val );
	if( it != _p->_Lights.end() )
	{
		_p->_Lights.push_back( val );
	}
}

void XE::RenderService::UnregisterLight( const LightPtr & val )
{
	auto it = std::find( _p->_Lights.begin(), _p->_Lights.end(), val );
	if( it != _p->_Lights.end() )
	{
		_p->_Lights.erase( it );
	}
}

void XE::RenderService::RegisterCamera( const CameraPtr & val )
{
	auto it = std::find( _p->_Cameras.begin(), _p->_Cameras.end(), val );
	if( it != _p->_Cameras.end() )
	{
		_p->_Cameras.push_back( val );
	}
}

void XE::RenderService::UnregisterCamera( const CameraPtr & val )
{
	auto it = std::find( _p->_Cameras.begin(), _p->_Cameras.end(), val );
	if( it != _p->_Cameras.end() )
	{
		_p->_Cameras.erase( it );
	}
}

void XE::RenderService::RegisterRenderable( const RenderablePtr & val )
{
	auto it = std::find( _p->_Renderables.begin(), _p->_Renderables.end(), val );
	if( it != _p->_Renderables.end() )
	{
		_p->_Renderables.push_back( val );
	}
}

void XE::RenderService::UnregisterRenderable( const RenderablePtr & val )
{
	auto it = std::find( _p->_Renderables.begin(), _p->_Renderables.end(), val );
	if( it != _p->_Renderables.end() )
	{
		_p->_Renderables.erase( it );
	}
}

const XE::Array<XE::LightPtr> & XE::RenderService::GetLights() const
{
	return _p->_Lights;
}

const XE::Array<XE::CameraPtr> & XE::RenderService::GetCameras() const
{
	return _p->_Cameras;
}

const XE::Array<XE::RenderablePtr> & XE::RenderService::GetRenderables() const
{
	return _p->_Renderables;
}
