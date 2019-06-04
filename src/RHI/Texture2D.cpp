#include "Texture2D.h"

USING_XE

BEG_META(Texture2D)
END_META()

XE::Texture2D::Texture2D()
{

}

XE::Texture2D::~Texture2D()
{

}

XE::uint32 XE::Texture2D::GetMipCount() const
{
	return _MipLevel;
}

XE::uint32 XE::Texture2D::GetWidth( XE::uint32 mip ) const
{
	return _Width;
}

XE::uint32 XE::Texture2D::GetHeight( XE::uint32 mip ) const
{
	return _Height;
}
