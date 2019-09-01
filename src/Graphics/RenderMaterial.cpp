#include "RenderMaterial.h"

#include "Technique.h"

USING_XE

BEG_META( RenderMaterial )
type->Property( "Technique", &RenderMaterial::_Technique );
END_META()

XE::RenderMaterial::RenderMaterial()
{

}

XE::RenderMaterial::~RenderMaterial()
{

}

const XE::TechniquePtr & XE::RenderMaterial::GetTechnique() const
{
	return _Technique;
}
