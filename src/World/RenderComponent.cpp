#include "RenderComponent.h"

#include "GameObject.h"

USING_XE

BEG_META( RenderComponent )
END_META()

XE::RenderComponent::RenderComponent()
{

}

XE::RenderComponent::~RenderComponent()
{

}

XE::AABB XE::RenderComponent::GetBoundingBox() const
{
	AABB ret;

	auto children = GetChildren();
	for ( auto child : children )
	{
		if ( auto rcom = DP_CAST<RenderComponent>( child ) )
		{
			AABB raabb = rcom->GetBoundingBox();

			ret.min = Mathf::Min( ret.min, raabb.min );
			ret.max = Mathf::Max( ret.max, raabb.max );
		}
	}

	return ret;
}
