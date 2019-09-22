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

void XE::Technique::Startup()
{
	for( auto & pass : _Passes )
	{
		pass->_Technique = XE_THIS( Technique );
		pass->Startup();
	}

	OnStartup();
}

void XE::Technique::Render()
{
	for( auto & pass : _Passes )
	{
		pass->Render();
	}

	OnRender();
}

void XE::Technique::Clearup()
{
	for( auto & pass : _Passes )
	{
		pass->Clearup();
	}

	OnClearup();
}
