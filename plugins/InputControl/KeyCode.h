/*!
 * \file	KeyCode.h
 *
 * \author	ZhengYuanQing
 * \date	2019/07/08
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef KEYCODE_H__030B6724_2500_4498_925F_C3353688D5C9
#define KEYCODE_H__030B6724_2500_4498_925F_C3353688D5C9

#include "Type.h"

#if PLATFORM_OS == OS_PS4
#elif PLATFORM_OS == OS_MAC
#elif PLATFORM_OS == OS_IOS
#elif PLATFORM_OS == OS_LINUX
#elif PLATFORM_OS == OS_ANDROID
#elif PLATFORM_OS == OS_XBOXONE
#elif PLATFORM_OS == OS_WINDOWS
#include <windows.h>
#include <winuser.h>
static XE::KeyCode TranslateKey[1] =
{
	XE::KeyCode::None
	/*
	VK_LBUTTON		0x01	1	�������
	VK_RBUTTON		0x02	2	�����Ҽ�
	VK - CANCEL		0x03	3	Ctrl + Break( ͨ������Ҫ���� )
	VK_MBUTTON		0x04	4	�����м������������)
	VK_BACK			0x08	8	Backspace��
	VK_TAB			0x09	9	Tab��
	VK_CLEAR		0x0C	12	Clear����Num Lock�ر�ʱ�����ּ���5��
	VK_RETURN		0x0D	13	Enter��
	VK_SHIFT		0x10	16	Shift��
	VK_CONTROL		0x11	17	Ctrl��
	VK_MENU			0x12	18	Alt��
	VK_PAUSE		0x13	19	Pause��
	VK_CAPITAL		0x14	20	Caps Lock��
	VK_ESCAPE		0x1B	27	Ese��
	VK_SPACE		0x20	32	Spacebar��
	VK_PRIOR		0x21	33	Page Up��
	VK_NEXT			0x22	34	Page Domw��
	VK_END			0x23	35	End��
	VK_HOME			0x24	36	Home��
	VK_LEFT			0x25	37	LEFT ARROW ��( �� )
	VK_UP			0x26	38	UP ARROW��( �� )
	VK_RIGHT		0x27	39	RIGHT ARROW��( �� )
	VK_DOWN			0x28	40	DOWN ARROW��( �� )
	VK_Select		0x29	41	Select��
	VK_PRINT		0x2A	42	Print��
	VK_EXECUTE		0x2B	43	EXECUTE��
	VK_SNAPSHOT		0x2C	44	Print Screen����ץ����
	VK_Insert		0x2D	45	Ins��( Num Lock�ر�ʱ�����ּ���0 )
	VK_Delete		0x2E	46	Del��( Num Lock�ر�ʱ�����ּ���. )
	VK_HELP			0x2F	47	Help��
	VK_0			0x30	48	0��
	VK_1			0x31	49	1��
	VK_2			0x32	50	2��
	VK_3			0x33	51	3��
	VK_4			0x34	52	4��
	VK_5			0x35	53	5��
	VK_6			0x36	54	6��
	VK_7			0x37	55	7��
	VK_8			0x38	56	8��
	VK_9			0x39	57	9��
	VK_A			0x41	65	A��
	VK_B			0x42	66	B��
	VK_C			0x43	67	C��
	VK_D			0x44	68	D��
	VK_E			0x45	69	E��
	VK_F			0x46	70	F��
	VK_G			0x47	71	G��
	VK_H			0x48	72	H��
	VK_I			0x49	73	I��
	VK_J			0x4A	74	J��
	VK_K			0x4B	75	K��
	VK_L			0x4C	76	L��
	VK_M			0x4D	77	M��
	VK_N			0x4E	78	N��
	VK_O			0x4F	79	O��
	VK_P			0x50	80	P��
	VK_Q			0x51	81	Q��
	VK_R			0x52	82	R��
	VK_S			0x53	83	S��
	VK_T			0x54	84	T��
	VK_U			0x55	85	U��
	VK_V			0x56	86	V��
	VK_W			0x57	87	W��
	VK_X			0x58	88	X��
	VK_Y			0x59	89	Y��
	VK_Z			0x5A	90	Z��
	VK_NUMPAD0		0x60	96	���ּ�0��
	VK_NUMPAD1		0x61	97	���ּ�1��
	VK_NUMPAD2		0x62	98	���ּ�2��
	VK_NUMPAD3		0x62	99	���ּ�3��
	VK_NUMPAD4		0x64	100	���ּ�4��
	VK_NUMPAD5		0x65	101	���ּ�5��
	VK_NUMPAD6		0x66	102	���ּ�6��
	VK_NUMPAD7		0x67	103	���ּ�7��
	VK_NUMPAD8		0x68	104	���ּ�8��
	VK_NUMPAD9		0x69	105	���ּ�9��
	VK_MULTIPLY		0x6A	106	���ּ����ϵ� * ��
	VK_ADD			0x6B	107	���ּ����ϵ� + ��
	VK_SEPARATOR	0x6C	108	Separator��
	VK_SUBTRACT		0x6D	109	���ּ����ϵ� - ��
	VK_DECIMAL		0x6E	110	���ּ����ϵ�.��
	VK_DIVIDE		0x6F	111	���ּ����ϵ� / ��
	VK_F1			0x70	112	F1��
	VK_F2			0x71	113	F2��
	VK_F3			0x72	114	F3��
	VK_F4			0x73	115	F4��
	VK_F5			0x74	116	F5��
	VK_F6			0x75	117	F6��
	VK_F7			0x76	118	F7��
	VK_F8			0x77	119	F8��
	VK_F9			0x78	120	F9��
	VK_F10			0x79	121	F10��
	VK_F11			0x7A	122	F11��
	VK_F12			0x7B	123	F12��
	VK_NUMLOCK		0x90	144	Num Lock ��
	VK_SCROLL		0x91	145	Scroll Lock��
	VK_LWIN			0x91		��win��
	VK_RWIN			0x92		��win��
	VK_APPS			0x93		��Ctrl��߼�������൱�ڵ������Ҽ����ᵯ����ݲ˵�
					0x186		; ��
					0x187		= ��
					0x188		, ��
					0x189		- ��
					0x190		. ��
					0x191		/ ��
					0x192		` ��
					0x219		[ ��
					0x220		  ��
					0x221		] ��
					0x222		' ��
	*/
};

#endif


#endif // KEYCODE_H__030B6724_2500_4498_925F_C3353688D5C9
