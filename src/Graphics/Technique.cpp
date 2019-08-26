#include "Technique.h"

#include "RenderPass.h"

USING_XE

BEG_META( Technique )
END_META()

XE::Technique::Technique()
{

}

XE::Technique::~Technique()
{

}

void XE::Technique::Startup( IRenderContextPtr & context )
{
	for( auto & pass : _Passes )
	{
		pass->_Technique = XE_THIS( Technique );
		pass->Startup( context );
	}

	OnStartup( context );
}

void XE::Technique::Render( IRenderContextPtr & context )
{
	for( auto & pass : _Passes )
	{
		pass->Render( context );
	}

	OnRender( context );
}

void XE::Technique::Clearup( IRenderContextPtr & context )
{
	for( auto & pass : _Passes )
	{
		pass->Clearup( context );
	}

	OnClearup( context );
}
