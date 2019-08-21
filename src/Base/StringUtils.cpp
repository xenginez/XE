#include "StringUtils.h"

#if PLATFORM_OS & OS_WINDOWS
#include <Windows.h>
#endif

USING_XE

std::string XE::StringUtils::UTF16ToUTF8( const std::wstring & val )
{
#if PLATFORM_OS & OS_WINDOWS
	std::string s;
	int len = WideCharToMultiByte( CP_UTF8, 0, val.c_str(), (int )val.length(), NULL, 0, NULL, NULL );
	if( len <= 0 )
	{
		return s;
	}

	char * buffer = new char[len + 1];
	memset( buffer, 0, len + 1 );
	WideCharToMultiByte( CP_UTF8, 0, val.c_str(), (int )val.length(), buffer, len, NULL, NULL );
	s = buffer;

	delete[] buffer;
	
	return s;
#else
	return std::wstring_convert<std::codecvt_utf8<wchar_t> >().to_bytes( val );
#endif
}

std::wstring XE::StringUtils::UTF8ToUTF16( const std::string & val )
{
#if PLATFORM_OS & OS_WINDOWS
	std::wstring s;
	int len = MultiByteToWideChar( CP_UTF8, 0, val.c_str(), (int )val.length(), NULL, 0 );
	if( len <= 0 )
	{
		return s;
	}

	wchar_t * buffer = new wchar_t[len + 1];
	memset( buffer, 0, ( len + 1 ) * sizeof( WCHAR ) );
	MultiByteToWideChar( CP_UTF8, 0, val.c_str(), (int )val.length(), buffer, len );
	s = buffer;

	delete[] buffer;

	return s;
#else
	return std::wstring_convert<std::codecvt_utf8<wchar_t> >().from_bytes( val );
#endif
}

std::string XE::StringUtils::UTF16ToGBK( const std::wstring & val )
{
#if PLATFORM_OS & OS_WINDOWS
	std::string s;
	int len = WideCharToMultiByte( CP_ACP, 0, val.c_str(), (int )val.length(), NULL, 0, NULL, NULL );
	if( len <= 0 )
	{
		return s;
	}

	char * buffer = new char[len + 1];
	memset( buffer, 0, len + 1 );
	WideCharToMultiByte( CP_ACP, 0, val.c_str(), (int )val.length(), buffer, len, NULL, NULL );
	s = buffer;

	delete[] buffer;

	return s;
#else
	return std::wstring_convert<std::codecvt_byname<wchar_t, char, mbstate_t> >( new std::codecvt_byname<wchar_t, char, mbstate_t>( ".936" ) ).to_bytes( val );
#endif
}

std::wstring XE::StringUtils::GBKToUTF16( const std::string & val )
{
#if PLATFORM_OS & OS_WINDOWS
	std::wstring s;
	int len = MultiByteToWideChar( CP_ACP, 0, val.c_str(), (int )val.length(), NULL, 0 );
	if( len <= 0 )
	{
		return s;
	}

	LPWSTR buffer = new wchar_t[len + 1];
	memset( buffer, 0, ( len + 1 ) * sizeof( WCHAR ) );
	MultiByteToWideChar( CP_ACP, 0, val.c_str(), (int )val.length(), buffer, len );
	s = buffer;

	delete[] buffer;

	return s;
#else
	return std::wstring_convert<std::codecvt_byname<wchar_t, char, mbstate_t> >( new std::codecvt_byname<wchar_t, char, mbstate_t>( ".936" ) ).from_bytes( val );
#endif
}

std::string XE::StringUtils::UTF8ToGBK( const std::string & val )
{
	return UTF16ToGBK( UTF8ToUTF16( val ) );
}

std::string XE::StringUtils::GBKToUTF8( const std::string & val )
{
	return UTF16ToUTF8( GBKToUTF16( val ) );
}

std::vector<std::string> XE::StringUtils::Split( const std::string& src, const std::string& sep )
{
	std::regex re{ sep };

	return std::vector<std::string> {
		std::sregex_token_iterator( src.begin(), src.end(), re, -1 ),
			std::sregex_token_iterator()
	};
}

XE::uint64 XE::StringUtils::UTF8CharacterCount( const std::string & val )
{
	XE::uint64 ret = 0;

	const char * str = val.c_str();

	while( *str != '\0' )
	{
		XE::uint8 i = 0;

		XE::uint8 c = static_cast< XE::uint8 >( *str );

		if( c & ( 1 << 7 ) ) i++;
		if( c & ( 1 << 6 ) ) i++;
		if( c & ( 1 << 5 ) ) i++;
		if( c & ( 1 << 4 ) ) i++;

		str += i;
		ret++;
	}

	return ret;
}
