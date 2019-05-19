#include"Utils/Type.h"

USING_XE

BEG_META(Language)
		type->Value("ENGLISH", Language::ENGLISH);
		type->Value("CHINESESIMPLIFIED", Language::CHINESESIMPLIFIED);
		type->Value("CHINESETRADITIONAL", Language::CHINESETRADITIONAL);
		type->Value("AFRIKAANS", Language::AFRIKAANS);
		type->Value("ARABIC", Language::ARABIC);
		type->Value("BASQUE", Language::BASQUE);
		type->Value("BELARUSIAN", Language::BELARUSIAN);
		type->Value("BULGARIAN", Language::BULGARIAN);
		type->Value("CATALAN", Language::CATALAN);
		type->Value("CZECH", Language::CZECH);
		type->Value("DANISH", Language::DANISH);
		type->Value("DUTCH", Language::DUTCH);
		type->Value("ESTONIAN", Language::ESTONIAN);
		type->Value("FAROESE", Language::FAROESE);
		type->Value("FINNISH", Language::FINNISH);
		type->Value("FRENCH", Language::FRENCH);
		type->Value("GERMAN", Language::GERMAN);
		type->Value("GREEK", Language::GREEK);
		type->Value("HEBREW", Language::HEBREW);
		type->Value("ICELANDIC", Language::ICELANDIC);
		type->Value("INDONESIAN", Language::INDONESIAN);
		type->Value("ITALIAN", Language::ITALIAN);
		type->Value("JAPANESE", Language::JAPANESE);
		type->Value("KOREAN", Language::KOREAN);
		type->Value("LATVIAN", Language::LATVIAN);
		type->Value("LITHUANIAN", Language::LITHUANIAN);
		type->Value("NORWEGIAN", Language::NORWEGIAN);
		type->Value("POLISH", Language::POLISH);
		type->Value("PORTUGUESE", Language::PORTUGUESE);
		type->Value("ROMANIAN", Language::ROMANIAN);
		type->Value("RUSSIAN", Language::RUSSIAN);
		type->Value("SERBOCROATIAN", Language::SERBOCROATIAN);
		type->Value("SLOVAK", Language::SLOVAK);
		type->Value("SLOVENIAN", Language::SLOVENIAN);
		type->Value("SPANISH", Language::SPANISH);
		type->Value("SWEDISH", Language::SWEDISH);
		type->Value("THAI", Language::THAI);
		type->Value("TURKISH", Language::TURKISH);
		type->Value("UKRAINIAN", Language::UKRAINIAN);
		type->Value("VIETNAMESE", Language::VIETNAMESE);
		type->Value("HUNGARIAN", Language::HUNGARIAN);
		type->Value("UNKNOWN", Language::UNKNOWN);
END_META()


BEG_META(WindowFlags)
		type->Value("FULLSCREEN", WindowFlags::FULLSCREEN);
		type->Value("SHOWN", WindowFlags::SHOWN);
		type->Value("HIDDEN", WindowFlags::HIDDEN);
		type->Value("BORDERLESS", WindowFlags::BORDERLESS);
		type->Value("RESIZABLE", WindowFlags::RESIZABLE);
		type->Value("MINIMIZED", WindowFlags::MINIMIZED);
		type->Value("MAXIMIZED", WindowFlags::MAXIMIZED);
		type->Value("INPUT_GRABBED", WindowFlags::INPUT_GRABBED);
		type->Value("INPUT_FOCUS", WindowFlags::INPUT_FOCUS);
		type->Value("MOUSE_FOCUS", WindowFlags::MOUSE_FOCUS);
		type->Value("FOREIGN", WindowFlags::FOREIGN);
		type->Value("ALLOW_HIGHDPI", WindowFlags::ALLOW_HIGHDPI);
		type->Value("MOUSE_CAPTURE", WindowFlags::MOUSE_CAPTURE);
		type->Value("ALWAYS_ON_TOP", WindowFlags::ALWAYS_ON_TOP);
		type->Value("SKIP_TASKBAR", WindowFlags::SKIP_TASKBAR);
		type->Value("UTILITY", WindowFlags::UTILITY);
		type->Value("TOOLTIP", WindowFlags::TOOLTIP);
		type->Value("POPUP_MENU", WindowFlags::POPUP_MENU);
		type->Value("VULKAN", WindowFlags::VULKAN);
END_META()
