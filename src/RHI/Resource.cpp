#include "Resource.h"

USING_XE

BEG_META(Resource)
END_META()

XE::Resource::Resource()
{

}

XE::Resource::~Resource()
{

}

XE::ResourceHandle XE::Resource::GetHandle() const
{
	return _Handle;
}

void XE::Resource::SetHandle( ResourceHandle handle )
{
	_Handle = handle;
}

void XE::Resource::Preinitialize( RenderContextRPtr context )
{
	_RenderContext = context;
}

RenderContextRPtr XE::Resource::GetRenderContext() const
{
	return _RenderContext;
}
