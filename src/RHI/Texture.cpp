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

BEG_META( Texture2D )
END_META()

XE::Texture2D::Texture2D()
{

}

XE::Texture2D::~Texture2D()
{

}

BEG_META( Texture3D )
END_META()

XE::Texture3D::Texture3D()
{

}

XE::Texture3D::~Texture3D()
{

}

BEG_META( TextureCube )
END_META()

XE::TextureCube::TextureCube()
{

}

XE::TextureCube::~TextureCube()
{

}

BEG_META( Texture2DArray )
END_META()

XE::Texture2DArray::Texture2DArray()
{

}

XE::Texture2DArray::~Texture2DArray()
{

}
