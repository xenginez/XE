/*!
 * \file    Texture2D.h
 *
 * \author  ZhengYuanQing
 * \date    2019-06-04
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TEXTURE2D_H__0CB6F65B_D076_41B5_8104_7482AED2BBDA
#define __TEXTURE2D_H__0CB6F65B_D076_41B5_8104_7482AED2BBDA

#include "Texture.h"

BEG_XE_NAMESPACE

class RHI_API Texture2D : public Texture
{
	OBJECT(Texture2D, Texture)
	
public:
	Texture2D();
	
	~Texture2D() override;

public:
	XE::uint32 GetMipCount() const;
	
	XE::uint32 GetWidth( XE::uint32 mip = 1 ) const;
	
	XE::uint32 GetHeight( XE::uint32 mip = 1 ) const;

protected:
	XE::uint32 _Width;
	XE::uint32 _Height;
	XE::uint32 _MipLevel;
};

END_XE_NAMESPACE

#endif //__TEXTURE2D_H__0CB6F65B_D076_41B5_8104_7482AED2BBDA
