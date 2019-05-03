/*!
 * \file    Window.h
 *
 * \author  ZhengYuanQing
 * \date    2019-04-21$
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __XE_WINDOW_H__
#define __XE_WINDOW_H__

#include "Type.h"

BEG_XE_NAMESPACE

class UTILS_API Window : public XE::NonCopyable
{
private:
	struct Private;
	
public:
	Window();
	
	Window( const String &title, int32 x, int32 y, uint32 w, uint32 h, uint32 flags );
	
	Window( const void * data );
	
	virtual ~Window();

public:
	int32 GetX() const;
	
	void SetX( int32 val );
	
	int32 GetY() const;
	
	void SetY( int32 val );
	
	uint32 GetWidth() const;
	
	void SetWidth( uint32 val );
	
	uint32 GetHeight() const;
	
	void SetHeight( uint32 val );
	
	const void * GetData() const;
	
	void SetData( const void * val );
	
	const String& GetTitle() const;
	
	void SetTitle( const String &val );
	
public:
	uint32 GetFlags() const;

	XE::uint64 GetHandle() const;
	
public:
	void Hide();
	
	void Show();
	
	void Raise();
	
	void Restore();
	
	void Maximize();
	
	void Minimize();
	
	void Fullscreen( bool val );

private:
	Private * _p;
};
DECL_META_CLASS( UTILS_API, Window );

END_XE_NAMESAPCE

#endif //__XE_WINDOW_H__
