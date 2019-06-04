#include "Texture3D.h"

USING_XE

BEG_META(Texture3D)
END_META()

XE::Texture3D::Texture3D()
{

}

XE::Texture3D::~Texture3D()
{

}

XE::uint32 XE::Texture3D::GetDepth( XE::uint32 mip ) const
{
	return _Depth;
}
