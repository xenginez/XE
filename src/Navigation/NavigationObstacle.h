/*!
 * \file	NavigationObstacle.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/30
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef NAVIGATIONOBSTACLE_H__CD527FA1_B3A9_45B0_98BE_05C1796CF15E
#define NAVIGATIONOBSTACLE_H__CD527FA1_B3A9_45B0_98BE_05C1796CF15E

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API NavigationObstacle : public XE::Object
{
	OBJECT( NavigationObstacle, Object )

public:
	NavigationObstacle();

	~NavigationObstacle() override;

public:

};

END_XE_NAMESPACE

#endif // NAVIGATIONOBSTACLE_H__CD527FA1_B3A9_45B0_98BE_05C1796CF15E
