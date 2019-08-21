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
	String ContextName;
#if PLATFORM_OS & OS_WINDOWS
#	if PLATFORM_OS & OS_WINDOWS_10
	ContextName = "XE::D3D12RenderContext";
#	else
	ContextName = "XE::D3D11RenderContext";
#	endif
#elif PLATFORM_OS & OS_MAC
#	if PLATFORM_OS > OS_MAC_10_8
	ContextName = "XE::MetalRenderContext";
#	else
	ContextName = "XE::GLES3RenderContext";
#	endif
#elif PLATFORM_OS & OS_IOS
#	if PLATFORM_OS > OS_IOS_8
	ContextName = "XE::MetalRenderContext";
#	else
	ContextName = "XE::GLES3RenderContext";
#	endif
#elif PLATFORM_OS & OS_ANDROID
	ContextName = "XE::GLES2RenderContext";
#elif PLATFORM_OS & OS_XBOXONE
	ContextName = "XE::D3D12RenderContext";
#elif PLATFORM_OS & OS_LINUX
	ContextName = "XE::OGLRenderContext";
#elif PLATFORM_OS & OS_PS4
	ContextName = "XE::OGLRenderContext";
#else
	ContextName = "XE::EmptyRenderContext";
#endif

	if( IMetaClassPtr cls = Reflection::FindClass( ContextName ) )
	{
		_p->_Context = SP_CAST<RenderContext>( cls->ConstructPtr().DetachPtr() );
	}
	else
	{
		throw XE::RuntimeException();
	}
}

bool XE::RenderService::Startup()
{
	if(_p->_Context )
	{
		_p->_Context->Startup();
		return true;
	}

	return false;
}

void XE::RenderService::Update()
{
	std::sort( _p->_Cameras.begin(), _p->_Cameras.end(), []( const CameraPtr & left, const CameraPtr & right )
			   {
				   return left->GetDepth() < right->GetDepth();
			   } );


	tbb::parallel_for( XE::uint64( 0 ), _p->_Cameras.size(), [&]( XE::uint64 i )
					   {
						   _p->_Cameras[i]->GetRenderer()->Render( _p->_Context, _p->_Cameras[i] );
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
