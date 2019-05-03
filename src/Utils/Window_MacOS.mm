#include "Window.h"
#include "Window.h"

#if PLATFORM_OS == OS_MAC

#import <Cocoa/Cocoa.h>

USING_XE

BEGIN_META(Window)
END_META()

struct XE::Window::Private
{
	Private()
			:X(0), Y(0), W(1), H(1), Flags(0), Window(nullptr)
	{
	}
	
	void Setup()
	{
		NSString * title = [Window title];
		if( title )
		{
			Title = [title UTF8String];
		}
		
		{
			NSRect rect = [Window contentRectForFrameRect:[Window frame]];
			rect.origin.y = CGDisplayPixelsHigh(kCGDirectMainDisplay) - rect.origin.y - rect.size.height;
			X = ( int32 ) rect.origin.x;
			Y = ( int32 ) rect.origin.y;
			W = ( uint32 ) rect.size.width;
			H = ( uint32 ) rect.size.height;
		}
		
		Flags = [Window isVisible] ? Flags | WindowFlags::SHOWN : Flags & ( ~WindowFlags::SHOWN );
		
		uint64 style = [Window styleMask];
		Flags = style == NSWindowStyleMaskBorderless ? Flags | WindowFlags::BORDERLESS : Flags &
																						 ( ~WindowFlags::BORDERLESS );
		Flags = ( style & NSWindowStyleMaskResizable ) ? Flags | WindowFlags::RESIZABLE : Flags &
																						  ( ~WindowFlags::RESIZABLE );
		
		Flags = (( Flags & WindowFlags::RESIZABLE ) && [Window isZoomed] ) ? Flags | WindowFlags::MAXIMIZED : Flags &
																											  ( ~WindowFlags::MAXIMIZED );
		Flags = [Window isMiniaturized] ? Flags | WindowFlags::MINIMIZED : Flags & ( ~WindowFlags::MINIMIZED );
		
		Flags = [Window isKeyWindow] ? Flags | WindowFlags::INPUT_FOCUS : Flags;
	}
	
	int32 X;
	int32 Y;
	uint32 W;
	uint32 H;
	String Title;
	uint32 Flags;
	NSWindow * Window;
};

Window::Window()
		:_p(new Private)
{
	_p->Setup();
}

XE::Window::Window( const String &title, int32 x, int32 y, uint32 w, uint32 h, uint32 flags )
		:_p(new Private)
{
	_p->X = x;
	_p->Y = y;
	_p->W = w;
	_p->H = h;
	_p->Flags = flags;
	
	_p->Setup();
}

XE::Window::Window( const void * data )
		:_p(new Private)
{
	_p->Window = ( NSWindow * ) data;
	
	_p->Setup();
}

XE::Window::~Window()
{
	delete _p;
}

int32 Window::GetX() const
{
	return _p->X;
}

void Window::SetX( int32 val )
{
	_p->X = val;
	
	NSRect rect;
	
	rect.origin.x = _p->X;
	rect.origin.y = _p->Y;
	rect.size.width = _p->W;
	rect.size.height = _p->H;
	rect.origin.y = CGDisplayPixelsHigh(kCGDirectMainDisplay) - rect.origin.y - rect.size.height;
	
	[_p->Window setFrameOrigin:rect.origin];
}

int32 Window::GetY() const
{
	return _p->Y;
}

void Window::SetY( int32 val )
{
	_p->Y = val;
	
	NSRect rect;
	
	rect.origin.x = _p->X;
	rect.origin.y = _p->Y;
	rect.size.width = _p->W;
	rect.size.height = _p->H;
	rect.origin.y = CGDisplayPixelsHigh(kCGDirectMainDisplay) - rect.origin.y - rect.size.height;
	
	[_p->Window setFrameOrigin:rect.origin];
}

uint32 Window::GetWidth() const
{
	return _p->W;
}

void Window::SetWidth( uint32 val )
{
	_p->W = val;
	
	NSRect rect;
	
	rect.origin.x = _p->X;
	rect.origin.y = _p->Y;
	rect.size.width = _p->W;
	rect.size.height = _p->H;
	rect.origin.y = CGDisplayPixelsHigh(kCGDirectMainDisplay) - rect.origin.y - rect.size.height;
	
	[_p->Window setFrameOrigin:rect.origin];
}

uint32 Window::GetHeight() const
{
	return _p->H;
}

void Window::SetHeight( uint32 val )
{
	_p->H = val;
	
	NSRect rect;
	
	rect.origin.x = _p->X;
	rect.origin.y = _p->Y;
	rect.size.width = _p->W;
	rect.size.height = _p->H;
	rect.origin.y = CGDisplayPixelsHigh(kCGDirectMainDisplay) - rect.origin.y - rect.size.height;
	
	[_p->Window setFrameOrigin:rect.origin];
}

const void * Window::GetData() const
{
	return _p->Window;
}

void Window::SetData( const void * val )
{
	if( _p->Window )
	{
		[_p->Window close];
	}
	
	_p->Window = ( NSWindow * ) val;
	
	_p->Setup();
}

const String &Window::GetTitle() const
{
	return _p->Title;
}

void Window::SetTitle( const String &val )
{
	_p->Title = val;
	
	NSString * string = [[NSString alloc] initWithUTF8String:_p->Title.ToCString()];
	[_p->Window setTitle:string];
}

uint32 Window::GetFlags() const
{
	return _p->Flags;
}

XE::uint64 Window::GetHandle() const
{
	return reinterpret_cast<uint64>(_p->Window);
}

void Window::Hide()
{
	[_p->Window orderOut:nil];
}

void Window::Show()
{
	if( [_p->Window isMiniaturized] )
	{
		[_p->Window makeKeyAndOrderFront:nil];
	}
}

void Window::Raise()
{
	if( ![_p->Window isMiniaturized] && [_p->Window isVisible] )
	{
		[_p->Window makeKeyAndOrderFront:nil];
	}
}

void Window::Restore()
{
	if( [_p->Window isMiniaturized] )
	{
		[_p->Window deminiaturize:nil];
	}
	else if(( _p->Flags & WindowFlags::RESIZABLE ) && [_p->Window isZoomed] )
	{
		[_p->Window zoom:nil];
	}
}

void Window::Maximize()
{
	[_p->Window zoom:nil];
}

void Window::Minimize()
{
	[_p->Window miniaturize:nil];
}

void Window::Fullscreen( bool val )
{
	_p->Flags |= WindowFlags::FULLSCREEN;
	
	NSRect rect;
	
	if( val )
	{
		rect.origin.x = 0;
		rect.origin.y = 0;
		rect.size.width = [[NSScreen mainScreen] frame].size.width;
		rect.size.height = [[NSScreen mainScreen] frame].size.height;
		rect.origin.y = CGDisplayPixelsHigh(kCGDirectMainDisplay) - rect.origin.y - rect.size.height;
		
		NSRect screenRect = [[_p->Window screen] frame];
		if( screenRect.size.height >= 1.0f )
		{
			rect.origin.y += ( screenRect.size.height - rect.size.height );
		}
		
		[_p->Window setStyleMask:NSWindowStyleMaskBorderless];
	}
	else
	{
		rect.origin.x = _p->X;
		rect.origin.y = _p->Y;
		rect.size.width = _p->W;
		rect.size.height = _p->H;
		rect.origin.y = CGDisplayPixelsHigh(kCGDirectMainDisplay) - rect.origin.y - rect.size.height;
		
		[_p->Window setStyleMask:_p->Flags];
		
		NSRect frameRect = [_p->Window frame];
		[_p->Window setFrame:NSMakeRect(frameRect.origin.x, frameRect.origin.y, frameRect.size.width +
																				1, frameRect.size.height) display:NO];
		[_p->Window setFrame:frameRect display:NO];
	}
}

#endif