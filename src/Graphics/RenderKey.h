/*!
 * \file   RenderKey.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __RENDERKEY_H__DF0382C2_A5DB_465A_8C19_1BC6EBD2A567
#define __RENDERKEY_H__DF0382C2_A5DB_465A_8C19_1BC6EBD2A567

#include "Type.h"

BEG_XE_NAMESPACE

struct GRAPHICS_API FBOKey
{
	String ID;
	Array<TexturePtr> Textures;
};

struct GRAPHICS_API TextureKey
{
	String ID;
	TextureInfo Info;
	uint64 Flags = BGFX_TEXTURE_NONE;
	BackbufferRatio Ratio = BackbufferRatio::Count;
};

END_XE_NAMESAPCE

bool operator==( const XE::FBOKey& key1, const XE::FBOKey& key2 );

bool operator==( const XE::TextureKey& key1, const XE::TextureKey& key2 );

namespace std
{
	template <> struct hash<XE::FBOKey>
	{
		using argument_type = XE::FBOKey;
		using result_type = XE::uint64;

		result_type operator()( argument_type const& s ) const
		{
			std::hash<XE::TexturePtr> th;

			XE::uint64 seed = std::hash<XE::String>()( s.ID );

			for ( auto& tex : s.Textures )
			{
				seed ^= th( tex );
			}

			return seed;
		}
	};

	template <> struct hash<XE::TextureKey>
	{
		using argument_type = XE::TextureKey;
		using result_type = XE::uint64;

		result_type operator()( argument_type const& s ) const
		{
			std::hash<XE::int64> ih;

			XE::uint64 seed = std::hash<XE::String>()( s.ID );

			seed ^= ih( static_cast<XE::int64>( s.Info.format ) );
			seed ^= ih( static_cast<XE::int64>( s.Info.storageSize ) );
			seed ^= ih( static_cast<XE::int64>( s.Info.width ) );
			seed ^= ih( static_cast<XE::int64>( s.Info.height ) );
			seed ^= ih( static_cast<XE::int64>( s.Info.depth ) );
			seed ^= ih( static_cast<XE::int64>( s.Info.numLayers ) );
			seed ^= ih( static_cast<XE::int64>( s.Info.numMips ) );
			seed ^= ih( static_cast<XE::int64>( s.Info.bitsPerPixel ) );
			seed ^= ih( static_cast<XE::int64>( s.Info.cubeMap ) );

			return seed;
		}
	};

	template<> struct equal_to<XE::FBOKey>
	{
		using first_argument_type = XE::FBOKey;
		using second_argument_type = XE::FBOKey;
		using result_type = bool;

		bool operator()( const first_argument_type& _Left, const second_argument_type& _Right ) const
		{
			bool result = ( ( _Left.ID == _Right.ID ) && ( _Left.Textures.size() == _Right.Textures.size() ) );
			if ( !result )
			{
				return false;
			}

			XE::uint64 tex_count = _Left.Textures.size();
			for ( XE::uint64 i = 0; i < tex_count; ++i )
			{
				if ( _Left.Textures[i] != _Right.Textures[i] )
				{
					return false;
				}
			}

			return true;
		}
	};

	template<> struct equal_to<XE::TextureKey>
	{
		using first_argument_type = XE::TextureKey;
		using second_argument_type = XE::TextureKey;
		using result_type = bool;

		bool operator()( const first_argument_type& _Left, const second_argument_type& _Right ) const
		{
			return _Left.ID == _Right.ID && _Left.Flags == _Right.Flags && _Left.Ratio == _Right.Ratio &&
				_Left.Info.format == _Right.Info.format && _Left.Info.storageSize == _Right.Info.storageSize &&
				_Left.Info.width == _Right.Info.width && _Left.Info.height == _Right.Info.height &&
				_Left.Info.depth == _Right.Info.depth && _Left.Info.numMips == _Right.Info.numMips &&
				_Left.Info.numLayers == _Right.Info.numLayers && _Left.Info.bitsPerPixel == _Right.Info.bitsPerPixel &&
				_Left.Info.cubeMap == _Right.Info.cubeMap;
		}
	};
};

#endif // __RENDERKEY_H__DF0382C2_A5DB_465A_8C19_1BC6EBD2A567
