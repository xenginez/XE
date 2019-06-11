/*!
 * \file    TextureCube.h
 *
 * \author  ZhengYuanQing
 * \date    2019-06-04
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TEXTURECUBE_H__0553F2CC_7369_4D5C_886C_1CD0A7BD00B7
#define __TEXTURECUBE_H__0553F2CC_7369_4D5C_886C_1CD0A7BD00B7

#include "Texture2D.h"

BEG_XE_NAMESPACE

class RHI_API TextureCube : public Texture2D
{
	OBJECT(TextureCube, Texture2D)
	
public:
	TextureCube();
	
	~TextureCube() override;

public:
	XE::uint32 GetSize() const;

private:
	XE::uint32 _Size;
};

END_XE_NAMESPACE

#endif //__TEXTURECUBE_H__0553F2CC_7369_4D5C_886C_1CD0A7BD00B7
