/*!
 * \file    Texture3D.h
 *
 * \author  ZhengYuanQing
 * \date    2019-06-04
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TEXTURE3D_H__C602ADBC_008B_4ECE_8683_9216167CD259
#define __TEXTURE3D_H__C602ADBC_008B_4ECE_8683_9216167CD259

#include "Texture2D.h"

BEG_XE_NAMESPACE

class RHI_API Texture3D : public Texture2D
{
	OBJECT(Texture3D, Texture2D)
	
public:
	Texture3D();
	
	~Texture3D() override;

public:
	XE::uint32 GetDepth( XE::uint32 mip = 1) const;

private:
	XE::uint32 _Depth;
};

END_XE_NAMESPACE

#endif //__TEXTURE3D_H__C602ADBC_008B_4ECE_8683_9216167CD259
