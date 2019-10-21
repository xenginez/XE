#include "RenderMaterial.h"

#include "RenderTechnique.h"

USING_XE

BEG_META( RenderMaterial )
END_META()

XE::RenderMaterial::RenderMaterial()
{

}

XE::RenderMaterial::~RenderMaterial()
{

}

const XE::String & XE::RenderMaterial::GetName() const
{
	return _Name;
}

void XE::RenderMaterial::SetName( const XE::String & val )
{
	_Name = val;
}

const RenderTechniquePtr & XE::RenderMaterial::GetRenderTechnique() const
{
	return _Technique;
}

void XE::RenderMaterial::SetRenderTechnique( const RenderTechniquePtr & val )
{
	_Technique = val;
}

void XE::RenderMaterial::AssetLoad()
{
	if( _Technique )
	{
		_Technique->Startup();
	}
}

void XE::RenderMaterial::AssetUnload()
{
	if( _Technique )
	{
		_Technique->Clearup();
	}
}
