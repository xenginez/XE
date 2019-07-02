/*!
 * \file   Platform.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __PLATFORM_H__BDD7C650_EC23_41CF_A4EA_7CDBFE3B0135
#define __PLATFORM_H__BDD7C650_EC23_41CF_A4EA_7CDBFE3B0135

#include "Type.h"

BEG_XE_NAMESPACE

class UTILS_API Platform
{
public:
	static Language GetDefaultLanguage();

public:
	static bool RegisterWindowClass( const String & icon, std::function<bool( XE::uint64, XE::uint64, XE::uint64, XE::uint64 )> callback );

	static XE::uint64 ConstructWindow( const String & title, XE::uint32 x, XE::uint32 y, XE::uint32 w, XE::uint32 h );

	static bool DestroyWindow( XE::uint64 handle );

	static bool GrabWindow( XE::uint64 handle );

	static bool ShowWindow( XE::uint64 handle );

	static bool HideWindow( XE::uint64 handle );

	static bool MinimizeWindow( XE::uint64 handle );

	static bool MaximizeWindow( XE::uint64 handle );

	static bool FullscreenWindow( XE::uint64 handle );

	static bool SetWindowRect( XE::uint64 handle, XE::uint32 x, XE::uint32 y, XE::uint32 w, XE::uint32 h, bool topmost );

};

END_XE_NAMESPACE

#endif // __PLATFORM_H__BDD7C650_EC23_41CF_A4EA_7CDBFE3B0135
