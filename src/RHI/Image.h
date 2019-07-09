/*!
 * \file    Image.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-17
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __IMAGE_H__43F807F7_67DE_4C1F_BC4B_78BDA64E3A4E
#define __IMAGE_H__43F807F7_67DE_4C1F_BC4B_78BDA64E3A4E

#include "Type.h"

BEG_XE_NAMESPACE

class RHI_API Image
{
	OBJECT(Image)
	
public:
	Image();

	Image( XE::basic_memory_view<XE::uint8> & val );

	Image( const std::filesystem::path & val );

	Image( XE::uint32 width, XE::uint32 height, XE::uint32 channels, bool is_hdr = false );

	Image( const Image& val );

	~Image();

public:
	bool Load( XE::basic_memory_view<XE::uint8> val );

	bool Load( const std::filesystem::path& val );

public:
	bool Save( const std::filesystem::path& val );

public:
	bool IsHDR() const;

	XE::uint32 GetWidth() const;

	XE::uint32 GetHeight() const;

	XE::uint32 GetChannels() const;

public:
	XE::uint64 Size() const;

	XE::uint64 Count() const;

public:
	Color GetPixel( XE::uint32 x, XE::uint32 y ) const;

	void SetPixel( XE::uint32 x, XE::uint32 y, const Color & val );

	FColor GetHDRPixel( XE::uint32 x, XE::uint32 y ) const;

	void SetHDRPixel( XE::uint32 x, XE::uint32 y, const FColor & val );

public:
	XE::basic_memory_view<XE::uint8> GetPixels() const;

	XE::basic_memory_view<XE::float32> GetHDRPixels() const;

public:
	Image Copy( XE::uint32 x, XE::uint32 y, XE::uint32 width, XE::uint32 height ) const;

public:
	void Roate( XE::float32 val );

	void Scaled( XE::float32 x, XE::float32 y );

private:
	bool _IsHDR;
	XE::int32 _Width;
	XE::int32 _Height;
	XE::int32 _Channels;
	union
	{
		Array< XE::uint8 > _Data;
		Array< XE::float32 > _HDRData;
	};
};

END_XE_NAMESPACE

#endif //__IMAGE_H__43F807F7_67DE_4C1F_BC4B_78BDA64E3A4E
