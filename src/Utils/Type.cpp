#include"Type.h"

USING_XE

BEG_META( AssetStatus )
type->Value( "UNDEFINED", AssetStatus::UNDEFINED );
type->Value( "LOADING", AssetStatus::LOADING );
type->Value( "READY", AssetStatus::READY );
type->Value( "FAILED", AssetStatus::FAILED );
END_META()

BEG_META( Language )
type->Value( "ENGLISH", Language::ENGLISH );
type->Value( "CHINESESIMPLIFIED", Language::CHINESESIMPLIFIED );
type->Value( "CHINESETRADITIONAL", Language::CHINESETRADITIONAL );
type->Value( "AFRIKAANS", Language::AFRIKAANS );
type->Value( "ARABIC", Language::ARABIC );
type->Value( "BASQUE", Language::BASQUE );
type->Value( "BELARUSIAN", Language::BELARUSIAN );
type->Value( "BULGARIAN", Language::BULGARIAN );
type->Value( "CATALAN", Language::CATALAN );
type->Value( "CZECH", Language::CZECH );
type->Value( "DANISH", Language::DANISH );
type->Value( "DUTCH", Language::DUTCH );
type->Value( "ESTONIAN", Language::ESTONIAN );
type->Value( "FAROESE", Language::FAROESE );
type->Value( "FINNISH", Language::FINNISH );
type->Value( "FRENCH", Language::FRENCH );
type->Value( "GERMAN", Language::GERMAN );
type->Value( "GREEK", Language::GREEK );
type->Value( "HEBREW", Language::HEBREW );
type->Value( "ICELANDIC", Language::ICELANDIC );
type->Value( "INDONESIAN", Language::INDONESIAN );
type->Value( "ITALIAN", Language::ITALIAN );
type->Value( "JAPANESE", Language::JAPANESE );
type->Value( "KOREAN", Language::KOREAN );
type->Value( "LATVIAN", Language::LATVIAN );
type->Value( "LITHUANIAN", Language::LITHUANIAN );
type->Value( "NORWEGIAN", Language::NORWEGIAN );
type->Value( "POLISH", Language::POLISH );
type->Value( "PORTUGUESE", Language::PORTUGUESE );
type->Value( "ROMANIAN", Language::ROMANIAN );
type->Value( "RUSSIAN", Language::RUSSIAN );
type->Value( "SERBOCROATIAN", Language::SERBOCROATIAN );
type->Value( "SLOVAK", Language::SLOVAK );
type->Value( "SLOVENIAN", Language::SLOVENIAN );
type->Value( "SPANISH", Language::SPANISH );
type->Value( "SWEDISH", Language::SWEDISH );
type->Value( "THAI", Language::THAI );
type->Value( "TURKISH", Language::TURKISH );
type->Value( "UKRAINIAN", Language::UKRAINIAN );
type->Value( "VIETNAMESE", Language::VIETNAMESE );
type->Value( "HUNGARIAN", Language::HUNGARIAN );
type->Value( "UNKNOWN", Language::UNKNOWN );
END_META()

BEG_META( WindowEvent )
type->Value( "CREATE", WindowEvent::CREATE );
type->Value( "DESTROY", WindowEvent::DESTROY );
type->Value( "MOVE", WindowEvent::MOVE );
type->Value( "SIZE", WindowEvent::SIZE );
type->Value( "ACTIVATE", WindowEvent::ACTIVATE );
type->Value( "SETFOCUS", WindowEvent::SETFOCUS );
type->Value( "KILLFOCUS", WindowEvent::KILLFOCUS );
type->Value( "ENABLE", WindowEvent::ENABLE );
type->Value( "PAINT", WindowEvent::PAINT );
type->Value( "CLOSE", WindowEvent::CLOSE );
type->Value( "QUERYENDSESSION", WindowEvent::QUERYENDSESSION );
type->Value( "QUIT", WindowEvent::QUIT );
type->Value( "SHOWWINDOW", WindowEvent::SHOWWINDOW );
type->Value( "ACTIVATEAPP", WindowEvent::ACTIVATEAPP );
type->Value( "SETCURSOR", WindowEvent::SETCURSOR );
type->Value( "MOUSEACTIVATE", WindowEvent::MOUSEACTIVATE );
type->Value( "GETMINMAXINFO", WindowEvent::GETMINMAXINFO );
type->Value( "NEXTDLGCTL", WindowEvent::NEXTDLGCTL );
type->Value( "COMPACTING", WindowEvent::COMPACTING );
type->Value( "WINDOWPOSCHANGING", WindowEvent::WINDOWPOSCHANGING );
type->Value( "WINDOWPOSCHANGED", WindowEvent::WINDOWPOSCHANGED );
type->Value( "DISPLAYCHANGE", WindowEvent::DISPLAYCHANGE );
type->Value( "GETICON", WindowEvent::GETICON );
type->Value( "SETICON", WindowEvent::SETICON );
type->Value( "KEYDOWN", WindowEvent::KEYDOWN );
type->Value( "KEYUP", WindowEvent::KEYUP );
type->Value( "CHAR", WindowEvent::CHAR );
type->Value( "DEADCHAR", WindowEvent::DEADCHAR );
type->Value( "SYSKEYDOWN", WindowEvent::SYSKEYDOWN );
type->Value( "SYSKEYUP", WindowEvent::SYSKEYUP );
type->Value( "SYSCHAR", WindowEvent::SYSCHAR );
type->Value( "SYSDEADCHAR", WindowEvent::SYSDEADCHAR );
type->Value( "MOUSEMOVE", WindowEvent::MOUSEMOVE );
type->Value( "LBUTTONDOWN", WindowEvent::LBUTTONDOWN );
type->Value( "LBUTTONUP", WindowEvent::LBUTTONUP );
type->Value( "LBUTTONDBLCLK", WindowEvent::LBUTTONDBLCLK );
type->Value( "RBUTTONDOWN", WindowEvent::RBUTTONDOWN );
type->Value( "RBUTTONUP", WindowEvent::RBUTTONUP );
type->Value( "RBUTTONDBLCLK", WindowEvent::RBUTTONDBLCLK );
type->Value( "MBUTTONDOWN", WindowEvent::MBUTTONDOWN );
type->Value( "MBUTTONUP", WindowEvent::MBUTTONUP );
type->Value( "MBUTTONDBLCLK", WindowEvent::MBUTTONDBLCLK );
type->Value( "MOUSEWHEEL", WindowEvent::MOUSEWHEEL );
type->Value( "SIZING", WindowEvent::SIZING );
type->Value( "CAPTURECHANGED", WindowEvent::CAPTURECHANGED );
type->Value( "MOVING", WindowEvent::MOVING );
type->Value( "POWERBROADCAST", WindowEvent::POWERBROADCAST );
type->Value( "DEVICECHANGE", WindowEvent::DEVICECHANGE );
END_META()
