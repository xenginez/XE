#include "Material.h"

#include "Technique.h"

USING_XE

BEG_META( Material )
type->Property( "Technique", &Material::_Technique );
END_META()

XE::Material::Material()
{

}

XE::Material::~Material()
{

}

const XE::TechniquePtr & XE::Material::GetTechnique() const
{
	return _Technique;
}
