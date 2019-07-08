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
	VK_LBUTTON		0x01	1	Êó±êµÄ×ó¼ü
	VK_RBUTTON		0x02	2	Êó±êµÄÓÒ¼ü
	VK - CANCEL		0x03	3	Ctrl + Break( Í¨³£²»ÐèÒª´¦Àí )
	VK_MBUTTON		0x04	4	Êó±êµÄÖÐ¼ü£¨Èý°´¼üÊó±ê)
	VK_BACK			0x08	8	Backspace¼ü
	VK_TAB			0x09	9	Tab¼ü
	VK_CLEAR		0x0C	12	Clear¼ü£¨Num Lock¹Ø±ÕÊ±µÄÊý×Ö¼üÅÌ5£©
	VK_RETURN		0x0D	13	Enter¼ü
	VK_SHIFT		0x10	16	Shift¼ü
	VK_CONTROL		0x11	17	Ctrl¼ü
	VK_MENU			0x12	18	Alt¼ü
	VK_PAUSE		0x13	19	Pause¼ü
	VK_CAPITAL		0x14	20	Caps Lock¼ü
	VK_ESCAPE		0x1B	27	Ese¼ü
	VK_SPACE		0x20	32	Spacebar¼ü
	VK_PRIOR		0x21	33	Page Up¼ü
	VK_NEXT			0x22	34	Page Domw¼ü
	VK_END			0x23	35	End¼ü
	VK_HOME			0x24	36	Home¼ü
	VK_LEFT			0x25	37	LEFT ARROW ¼ü( ¡û )
	VK_UP			0x26	38	UP ARROW¼ü( ¡ü )
	VK_RIGHT		0x27	39	RIGHT ARROW¼ü( ¡ú )
	VK_DOWN			0x28	40	DOWN ARROW¼ü( ¡ý )
	VK_Select		0x29	41	Select¼ü
	VK_PRINT		0x2A	42	Print¼ü
	VK_EXECUTE		0x2B	43	EXECUTE¼ü
	VK_SNAPSHOT		0x2C	44	Print Screen¼ü£¨×¥ÆÁ£©
	VK_Insert		0x2D	45	Ins¼ü( Num Lock¹Ø±ÕÊ±µÄÊý×Ö¼üÅÌ0 )
	VK_Delete		0x2E	46	Del¼ü( Num Lock¹Ø±ÕÊ±µÄÊý×Ö¼üÅÌ. )
	VK_HELP			0x2F	47	Help¼ü
	VK_0			0x30	48	0¼ü
	VK_1			0x31	49	1¼ü
	VK_2			0x32	50	2¼ü
	VK_3			0x33	51	3¼ü
	VK_4			0x34	52	4¼ü
	VK_5			0x35	53	5¼ü
	VK_6			0x36	54	6¼ü
	VK_7			0x37	55	7¼ü
	VK_8			0x38	56	8¼ü
	VK_9			0x39	57	9¼ü
	VK_A			0x41	65	A¼ü
	VK_B			0x42	66	B¼ü
	VK_C			0x43	67	C¼ü
	VK_D			0x44	68	D¼ü
	VK_E			0x45	69	E¼ü
	VK_F			0x46	70	F¼ü
	VK_G			0x47	71	G¼ü
	VK_H			0x48	72	H¼ü
	VK_I			0x49	73	I¼ü
	VK_J			0x4A	74	J¼ü
	VK_K			0x4B	75	K¼ü
	VK_L			0x4C	76	L¼ü
	VK_M			0x4D	77	M¼ü
	VK_N			0x4E	78	N¼ü
	VK_O			0x4F	79	O¼ü
	VK_P			0x50	80	P¼ü
	VK_Q			0x51	81	Q¼ü
	VK_R			0x52	82	R¼ü
	VK_S			0x53	83	S¼ü
	VK_T			0x54	84	T¼ü
	VK_U			0x55	85	U¼ü
	VK_V			0x56	86	V¼ü
	VK_W			0x57	87	W¼ü
	VK_X			0x58	88	X¼ü
	VK_Y			0x59	89	Y¼ü
	VK_Z			0x5A	90	Z¼ü
	VK_NUMPAD0		0x60	96	Êý×Ö¼ü0¼ü
	VK_NUMPAD1		0x61	97	Êý×Ö¼ü1¼ü
	VK_NUMPAD2		0x62	98	Êý×Ö¼ü2¼ü
	VK_NUMPAD3		0x62	99	Êý×Ö¼ü3¼ü
	VK_NUMPAD4		0x64	100	Êý×Ö¼ü4¼ü
	VK_NUMPAD5		0x65	101	Êý×Ö¼ü5¼ü
	VK_NUMPAD6		0x66	102	Êý×Ö¼ü6¼ü
	VK_NUMPAD7		0x67	103	Êý×Ö¼ü7¼ü
	VK_NUMPAD8		0x68	104	Êý×Ö¼ü8¼ü
	VK_NUMPAD9		0x69	105	Êý×Ö¼ü9¼ü
	VK_MULTIPLY		0x6A	106	Êý×Ö¼üÅÌÉÏµÄ * ¼ü
	VK_ADD			0x6B	107	Êý×Ö¼üÅÌÉÏµÄ + ¼ü
	VK_SEPARATOR	0x6C	108	Separator¼ü
	VK_SUBTRACT		0x6D	109	Êý×Ö¼üÅÌÉÏµÄ - ¼ü
	VK_DECIMAL		0x6E	110	Êý×Ö¼üÅÌÉÏµÄ.¼ü
	VK_DIVIDE		0x6F	111	Êý×Ö¼üÅÌÉÏµÄ / ¼ü
	VK_F1			0x70	112	F1¼ü
	VK_F2			0x71	113	F2¼ü
	VK_F3			0x72	114	F3¼ü
	VK_F4			0x73	115	F4¼ü
	VK_F5			0x74	116	F5¼ü
	VK_F6			0x75	117	F6¼ü
	VK_F7			0x76	118	F7¼ü
	VK_F8			0x77	119	F8¼ü
	VK_F9			0x78	120	F9¼ü
	VK_F10			0x79	121	F10¼ü
	VK_F11			0x7A	122	F11¼ü
	VK_F12			0x7B	123	F12¼ü
	VK_NUMLOCK		0x90	144	Num Lock ¼ü
	VK_SCROLL		0x91	145	Scroll Lock¼ü
	VK_LWIN			0x91		×ówin¼ü
	VK_RWIN			0x92		ÓÒwin¼ü
	VK_APPS			0x93		ÓÒCtrl×ó±ß¼ü£¬µã»÷Ïàµ±ÓÚµã»÷Êó±êÓÒ¼ü£¬»áµ¯³ö¿ì½Ý²Ëµ¥
					0x186		; ¼ü
					0x187		= ¼ü
					0x188		, ¼ü
					0x189		- ¼ü
					0x190		. ¼ü
					0x191		/ ¼ü
					0x192		` ¼ü
					0x219		[ ¼ü
					0x220		  ¼ü
					0x221		] ¼ü
					0x222		' ¼ü
	*/
};

#endif


#endif // KEYCODE_H__030B6724_2500_4498_925F_C3353688D5C9
