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
	uint32 GetMipCount() const;
	
	uint32 GetWidth( uint32 mip = 1 ) const;
	
	uint32 GetHeight( uint32 mip = 1 ) const;

protected:
	uint32 _Width;
	uint32 _Height;
	uint32 _MipLevel;
};

END_XE_NAMESPACE

#endif //__TEXTURE2D_H__0CB6F65B_D076_41B5_8104_7482AED2BBDA
