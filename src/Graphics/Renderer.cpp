#include "Renderer.h"

#include "RenderQueue.h"

USING_XE

BEG_META( Renderer )
END_META()

XE::Renderer::Renderer()
{

}

XE::Renderer::~Renderer()
{

}

void XE::Renderer::Startup()
{
	_Queue = XE::make_shared<RenderQueue>();

	OnStartup();
}

void XE::Renderer::Render( IRenderContextPtr & context, CameraPtr & camera )
{
	OnRender( context, camera );

	auto list = context->CreateCommandList( CommandListType::DIRECT );

	// TODO: set commandlist viewport rendertarget ...

	_Queue->Flush( list );

	list->Close();

//	context->DestoryCommandList( list );
}

void XE::Renderer::Clearup()
{
	OnClearup();

	_Queue = nullptr;
}
