/*!
 * \file   Type.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TYPE_H__FF3D8A9E_5172_4F88_873F_0CAF1E5289F6
#define __TYPE_H__FF3D8A9E_5172_4F88_873F_0CAF1E5289F6

#include "Global.h"

BEG_XE_NAMESPACE

DECL_PTR( Event );
DECL_PTR( Object );
DECL_PTR( Buffer );
DECL_PTR( Message );

enum class AssetStatus
{
	UNDEFINED,
	LOADING,
	READY,
	FAILED,
};
DECL_META_ENUM( XE_API, AssetStatus );

enum class Language
{
	ENGLISH,
	CHINESESIMPLIFIED,
	CHINESETRADITIONAL,
	AFRIKAANS,
	ARABIC,
	BASQUE,
	BELARUSIAN,
	BULGARIAN,
	CATALAN,
	CZECH,
	DANISH,
	DUTCH,
	ESTONIAN,
	FAROESE,
	FINNISH,
	FRENCH,
	GERMAN,
	GREEK,
	HEBREW,
	ICELANDIC,
	INDONESIAN,
	ITALIAN,
	JAPANESE,
	KOREAN,
	LATVIAN,
	LITHUANIAN,
	NORWEGIAN,
	POLISH,
	PORTUGUESE,
	ROMANIAN,
	RUSSIAN,
	SERBOCROATIAN,
	SLOVAK,
	SLOVENIAN,
	SPANISH,
	SWEDISH,
	THAI,
	TURKISH,
	UKRAINIAN,
	VIETNAMESE,
	HUNGARIAN,
	UNKNOWN,
};
DECL_META_ENUM( XE_API, Language );

enum class WindowEvent
{
	CREATE,						// application creates a window
	DESTROY,					// a window is destroyed.
	MOVE,						// move a window
	SIZE,						// change the size of a window
	ACTIVATE,					// a window is activated or lost;
	SETFOCUS,					// once you're in focus
	KILLFOCUS,					// losing focus
	ENABLE,						// changing the state of the enable
	PAINT,						// ask a window to redraw yourself
	CLOSE,						// send a signal when a window or application is to close
	QUERYENDSESSION,			// when the user chooses to call the Exit Windows function by the end dialog box or the program itself
	QUIT,						// used to end a program run or when a program calls the postquitmessage function
	SHOWWINDOW,					// when a hidden or display window is sent this message to this window
	ACTIVATEAPP,				// send this message to the application which window is active and which is inactive;
	SETCURSOR,					// if the mouse causes the cursor to move in a window and the mouse input is not captured, a message is sent to a window
	MOUSEACTIVATE,				// this message is sent to the current window when the cursor is in an inactive window and the user is pressing a button on the mouse
	GETMINMAXINFO,				// this message is sent to the window when it is about to change the size or position;
	NEXTDLGCTL,					// send this message to a dialog program to change the focus position
	COMPACTING,					// show memory is already low
	WINDOWPOSCHANGING,			// send this message to that window when the size and position will be changed to call the setwindowpos function or other window management function
	WINDOWPOSCHANGED,			// to call the setwindowpos function or other window management function when the size and position of the window have been changed
	DISPLAYCHANGE,				// send this message to all windows when the resolution of the monitor changes
	GETICON,					// this message is sent to a window to return a handle to a large or small icon connected to a window;
	SETICON,					// the program sends this message to associate a new large or small icon with a window;
	KEYDOWN,					// press a key
	KEYUP,						// release a key
	CHAR,						// press a key and have sent a WM - KEYDOWN, WM - KEYUP message
	DEADCHAR,					// send this message to a focus - owning window when translating a WM - KEYUP message with the translatemessage function
	SYSKEYDOWN,					// submit this message to the focus - owning window when the user holds down the ALT key and presses the other keys at the same time;
	SYSKEYUP,					// submit this message to the focus - owning window when the user releases a key while the ALT key is also pressed
	SYSCHAR,					// when the WM - SYSKEYDOWN message is translated by the TRANSLATEMESSAGE function, this message is submitted to the window with focus
	SYSDEADCHAR,				// send this message to the focus - owning window when the WM - SYSKEYDOWN message is translated by the TRANSLATEMESSAGE function
	MOUSEMOVE,					// move the mouse
	LBUTTONDOWN,				// press the left mouse button
	LBUTTONUP,					// release the left mouse button
	LBUTTONDBLCLK,				// double - click the left mouse button
	RBUTTONDOWN,				// press the right mouse button
	RBUTTONUP,					// release the right mouse button
	RBUTTONDBLCLK,				// double - click the right mouse button
	MBUTTONDOWN,				// press the middle mouse button
	MBUTTONUP,					// release the middle mouse button
	MBUTTONDBLCLK,				// double - click the middle mouse button
	MOUSEWHEEL,					// send this message a control that currently has focus when the mouse wheel turns
	SIZING,						// when the user is adjusting the window size to send this message to the window, the message application can monitor the window size and location can also modify them
	CAPTURECHANGED,				// send this message to the window when it loses the captured mouse;
	MOVING,						// when the user sends this message when the window is moved, the message application can monitor the size and location of the window or modify them;
	POWERBROADCAST,				// this message is sent to the application to notify it about power management events;
	DEVICECHANGE,				// send this message to the application or device driver when the hardware configuration of the device changes
};
DECL_META_ENUM( XE_API, WindowEvent );

enum class LoggerLevel
{
	Error,
	Warning,
	Message,
};

END_XE_NAMESPACE

#endif // __TYPE_H__FF3D8A9E_5172_4F88_873F_0CAF1E5289F6
