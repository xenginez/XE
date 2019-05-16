/*!
 * \file    RenderWindow.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-16
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __RENDERWINDOW_H__30A203B0_90D8_42E1_A032_520EC8A73A3D
#define __RENDERWINDOW_H__30A203B0_90D8_42E1_A032_520EC8A73A3D

#include "Type.h"

BEG_XE_NAMESPACE

class RHI_API RenderWindow : public XE::Object
{
	OBJECT(RenderWindow, Object)
	
public:
	RenderWindow();
	
	~RenderWindow() override;

public:

};

END_XE_NAMESAPCE

#endif //__RENDERWINDOW_H__30A203B0_90D8_42E1_A032_520EC8A73A3D
