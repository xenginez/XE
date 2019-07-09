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

	Image( XE::memory_view & val );

	Image( const std::filesystem::path & val );

	Image( XE::uint32 width, XE::uint32 height, TextureFormat format );

	Image( const Image& val );

	~Image();

public:
	bool Load( XE::memory_view val );

	bool Load( const std::filesystem::path& val );

	bool Load( XE::uint32 width, XE::uint32 height, TextureFormat format );

public:
	bool Save( XE::memory_view val );

	bool Save( const std::filesystem::path& val );

public:
	XE::uint32 GetWidth() const;

	XE::uint32 GetHeight() const;

	TextureFormat GetFormat() const;

public:
	XE::uint64 Size() const;

	XE::uint64 Count() const;

public:
	Color GetPixel( XE::uint64 index ) const;

	Color GetPixel( XE::uint32 x, XE::uint32 y ) const;

	void SetPixel( XE::uint64 index, const Color & val );

	void SetPixel( XE::uint32 x, XE::uint32 y, const Color & val );

public:
	XE::memory_view GetPixels() const;

public:
	Image Convert( TextureFormat format ) const;

	Image Copy( XE::uint32 x, XE::uint32 y, XE::uint32 width, XE::uint32 height ) const;

public:
	void Roate( XE::float32 val );

	void Scaled( XE::float32 x, XE::float32 y );

};

END_XE_NAMESPACE

#endif //__IMAGE_H__43F807F7_67DE_4C1F_BC4B_78BDA64E3A4E
