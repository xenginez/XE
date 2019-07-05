#include "Texture.h"

USING_XE

BEG_META(Texture)
END_META()

XE::Texture::Texture()
{

}

XE::Texture::~Texture()
{

}

XE::memory_view XE::Texture::Map( AccessType val )
{
	return memory_view();
}

void XE::Texture::Unmap()
{

}

XE::TextureHandle XE::Texture::GetHandle() const
{
	return _Handle;
}

XE::TextureFormat XE::Texture::GetFormat() const
{
	return _Format;
}
