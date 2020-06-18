#include "Platform.h"

#if PLATFORM_OS & OS_MAC

#import <Cocoa/Cocoa.h>



IMPLEMENT_META( XE::WindowHandle );
IMPLEMENT_META( ProcessHandle );

Language XE::Platform::GetDefaultLanguage()
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

XE::WindowHandle XE::Platform::CreateWindow( const XE::String & title, XE::uint32 x, XE::uint32 y, XE::uint32 w, XE::uint32 h )
{
	NSRect frame = NSMakeRect(x, y, w, h);
	
	NSWindow* window  = [[NSWindow alloc] initWithContentRect:frame
													 styleMask:NSBorderlessWindowMask
													   backing:NSBackingStoreBuffered
														 defer:NO];
	
	[window setBackgroundColor:[NSColor blackColor]];
	[window makeKeyAndOrderFront:nil];
	
	return reinterpret_cast<XE::uint64>(window);
}

bool XE::Platform::DestroyWindow( XE::WindowHandle handle )
{
	NSWindow * window = reinterpret_cast<NSWindow*>( handle.GetValue() );
	
	[window close];
	
	[window release];
	
	return true;
}

bool XE::Platform::GrabWindow( XE::WindowHandle handle )
{
	NSWindow * window = reinterpret_cast<NSWindow*>( handle.GetValue() );
	
	[window setLevel:NSNormalWindowLevel];
	
	[window makeKeyAndOrderFront:nil];
	
	return true;
}

bool XE::Platform::ShowWindow( XE::WindowHandle handle )
{
	NSWindow * window = reinterpret_cast<NSWindow*>( handle.GetValue() );
	
	[window makeKeyAndOrderFront:nil];
	
	return true;
}

bool XE::Platform::HideWindow( XE::WindowHandle handle )
{
	NSWindow * window = reinterpret_cast<NSWindow*>( handle.GetValue() );
	
	[window orderOut:nil];
	
	return true;
}

bool XE::Platform::MinimizeWindow( XE::WindowHandle handle )
{
	NSWindow * window = reinterpret_cast<NSWindow*>( handle.GetValue() );
	
	if(![window isMiniaturized])
	{
		[window miniaturize:nil];
		
		return true;
	}
	
	return false;
}

bool XE::Platform::MaximizeWindow( XE::WindowHandle handle )
{
	NSWindow * window = reinterpret_cast<NSWindow*>( handle.GetValue() );
	
	if(![window isZoomed])
	{
		[window zoom:nil];
		
		return true;
	}
	
	return false;
}

bool XE::Platform::FullscreenWindow( XE::WindowHandle handle )
{
	NSWindow * window = reinterpret_cast<NSWindow*>( handle.GetValue() );
	
	[window setStyleMask:NSWindowStyleMaskBorderless];
	[window setFrame:[[window screen] frame] display:NO];
	[window setLevel:NSMainMenuWindowLevel+1];
	[window makeKeyAndOrderFront:nil];
	
	return true;
}

bool XE::Platform::GetWindowFocus( XE::WindowHandle handle )
{
	NSWindow * window = reinterpret_cast<NSWindow*>( handle.GetValue() );
	
	return [window isKeyWindow];
}

bool XE::Platform::SetWindowTitle( XE::WindowHandle handle, const XE::String & title )
{
	NSWindow * window = reinterpret_cast<NSWindow*>( handle.GetValue() );
	
	NSString * s = [[[NSString alloc] initWithCString:title.ToCString()] autorelease];
	
	[window setTitle:s];
	
	return true;
}

bool XE::Platform::SetWindowRect( XE::WindowHandle handle, XE::uint32 x, XE::uint32 y, XE::uint32 w, XE::uint32 h, bool topmost )
{
	NSWindow * window = reinterpret_cast<NSWindow*>( handle.GetValue() );
	
	NSRect rect;
	rect.origin.x = x;
	rect.origin.y = y;
	rect.size.width = w;
	rect.size.height = h;
	
	[window setStyleMask:NSBorderlessWindowMask];
	[window setFrame:[window frameRectForContentRect:rect] display:YES];
	[window setLevel:NSNormalWindowLevel];
	
	return true;
}

bool XE::Platform::ShowMouse()
{
	return true;
}

bool XE::Platform::HideMouse()
{
	return true;
}

XE::ProcessHandle XE::Platform::CreateProcess( const std::filesystem::path & app, const std::string & cmd, bool inherit, XE::uint32 flag )
{
	NSTask *task;
	task = [[NSTask alloc] init];
	NSString * s = [[[NSString alloc] initWithCString:app.string().c_str()] autorelease];
	[task setLaunchPath:s];
	
	NSArray *argHelp = [@[[NSString stringWithCString:cmd.c_str()]] autorelease];
	[task setArguments:argHelp];
	NSPipe *pipe;
	pipe = [NSPipe pipe];
	NSPipe * inputPipe = [NSPipe pipe];
	[task setStandardOutput: pipe];
	[task setStandardInput:inputPipe];
	NSFileHandle *file;
	file = [pipe fileHandleForReading];
	NSFileHandle * InFile = [inputPipe fileHandleForWriting];
	NSString * pDir = [NSString stringWithCString:std::filesystem::current_path().string().c_str()];
	[task setCurrentDirectoryPath:pDir];
	[task launch];
	
	return reinterpret_cast<XE::uint64>(task);
}

bool XE::Platform::DestroyProcess( XE::ProcessHandle handle, XE::uint32 code )
{
	NSTask *task = reinterpret_cast<NSTask*>(handle.GetValue());
	
	[task release];
	
	return true;
}

#endif