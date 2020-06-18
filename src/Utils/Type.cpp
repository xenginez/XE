#include"Type.h"



BEG_META( XE::AssetStatus )
type->Value( "UNDEFINED", XE::AssetStatus::UNDEFINED );
type->Value( "LOADING", XE::AssetStatus::LOADING );
type->Value( "READY", XE::AssetStatus::READY );
type->Value( "FAILED", XE::AssetStatus::FAILED );
END_META()

BEG_META( XE::Language )
type->Value( "ENGLISH", XE::Language::ENGLISH );
type->Value( "CHINESESIMPLIFIED", XE::Language::CHINESESIMPLIFIED );
type->Value( "CHINESETRADITIONAL", XE::Language::CHINESETRADITIONAL );
type->Value( "AFRIKAANS", XE::Language::AFRIKAANS );
type->Value( "ARABIC", XE::Language::ARABIC );
type->Value( "BASQUE", XE::Language::BASQUE );
type->Value( "BELARUSIAN", XE::Language::BELARUSIAN );
type->Value( "BULGARIAN", XE::Language::BULGARIAN );
type->Value( "CATALAN", XE::Language::CATALAN );
type->Value( "CZECH", XE::Language::CZECH );
type->Value( "DANISH", XE::Language::DANISH );
type->Value( "DUTCH", XE::Language::DUTCH );
type->Value( "ESTONIAN", XE::Language::ESTONIAN );
type->Value( "FAROESE", XE::Language::FAROESE );
type->Value( "FINNISH", XE::Language::FINNISH );
type->Value( "FRENCH", XE::Language::FRENCH );
type->Value( "GERMAN", XE::Language::GERMAN );
type->Value( "GREEK", XE::Language::GREEK );
type->Value( "HEBREW", XE::Language::HEBREW );
type->Value( "ICELANDIC", XE::Language::ICELANDIC );
type->Value( "INDONESIAN", XE::Language::INDONESIAN );
type->Value( "ITALIAN", XE::Language::ITALIAN );
type->Value( "JAPANESE", XE::Language::JAPANESE );
type->Value( "KOREAN", XE::Language::KOREAN );
type->Value( "LATVIAN", XE::Language::LATVIAN );
type->Value( "LITHUANIAN", XE::Language::LITHUANIAN );
type->Value( "NORWEGIAN", XE::Language::NORWEGIAN );
type->Value( "POLISH", XE::Language::POLISH );
type->Value( "PORTUGUESE", XE::Language::PORTUGUESE );
type->Value( "ROMANIAN", XE::Language::ROMANIAN );
type->Value( "RUSSIAN", XE::Language::RUSSIAN );
type->Value( "SERBOCROATIAN", XE::Language::SERBOCROATIAN );
type->Value( "SLOVAK", XE::Language::SLOVAK );
type->Value( "SLOVENIAN", XE::Language::SLOVENIAN );
type->Value( "SPANISH", XE::Language::SPANISH );
type->Value( "SWEDISH", XE::Language::SWEDISH );
type->Value( "THAI", XE::Language::THAI );
type->Value( "TURKISH", XE::Language::TURKISH );
type->Value( "UKRAINIAN", XE::Language::UKRAINIAN );
type->Value( "VIETNAMESE", XE::Language::VIETNAMESE );
type->Value( "HUNGARIAN", XE::Language::HUNGARIAN );
type->Value( "UNKNOWN", XE::Language::UNKNOWN );
END_META()

BEG_META( XE::WindowEvent )
type->Value( "CREATE", XE::WindowEvent::CREATE );
type->Value( "DESTROY", XE::WindowEvent::DESTROY );
type->Value( "MOVE", XE::WindowEvent::MOVE );
type->Value( "SIZE", XE::WindowEvent::SIZE );
type->Value( "ACTIVATE", XE::WindowEvent::ACTIVATE );
type->Value( "SETFOCUS", XE::WindowEvent::SETFOCUS );
type->Value( "KILLFOCUS", XE::WindowEvent::KILLFOCUS );
type->Value( "ENABLE", XE::WindowEvent::ENABLE );
type->Value( "PAINT", XE::WindowEvent::PAINT );
type->Value( "CLOSE", XE::WindowEvent::CLOSE );
type->Value( "QUERYENDSESSION", XE::WindowEvent::QUERYENDSESSION );
type->Value( "QUIT", XE::WindowEvent::QUIT );
type->Value( "SHOWWINDOW", XE::WindowEvent::SHOWWINDOW );
type->Value( "ACTIVATEAPP", XE::WindowEvent::ACTIVATEAPP );
type->Value( "SETCURSOR", XE::WindowEvent::SETCURSOR );
type->Value( "MOUSEACTIVATE", XE::WindowEvent::MOUSEACTIVATE );
type->Value( "GETMINMAXINFO", XE::WindowEvent::GETMINMAXINFO );
type->Value( "NEXTDLGCTL", XE::WindowEvent::NEXTDLGCTL );
type->Value( "COMPACTING", XE::WindowEvent::COMPACTING );
type->Value( "WINDOWPOSCHANGING", XE::WindowEvent::WINDOWPOSCHANGING );
type->Value( "WINDOWPOSCHANGED", XE::WindowEvent::WINDOWPOSCHANGED );
type->Value( "DISPLAYCHANGE", XE::WindowEvent::DISPLAYCHANGE );
type->Value( "GETICON", XE::WindowEvent::GETICON );
type->Value( "SETICON", XE::WindowEvent::SETICON );
type->Value( "KEYDOWN", XE::WindowEvent::KEYDOWN );
type->Value( "KEYUP", XE::WindowEvent::KEYUP );
type->Value( "CHAR", XE::WindowEvent::CHAR );
type->Value( "DEADCHAR", XE::WindowEvent::DEADCHAR );
type->Value( "SYSKEYDOWN", XE::WindowEvent::SYSKEYDOWN );
type->Value( "SYSKEYUP", XE::WindowEvent::SYSKEYUP );
type->Value( "SYSCHAR", XE::WindowEvent::SYSCHAR );
type->Value( "SYSDEADCHAR", XE::WindowEvent::SYSDEADCHAR );
type->Value( "MOUSEMOVE", XE::WindowEvent::MOUSEMOVE );
type->Value( "LBUTTONDOWN", XE::WindowEvent::LBUTTONDOWN );
type->Value( "LBUTTONUP", XE::WindowEvent::LBUTTONUP );
type->Value( "LBUTTONDBLCLK", XE::WindowEvent::LBUTTONDBLCLK );
type->Value( "RBUTTONDOWN", XE::WindowEvent::RBUTTONDOWN );
type->Value( "RBUTTONUP", XE::WindowEvent::RBUTTONUP );
type->Value( "RBUTTONDBLCLK", XE::WindowEvent::RBUTTONDBLCLK );
type->Value( "MBUTTONDOWN", XE::WindowEvent::MBUTTONDOWN );
type->Value( "MBUTTONUP", XE::WindowEvent::MBUTTONUP );
type->Value( "MBUTTONDBLCLK", XE::WindowEvent::MBUTTONDBLCLK );
type->Value( "MOUSEWHEEL", XE::WindowEvent::MOUSEWHEEL );
type->Value( "SIZING", XE::WindowEvent::SIZING );
type->Value( "CAPTURECHANGED", XE::WindowEvent::CAPTURECHANGED );
type->Value( "MOVING", XE::WindowEvent::MOVING );
type->Value( "POWERBROADCAST", XE::WindowEvent::POWERBROADCAST );
type->Value( "DEVICECHANGE", XE::WindowEvent::DEVICECHANGE );
END_META()
