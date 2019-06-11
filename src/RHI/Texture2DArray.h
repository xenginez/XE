/*!
 * \file    Texture2DArray.h
 *
 * \author  ZhengYuanQing
 * \date    2019-06-04
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TEXTURE2DARRAY_H__BA0EAD30_29ED_49F2_AA55_F6C276F81ECF
#define __TEXTURE2DARRAY_H__BA0EAD30_29ED_49F2_AA55_F6C276F81ECF

#include "Texture2D.h"

BEG_XE_NAMESPACE

class RHI_API Texture2DArray : public Texture2D
{
	OBJECT(Texture2DArray, Texture2D)
	
public:
	Texture2DArray();
	
	~Texture2DArray() override;

public:
	XE::uint32 GetSize() const;

private:
	XE::uint32 _Size;
};

END_XE_NAMESPACE

#endif //__TEXTURE2DARRAY_H__BA0EAD30_29ED_49F2_AA55_F6C276F81ECF
