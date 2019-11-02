/*!
 * \file	Machine.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/08
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef MACHINE_H__58333465_3B43_47E0_9366_4B9A1AFDC354
#define MACHINE_H__58333465_3B43_47E0_9366_4B9A1AFDC354

#include "Type.h"

BEG_XE_NAMESPACE

class RegisterGroup
{

};

class Machine
{
public:
	Machine();

	~Machine();

public:
	void Exec( XE::basic_memory_view<XE::uint8> val );

private:
	Array<void( Machine:: * )( )> _Callbacks;
	XE::basic_memory_view<XE::uint8>::iterator _Cursor;
};

END_XE_NAMESPACE

#endif // MACHINE_H__58333465_3B43_47E0_9366_4B9A1AFDC354
