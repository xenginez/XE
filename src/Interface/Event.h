/*!
 * \file	Event.h
 *
 * \author	ZhengYuanQing
 * \date	2019/07/08
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef EVENT_H__1137B910_A3BE_4F6D_8873_46BF1A32A1D1
#define EVENT_H__1137B910_A3BE_4F6D_8873_46BF1A32A1D1

#include "Type.h"

BEG_XE_NAMESPACE

DECL_EVENT( KEY_UP, u8"���̰���̧��", XE::uint32 );
DECL_EVENT( KEY_DOWN, u8"���̰�������", XE::uint32 );
DECL_EVENT( MOUSE_UP, u8"��갴��̧��", XE::uint32 );
DECL_EVENT( MOUSE_DOWN, u8"��갴������", XE::uint32 );
DECL_EVENT( MOUSE_WHEEL, u8"�����ֹ���", XE::uint32 );

END_XE_NAMESPACE

#endif // EVENT_H__1137B910_A3BE_4F6D_8873_46BF1A32A1D1
