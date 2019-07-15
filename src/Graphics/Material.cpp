#include "Material.h"

USING_XE

BEG_META(Material)
END_META()

XE::Material::Material()
{

}

XE::Material::~Material()
{

}

XE::RenderPassPtr XE::Material::GetRenderPass() const
{
	return _Pass;
}

void XE::Material::SetRenderPass( const RenderPassPtr & val )
{
	_Pass = val;
}
