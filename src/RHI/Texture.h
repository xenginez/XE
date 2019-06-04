/*!
 * \file   Texture.h
 *
 * \author ZhengYuanQing
 * \date   2019/05/29
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TEXTURE_H__6DB7FD0A_1D06_48FC_9F35_B690DC44BD81
#define __TEXTURE_H__6DB7FD0A_1D06_48FC_9F35_B690DC44BD81

#include "Resource.h"

BEG_XE_NAMESPACE

class RHI_API Texture : public Resource
{
	OBJECT(Texture, Resource)
	
public:
	Texture();
	
	~Texture() override;

public:
	TextureHandle GetHandle() const;
	
	TextureFormat GetFormat() const;

protected:
	TextureFormat _Format;
	TextureHandle _Handle;
};

END_XE_NAMESPACE

#endif // __TEXTURE_H__6DB7FD0A_1D06_48FC_9F35_B690DC44BD81
