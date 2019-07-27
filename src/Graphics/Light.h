/*!
 * \file	Light.h
 *
 * \author	ZhengYuanQing
 * \date	2019/07/27
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef LIGHT_H__DEEF3151_DC77_48A1_99DC_F515876C7CCF
#define LIGHT_H__DEEF3151_DC77_48A1_99DC_F515876C7CCF

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API Light : public XE::Object
{
	OBJECT( Light, Object )

public:
	Light();

	~Light();

};

END_XE_NAMESPACE

#endif // LIGHT_H__DEEF3151_DC77_48A1_99DC_F515876C7CCF
