#include "RenderKey.h"

USING_XE

bool operator==( const XE::FBOKey& key1, const XE::FBOKey& key2 )
{
	bool result = ( ( key1.ID == key2.ID ) && ( key1.Textures.size() == key2.Textures.size() ) );
	if ( !result )
	{
		return false;
	}

	XE::uint64 tex_count = key1.Textures.size();
	for ( XE::uint64 i = 0; i < tex_count; ++i )
	{
		if ( key1.Textures[i] != key2.Textures[i] )
		{
			return false;
		}
	}

	return true;
}

bool operator==( const XE::TextureKey& key1, const XE::TextureKey& key2 )
{
	return key1.ID == key2.ID && key1.Flags == key2.Flags && key1.Ratio == key2.Ratio &&
		key1.Info.format == key2.Info.format && key1.Info.storageSize == key2.Info.storageSize &&
		key1.Info.width == key2.Info.width && key1.Info.height == key2.Info.height &&
		key1.Info.depth == key2.Info.depth && key1.Info.numMips == key2.Info.numMips &&
		key1.Info.numLayers == key2.Info.numLayers && key1.Info.bitsPerPixel == key2.Info.bitsPerPixel &&
		key1.Info.cubeMap == key2.Info.cubeMap;
}
