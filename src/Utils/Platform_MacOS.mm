#include "Platform.h"

#if PLATFORM_OS & OS_MAC

#import <Cocoa/Cocoa.h>

USING_XE

Language Platform::GetDefaultLanguage()
{
	NSUserDefaults * defaults = [NSUserDefaults standardUserDefaults];
	
	NSArray * languages = [defaults objectForKey:@"AppleLanguages"];
	
	NSString * currentLanguage = languages[0];
	
	if( [currentLanguage containsString:@"en"] )
	{
		return Language::ENGLISH;
	}
	else if( [currentLanguage containsString:@"en-GB"] )
	{
		return Language::ENGLISH;
	}
	else if( [currentLanguage containsString:@"zh-Hans"] )
	{
		return Language::CHINESESIMPLIFIED;
	}
	else if( [currentLanguage containsString:@"zh-Hant"] )
	{
		return Language::CHINESETRADITIONAL;
	}
	else if( [currentLanguage containsString:@"fr"] )
	{
		return Language::FAROESE;
	}
	else if( [currentLanguage containsString:@"de"] )
	{
		return Language::ENGLISH;
	}
	else if( [currentLanguage containsString:@"ja"] )
	{
		return Language::JAPANESE;
	}
	else if( [currentLanguage containsString:@"nl"] )
	{
		return Language::ENGLISH;
	}
	else if( [currentLanguage containsString:@"it"] )
	{
		return Language::ITALIAN;
	}
	else if( [currentLanguage containsString:@"es"] )
	{
		return Language::ESTONIAN;
	}
	else if( [currentLanguage containsString:@"pt"] )
	{
		return Language::PORTUGUESE;
	}
	else if( [currentLanguage containsString:@"pt-PT"] )
	{
		return Language::PORTUGUESE;
	}
	else if( [currentLanguage containsString:@"da"] )
	{
		return Language::DANISH;
	}
	else if( [currentLanguage containsString:@"fi"] )
	{
		return Language::FINNISH;
	}
	else if( [currentLanguage containsString:@"nb"] )
	{
		return Language::ENGLISH;
	}
	else if( [currentLanguage containsString:@"sv"] )
	{
		return Language::SLOVAK;
	}
	else if( [currentLanguage containsString:@"ko"] )
	{
		return Language::KOREAN;
	}
	else if( [currentLanguage containsString:@"ru"] )
	{
		return Language::RUSSIAN;
	}
	else if( [currentLanguage containsString:@"pl"] )
	{
		return Language::POLISH;
	}
	else if( [currentLanguage containsString:@"tr"] )
	{
		return Language::TURKISH;
	}
	else if( [currentLanguage containsString:@"uk"] )
	{
		return Language::UKRAINIAN;
	}
	else if( [currentLanguage containsString:@"ar"] )
	{
		return Language::ARABIC;
	}
	else if( [currentLanguage containsString:@"hr"] )
	{
		return Language::ENGLISH;
	}
	else if( [currentLanguage containsString:@"cs"] )
	{
		return Language::ENGLISH;
	}
	else if( [currentLanguage containsString:@"el"] )
	{
		return Language::ENGLISH;
	}
	else if( [currentLanguage containsString:@"he"] )
	{
		return Language::HEBREW;
	}
	else if( [currentLanguage containsString:@"ro"] )
	{
		return Language::ROMANIAN;
	}
	else if( [currentLanguage containsString:@"sk"] )
	{
		return Language::SLOVAK;
	}
	else if( [currentLanguage containsString:@"th"] )
	{
		return Language::TURKISH;
	}
	else if( [currentLanguage containsString:@"id"] )
	{
		return Language::INDONESIAN;
	}
	else if( [currentLanguage containsString:@"ms"] )
	{
		return Language::ENGLISH;
	}
	else if( [currentLanguage containsString:@"ca"] )
	{
		return Language::CATALAN;
	}
	else if( [currentLanguage containsString:@"hu"] )
	{
		return Language::HUNGARIAN;
	}
	else if( [currentLanguage containsString:@"vi"] )
	{
		return Language::VIETNAMESE;
	}
	
	return Language::ENGLISH;
}

#endif