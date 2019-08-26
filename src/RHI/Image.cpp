#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

USING_XE

BEG_META( Image )
END_META()

XE::Image::Image()
	:_Width( 0 ), _Height( 0 ), _Channels( 0 ), _IsHDR( false )
{
	
}

XE::Image::Image( XE::memory_view & val )
	: _Width( 0 ), _Height( 0 ), _Channels( 0 ), _IsHDR( false )
{
	Load( val );
}

XE::Image::Image( const std::filesystem::path & val )
	: _Width( 0 ), _Height( 0 ), _Channels( 0 ), _IsHDR( false )
{
	Load( val );
}

XE::Image::Image( XE::uint32 width, XE::uint32 height, XE::uint32 channels, bool is_hdr /*= false */ )
	: _Width( _Width ), _Height( _Height ), _Channels( channels ), _IsHDR( is_hdr )
{
	if( _IsHDR )
	{
		_HDRData.resize( _Width * _Height * _Channels * sizeof( XE::float32 ) );
	}
	else
	{
		_Data.resize( _Width * _Height * _Channels * sizeof( XE::uint8 ) );
	}
}

XE::Image::Image( const Image & val )
	: _Width( val._Width ), _Height( val._Height ), _Channels( val._Channels ), _Data( val._Data ), _IsHDR( val._IsHDR )
{

}

XE::Image::~Image()
{

}

bool XE::Image::Load( XE::memory_view val )
{
	_IsHDR = ( stbi_is_hdr_from_memory( reinterpret_cast< const stbi_uc * >( val.data() ), (int )val.size() ) != 0 );

	if( _IsHDR )
	{
		auto data = stbi_loadf_from_memory( reinterpret_cast< const stbi_uc * >( val.data() ), (int )val.size(), &_Width, &_Height, &_Channels, 0 );

		if( data != nullptr )
		{
			_HDRData.resize( _Width * _Height * _Channels * sizeof( XE::float32 ) );

			std::memcpy( _Data.data(), data, _Data.size() * sizeof( XE::float32 ) );

			STBI_FREE( data );

			return true;
		}
	}
	else
	{
		auto data = stbi_load_from_memory( reinterpret_cast< const stbi_uc * >( val.data() ), ( int )val.size(), &_Width, &_Height, &_Channels, 0 );

		if( data != nullptr )
		{
			_Data.resize( _Width * _Height * _Channels * sizeof( XE::uint8 ) );

			std::memcpy( _Data.data(), data, _Data.size() * sizeof( XE::uint8 ) );

			STBI_FREE( data );

			return true;
		}
	}

	return false;
}

bool XE::Image::Load( const std::filesystem::path & val )
{
	_IsHDR = ( stbi_is_hdr( val.string().c_str() ) != 0 );

	if( _IsHDR )
	{
		auto data = stbi_loadf( val.string().c_str(), &_Width, &_Height, &_Channels, 0 );

		if( data != nullptr )
		{
			_HDRData.resize( _Width * _Height * _Channels * sizeof( XE::float32 ) );

			std::memcpy( _Data.data(), data, _Data.size() * sizeof( XE::float32 ) );

			STBI_FREE( data );

			return true;
		}
	}
	else
	{
		auto data = stbi_load( val.string().c_str(), &_Width, &_Height, &_Channels, 0 );

		if( data != nullptr )
		{
			_Data.resize( _Width * _Height * _Channels * sizeof( XE::uint8 ) );

			std::memcpy( _Data.data(), data, _Data.size() );

			STBI_FREE( data );

			return true;
		}
	}

	return false;
}

bool XE::Image::Save( const std::filesystem::path & val )
{
	std::string ext = val.extension().string();
	std::transform( ext.begin(), ext.end(), ext.begin(), ::tolower );

	if( ext == ".jpg" )
	{
		if( _IsHDR )
		{
			auto data = stbi__hdr_to_ldr( _HDRData.data(), _Width, _Height, _Channels );
			if( data != nullptr )
			{
				stbi_write_jpg( val.string().c_str(), _Width, _Height, _Channels, data, 0 );
				STBI_FREE( data );
				return true;
			}
		}
		else
		{
			stbi_write_jpg( val.string().c_str(), _Width, _Height, _Channels, _Data.data(), 0 );
			return true;
		}
	}
	else if( ext == ".png" )
	{
		if( _IsHDR )
		{
			auto data = stbi__hdr_to_ldr( _HDRData.data(), _Width, _Height, _Channels );
			if( data != nullptr )
			{
				stbi_write_png( val.string().c_str(), _Width, _Height, _Channels, data, 0 );
				STBI_FREE( data );
				return true;
			}
		}
		else
		{
			stbi_write_png( val.string().c_str(), _Width, _Height, _Channels, _Data.data(), 0 );
			return true;
		}
	}
	else if( ext == ".tga" )
	{
		if( _IsHDR )
		{
			auto data = stbi__hdr_to_ldr( _HDRData.data(), _Width, _Height, _Channels );
			if( data != nullptr )
			{
				stbi_write_tga( val.string().c_str(), _Width, _Height, _Channels, data );
				STBI_FREE( data );
				return true;
			}
		}
		else
		{
			stbi_write_tga( val.string().c_str(), _Width, _Height, _Channels, _Data.data() );
			return true;
		}
	}
	else if( ext == ".bmp" )
	{
		if( _IsHDR )
		{
			auto data = stbi__hdr_to_ldr( _HDRData.data(), _Width, _Height, _Channels );
			if( data != nullptr )
			{
				stbi_write_bmp( val.string().c_str(), _Width, _Height, _Channels, data );
				STBI_FREE( data );
				return true;
			}
		}
		else
		{
			stbi_write_bmp( val.string().c_str(), _Width, _Height, _Channels, _Data.data() );
			return true;
		}
	}
	else if( ext == ".hdr" )
	{
		if( !_IsHDR )
		{
			auto data = stbi__ldr_to_hdr( _Data.data(), _Width, _Height, _Channels );
			if( data != nullptr )
			{
				stbi_write_hdr( val.string().c_str(), _Width, _Height, _Channels, data );
				STBI_FREE( data );
				return true;
			}
		}
		else
		{
			stbi_write_hdr( val.string().c_str(), _Width, _Height, _Channels, _HDRData.data() );
			return true;
		}
	}

	return false;
}

bool XE::Image::IsHDR() const
{
	return _IsHDR;
}

XE::uint32 XE::Image::GetWidth() const
{
	return _Width;
}

XE::uint32 XE::Image::GetHeight() const
{
	return _Height;
}

XE::uint32 XE::Image::GetChannels() const
{
	return _Channels;
}

XE::uint64 XE::Image::Size() const
{
	return _Data.size();
}

XE::uint64 XE::Image::Count() const
{
	return Size() / _Channels;
}

Color XE::Image::GetPixel( XE::uint32 x, XE::uint32 y ) const
{
	if( !_IsHDR )
	{
		return Color();
	}

	return Color();
}

void XE::Image::SetPixel( XE::uint32 x, XE::uint32 y, const Color & val )
{
	if( !_IsHDR )
	{

	}
}

XE::FColor XE::Image::GetHDRPixel( XE::uint32 x, XE::uint32 y ) const
{
	if( _IsHDR )
	{
		return FColor();
	}

	return FColor();
}

void XE::Image::SetHDRPixel( XE::uint32 x, XE::uint32 y, const FColor & val )
{
	if( _IsHDR )
	{

	}
}

XE::memory_view XE::Image::GetPixels() const
{
	return XE::memory_view( reinterpret_cast< const std::byte * >( _Data.data() ), _Data.size() );
}

XE::basic_memory_view<XE::float32> XE::Image::GetHDRPixels() const
{
	return XE::basic_memory_view<XE::float32>( _HDRData.data(), _HDRData.size() );
}

Image XE::Image::Copy( XE::uint32 x, XE::uint32 y, XE::uint32 width, XE::uint32 height ) const
{
	return Image();
}

void XE::Image::Roate( XE::float32 val )
{

}

void XE::Image::Scaled( XE::float32 x, XE::float32 y )
{

}
