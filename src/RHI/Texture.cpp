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

XE::TextureHandle XE::Texture::GetHandle() const
{
	return _Handle;
}

XE::TextureFormat XE::Texture::GetFormat() const
{
	return _Format;
}
