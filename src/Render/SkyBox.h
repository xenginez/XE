/*!
 * \file	SkyBox.h
 *
 * \author	ZhengYuanQing
 * \date	2019/10/13
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef SKYBOX_H__A566AB4F_A4DB_49B8_956B_C2B76ED7BBB4
#define SKYBOX_H__A566AB4F_A4DB_49B8_956B_C2B76ED7BBB4

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API SkyBox : public XE::Renderable
{
	OBJECT( SkyBox, Renderable )

public:
	SkyBox();

	~SkyBox();

public:

};

END_XE_NAMESPACE

#endif // SKYBOX_H__A566AB4F_A4DB_49B8_956B_C2B76ED7BBB4
