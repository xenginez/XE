/*!
 * \file   Type.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TYPE_H__67D32AA5_C812_4032_BD6F_E5A4FA0C221D
#define __TYPE_H__67D32AA5_C812_4032_BD6F_E5A4FA0C221D

#include "Global.h"

BEG_XE_NAMESPACE

DECL_PTR( IService );
DECL_PTR( ProfilerFrame );
DECL_PTR( IEventService );
DECL_PTR( ITimerService );
DECL_PTR( IAudioService );
DECL_PTR( IWorldService );
DECL_PTR( IInputService );
DECL_PTR( IPluginService );
DECL_PTR( IAssetsService );
DECL_PTR( IConfigService );
DECL_PTR( IRenderService );
DECL_PTR( IThreadService );
DECL_PTR( IPhysicsService );
DECL_PTR( IProfilerService );
DECL_PTR( INavigationService );
DECL_PTR( ILocalizationService );
class IFramework; typedef IFramework * IFrameworkPtr;

DECL_ALLOCATOR_POLL( Event );
DECL_ALLOCATOR_POLL( Logger );
DECL_ALLOCATOR_POLL( ProfilerFrame );

enum class KeyCode
{
	None,
	Backspace,
	Delete,
	Tab,
	Clear,
	Return,
	Pause,
	Escape,
	Space,
	Keypad0,
	Keypad1,
	Keypad2,
	Keypad3,
	Keypad4,
	Keypad5,
	Keypad6,
	Keypad7,
	Keypad8,
	Keypad9,
	KeypadPeriod,
	KeypadDivide,
	KeypadMultiply,
	KeypadMinus,
	KeypadPlus,
	KeypadEnter,
	KeypadEquals,
	UpArrow,
	DownArrow,
	RightArrow,
	LeftArrow,
	Insert,
	Home,
	End,
	PageUp,
	PageDown,
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,
	F13,
	F14,
	F15,
	Alpha0,
	Alpha1,
	Alpha2,
	Alpha3,
	Alpha4,
	Alpha5,
	Alpha6,
	Alpha7,
	Alpha8,
	Alpha9,
	Exclaim,
	DoubleQuote,
	Hash,
	Dollar,
	Ampersand,
	Quote,
	LeftParen,
	RightParen,
	Asterisk,
	Plus,
	Comma,
	Minus,
	Period,
	Slash,
	Colon,
	Semicolon,
	Less,
	Equals,
	Greater,
	Question,
	At,
	LeftBracket,
	Backslash,
	RightBracket,
	Caret,
	Underscore,
	BackQuote,
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	Numlock,
	CapsLock,
	ScrollLock,
	RightShift,
	LeftShift,
	RightControl,
	LeftControl,
	RightAlt,
	LeftAlt,
	LeftCommand,
	LeftApple,
	LeftWindows,
	RightCommand,
	RightApple,
	RightWindows,
	AltGr,
	Help,
	Print,
	SysReq,
	Break,
	Menu,
	MouseLeft,
	MouseMiddle,
	MouseRight,
	MouseWheel,
	MouseX,
	MouseY,
	MouseButton0,
	MouseButton1,
	MouseButton2,
	MouseButton3,
	MouseButton4,
	MouseButton5,
	MouseButton6,
	JoystickButton0,
	JoystickButton1,
	JoystickButton2,
	JoystickButton3,
	JoystickButton4,
	JoystickButton5,
	JoystickButton6,
	JoystickButton7,
	JoystickButton8,
	JoystickButton9,
	JoystickButton10,
	JoystickButton11,
	JoystickButton12,
	JoystickButton13,
	JoystickButton14,
	JoystickButton15,
	JoystickButton16,
	JoystickButton17,
	JoystickButton18,
	JoystickButton19,
	Joystick1Button0,
	Joystick1Button1,
	Joystick1Button2,
	Joystick1Button3,
	Joystick1Button4,
	Joystick1Button5,
	Joystick1Button6,
	Joystick1Button7,
	Joystick1Button8,
	Joystick1Button9,
	Joystick1Button10,
	Joystick1Button11,
	Joystick1Button12,
	Joystick1Button13,
	Joystick1Button14,
	Joystick1Button15,
	Joystick1Button16,
	Joystick1Button17,
	Joystick1Button18,
	Joystick1Button19,
	Joystick2Button0,
	Joystick2Button1,
	Joystick2Button2,
	Joystick2Button3,
	Joystick2Button4,
	Joystick2Button5,
	Joystick2Button6,
	Joystick2Button7,
	Joystick2Button8,
	Joystick2Button9,
	Joystick2Button10,
	Joystick2Button11,
	Joystick2Button12,
	Joystick2Button13,
	Joystick2Button14,
	Joystick2Button15,
	Joystick2Button16,
	Joystick2Button17,
	Joystick2Button18,
	Joystick2Button19,
	Joystick3Button0,
	Joystick3Button1,
	Joystick3Button2,
	Joystick3Button3,
	Joystick3Button4,
	Joystick3Button5,
	Joystick3Button6,
	Joystick3Button7,
	Joystick3Button8,
	Joystick3Button9,
	Joystick3Button10,
	Joystick3Button11,
	Joystick3Button12,
	Joystick3Button13,
	Joystick3Button14,
	Joystick3Button15,
	Joystick3Button16,
	Joystick3Button17,
	Joystick3Button18,
	Joystick3Button19,
	Joystick4Button0,
	Joystick4Button1,
	Joystick4Button2,
	Joystick4Button3,
	Joystick4Button4,
	Joystick4Button5,
	Joystick4Button6,
	Joystick4Button7,
	Joystick4Button8,
	Joystick4Button9,
	Joystick4Button10,
	Joystick4Button11,
	Joystick4Button12,
	Joystick4Button13,
	Joystick4Button14,
	Joystick4Button15,
	Joystick4Button16,
	Joystick4Button17,
	Joystick4Button18,
	Joystick4Button19,
	Joystick5Button0,
	Joystick5Button1,
	Joystick5Button2,
	Joystick5Button3,
	Joystick5Button4,
	Joystick5Button5,
	Joystick5Button6,
	Joystick5Button7,
	Joystick5Button8,
	Joystick5Button9,
	Joystick5Button10,
	Joystick5Button11,
	Joystick5Button12,
	Joystick5Button13,
	Joystick5Button14,
	Joystick5Button15,
	Joystick5Button16,
	Joystick5Button17,
	Joystick5Button18,
	Joystick5Button19,
	Joystick6Button0,
	Joystick6Button1,
	Joystick6Button2,
	Joystick6Button3,
	Joystick6Button4,
	Joystick6Button5,
	Joystick6Button6,
	Joystick6Button7,
	Joystick6Button8,
	Joystick6Button9,
	Joystick6Button10,
	Joystick6Button11,
	Joystick6Button12,
	Joystick6Button13,
	Joystick6Button14,
	Joystick6Button15,
	Joystick6Button16,
	Joystick6Button17,
	Joystick6Button18,
	Joystick6Button19,
	Joystick7Button0,
	Joystick7Button1,
	Joystick7Button2,
	Joystick7Button3,
	Joystick7Button4,
	Joystick7Button5,
	Joystick7Button6,
	Joystick7Button7,
	Joystick7Button8,
	Joystick7Button9,
	Joystick7Button10,
	Joystick7Button11,
	Joystick7Button12,
	Joystick7Button13,
	Joystick7Button14,
	Joystick7Button15,
	Joystick7Button16,
	Joystick7Button17,
	Joystick7Button18,
	Joystick7Button19,
	Joystick8Button0,
	Joystick8Button1,
	Joystick8Button2,
	Joystick8Button3,
	Joystick8Button4,
	Joystick8Button5,
	Joystick8Button6,
	Joystick8Button7,
	Joystick8Button8,
	Joystick8Button9,
	Joystick8Button10,
	Joystick8Button11,
	Joystick8Button12,
	Joystick8Button13,
	Joystick8Button14,
	Joystick8Button15,
	Joystick8Button16,
	Joystick8Button17,
	Joystick8Button18,
	Joystick8Button19,
	JoystickAxis0,
	JoystickAxis1,
	JoystickAxis2,
	JoystickAxis3,
	JoystickAxis4,
	JoystickAxis5,
	JoystickAxis6,
	JoystickAxis7,
	JoystickAxis8,
	JoystickAxis9,
	JoystickAxis10,
	JoystickAxis11,
	JoystickAxis12,
	JoystickAxis13,
	JoystickAxis14,
	JoystickAxis15,
	JoystickAxis16,
	JoystickAxis17,
	JoystickAxis18,
	JoystickAxis19,
	Joystick1Axis0,
	Joystick1Axis1,
	Joystick1Axis2,
	Joystick1Axis3,
	Joystick1Axis4,
	Joystick1Axis5,
	Joystick1Axis6,
	Joystick1Axis7,
	Joystick1Axis8,
	Joystick1Axis9,
	Joystick1Axis10,
	Joystick1Axis11,
	Joystick1Axis12,
	Joystick1Axis13,
	Joystick1Axis14,
	Joystick1Axis15,
	Joystick1Axis16,
	Joystick1Axis17,
	Joystick1Axis18,
	Joystick1Axis19,
	Joystick2Axis0,
	Joystick2Axis1,
	Joystick2Axis2,
	Joystick2Axis3,
	Joystick2Axis4,
	Joystick2Axis5,
	Joystick2Axis6,
	Joystick2Axis7,
	Joystick2Axis8,
	Joystick2Axis9,
	Joystick2Axis10,
	Joystick2Axis11,
	Joystick2Axis12,
	Joystick2Axis13,
	Joystick2Axis14,
	Joystick2Axis15,
	Joystick2Axis16,
	Joystick2Axis17,
	Joystick2Axis18,
	Joystick2Axis19,
	Joystick3Axis0,
	Joystick3Axis1,
	Joystick3Axis2,
	Joystick3Axis3,
	Joystick3Axis4,
	Joystick3Axis5,
	Joystick3Axis6,
	Joystick3Axis7,
	Joystick3Axis8,
	Joystick3Axis9,
	Joystick3Axis10,
	Joystick3Axis11,
	Joystick3Axis12,
	Joystick3Axis13,
	Joystick3Axis14,
	Joystick3Axis15,
	Joystick3Axis16,
	Joystick3Axis17,
	Joystick3Axis18,
	Joystick3Axis19,
	Joystick4Axis0,
	Joystick4Axis1,
	Joystick4Axis2,
	Joystick4Axis3,
	Joystick4Axis4,
	Joystick4Axis5,
	Joystick4Axis6,
	Joystick4Axis7,
	Joystick4Axis8,
	Joystick4Axis9,
	Joystick4Axis10,
	Joystick4Axis11,
	Joystick4Axis12,
	Joystick4Axis13,
	Joystick4Axis14,
	Joystick4Axis15,
	Joystick4Axis16,
	Joystick4Axis17,
	Joystick4Axis18,
	Joystick4Axis19,
	Joystick5Axis0,
	Joystick5Axis1,
	Joystick5Axis2,
	Joystick5Axis3,
	Joystick5Axis4,
	Joystick5Axis5,
	Joystick5Axis6,
	Joystick5Axis7,
	Joystick5Axis8,
	Joystick5Axis9,
	Joystick5Axis10,
	Joystick5Axis11,
	Joystick5Axis12,
	Joystick5Axis13,
	Joystick5Axis14,
	Joystick5Axis15,
	Joystick5Axis16,
	Joystick5Axis17,
	Joystick5Axis18,
	Joystick5Axis19,
	Joystick6Axis0,
	Joystick6Axis1,
	Joystick6Axis2,
	Joystick6Axis3,
	Joystick6Axis4,
	Joystick6Axis5,
	Joystick6Axis6,
	Joystick6Axis7,
	Joystick6Axis8,
	Joystick6Axis9,
	Joystick6Axis10,
	Joystick6Axis11,
	Joystick6Axis12,
	Joystick6Axis13,
	Joystick6Axis14,
	Joystick6Axis15,
	Joystick6Axis16,
	Joystick6Axis17,
	Joystick6Axis18,
	Joystick6Axis19,
	Joystick7Axis0,
	Joystick7Axis1,
	Joystick7Axis2,
	Joystick7Axis3,
	Joystick7Axis4,
	Joystick7Axis5,
	Joystick7Axis6,
	Joystick7Axis7,
	Joystick7Axis8,
	Joystick7Axis9,
	Joystick7Axis10,
	Joystick7Axis11,
	Joystick7Axis12,
	Joystick7Axis13,
	Joystick7Axis14,
	Joystick7Axis15,
	Joystick7Axis16,
	Joystick7Axis17,
	Joystick7Axis18,
	Joystick7Axis19,
	Joystick8Axis0,
	Joystick8Axis1,
	Joystick8Axis2,
	Joystick8Axis3,
	Joystick8Axis4,
	Joystick8Axis5,
	Joystick8Axis6,
	Joystick8Axis7,
	Joystick8Axis8,
	Joystick8Axis9,
	Joystick8Axis10,
	Joystick8Axis11,
	Joystick8Axis12,
	Joystick8Axis13,
	Joystick8Axis14,
	Joystick8Axis15,
	Joystick8Axis16,
	Joystick8Axis17,
	Joystick8Axis18,
	Joystick8Axis19,
	JoystickPov0,
	JoystickPov1,
	JoystickPov2,
	JoystickPov3,
	JoystickPov4,
	JoystickPov5,
	JoystickPov6,
	JoystickPov7,
	JoystickPov8,
	JoystickPov9,
	JoystickPov10,
	JoystickPov11,
	JoystickPov12,
	JoystickPov13,
	JoystickPov14,
	JoystickPov15,
	JoystickPov16,
	JoystickPov17,
	JoystickPov18,
	JoystickPov19,
	Joystick1Pov0,
	Joystick1Pov1,
	Joystick1Pov2,
	Joystick1Pov3,
	Joystick1Pov4,
	Joystick1Pov5,
	Joystick1Pov6,
	Joystick1Pov7,
	Joystick1Pov8,
	Joystick1Pov9,
	Joystick1Pov10,
	Joystick1Pov11,
	Joystick1Pov12,
	Joystick1Pov13,
	Joystick1Pov14,
	Joystick1Pov15,
	Joystick1Pov16,
	Joystick1Pov17,
	Joystick1Pov18,
	Joystick1Pov19,
	Joystick2Pov0,
	Joystick2Pov1,
	Joystick2Pov2,
	Joystick2Pov3,
	Joystick2Pov4,
	Joystick2Pov5,
	Joystick2Pov6,
	Joystick2Pov7,
	Joystick2Pov8,
	Joystick2Pov9,
	Joystick2Pov10,
	Joystick2Pov11,
	Joystick2Pov12,
	Joystick2Pov13,
	Joystick2Pov14,
	Joystick2Pov15,
	Joystick2Pov16,
	Joystick2Pov17,
	Joystick2Pov18,
	Joystick2Pov19,
	Joystick3Pov0,
	Joystick3Pov1,
	Joystick3Pov2,
	Joystick3Pov3,
	Joystick3Pov4,
	Joystick3Pov5,
	Joystick3Pov6,
	Joystick3Pov7,
	Joystick3Pov8,
	Joystick3Pov9,
	Joystick3Pov10,
	Joystick3Pov11,
	Joystick3Pov12,
	Joystick3Pov13,
	Joystick3Pov14,
	Joystick3Pov15,
	Joystick3Pov16,
	Joystick3Pov17,
	Joystick3Pov18,
	Joystick3Pov19,
	Joystick4Pov0,
	Joystick4Pov1,
	Joystick4Pov2,
	Joystick4Pov3,
	Joystick4Pov4,
	Joystick4Pov5,
	Joystick4Pov6,
	Joystick4Pov7,
	Joystick4Pov8,
	Joystick4Pov9,
	Joystick4Pov10,
	Joystick4Pov11,
	Joystick4Pov12,
	Joystick4Pov13,
	Joystick4Pov14,
	Joystick4Pov15,
	Joystick4Pov16,
	Joystick4Pov17,
	Joystick4Pov18,
	Joystick4Pov19,
	Joystick5Pov0,
	Joystick5Pov1,
	Joystick5Pov2,
	Joystick5Pov3,
	Joystick5Pov4,
	Joystick5Pov5,
	Joystick5Pov6,
	Joystick5Pov7,
	Joystick5Pov8,
	Joystick5Pov9,
	Joystick5Pov10,
	Joystick5Pov11,
	Joystick5Pov12,
	Joystick5Pov13,
	Joystick5Pov14,
	Joystick5Pov15,
	Joystick5Pov16,
	Joystick5Pov17,
	Joystick5Pov18,
	Joystick5Pov19,
	Joystick6Pov0,
	Joystick6Pov1,
	Joystick6Pov2,
	Joystick6Pov3,
	Joystick6Pov4,
	Joystick6Pov5,
	Joystick6Pov6,
	Joystick6Pov7,
	Joystick6Pov8,
	Joystick6Pov9,
	Joystick6Pov10,
	Joystick6Pov11,
	Joystick6Pov12,
	Joystick6Pov13,
	Joystick6Pov14,
	Joystick6Pov15,
	Joystick6Pov16,
	Joystick6Pov17,
	Joystick6Pov18,
	Joystick6Pov19,
	Joystick7Pov0,
	Joystick7Pov1,
	Joystick7Pov2,
	Joystick7Pov3,
	Joystick7Pov4,
	Joystick7Pov5,
	Joystick7Pov6,
	Joystick7Pov7,
	Joystick7Pov8,
	Joystick7Pov9,
	Joystick7Pov10,
	Joystick7Pov11,
	Joystick7Pov12,
	Joystick7Pov13,
	Joystick7Pov14,
	Joystick7Pov15,
	Joystick7Pov16,
	Joystick7Pov17,
	Joystick7Pov18,
	Joystick7Pov19,
	Joystick8Pov0,
	Joystick8Pov1,
	Joystick8Pov2,
	Joystick8Pov3,
	Joystick8Pov4,
	Joystick8Pov5,
	Joystick8Pov6,
	Joystick8Pov7,
	Joystick8Pov8,
	Joystick8Pov9,
	Joystick8Pov10,
	Joystick8Pov11,
	Joystick8Pov12,
	Joystick8Pov13,
	Joystick8Pov14,
	Joystick8Pov15,
	Joystick8Pov16,
	Joystick8Pov17,
	Joystick8Pov18,
	Joystick8Pov19,
	KeyCodeNum,
};
DECL_META_ENUM( XE_API, KeyCode );

enum class Operation
{
	EQUAL,
	NOT_EQUAL,
	LESS,
	GREATER,
	LESS_EQUAL,
	GREATER_EQUAL,
};
DECL_META_ENUM( XE_API, Operation );

enum class ThreadType
{
	IO,
	GAME,
	RENDER,
	PHYSICS,
	NAVIGATION,
	WORKS,
	UNKNOWN,
};
DECL_META_ENUM( XE_API, ThreadType );

using WindowEventPair = Pair<WindowHandle, XE::WindowEvent>;

END_XE_NAMESPACE

#endif 
