#include "String.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <iconv.h>
#endif

static const std::string local_codeset = []()
{
	std::string local = "";

#ifdef _WIN32
	char *s;
	size_t len;
	errno_t err = _dupenv_s( &s, &len, "LC_CTYPE" );
	if( err == 0 )
	{
		local = s;
	}
#else
	local = getenv( "LC_CTYPE" );
#endif

	size_t pos = local.find( '.' );
	if( pos != std::string::npos )
	{
		local.erase( local.begin(), local.begin() + ( pos + 1 ) );
	}

	return std::move( local );
}( );


XE::code_point::code_point()
	: _unicode( 0 )
{
}

XE::code_point::code_point( char c )
	: _unicode( static_cast< unsigned char >( c ) )
{

}

XE::code_point::code_point( wchar_t c )
	: _unicode( c )
{

}

XE::code_point::code_point( char16_t c )
	: _unicode( c )
{
}

XE::code_point::code_point( char32_t c )
	: _unicode( c )
{
}

XE::code_point::code_point( const XE::code_point & other )
	: _unicode( other._unicode )
{
}

bool XE::code_point::operator!=( const XE::code_point & other ) const
{
	return _unicode != other._unicode;
}

bool XE::code_point::operator==( const XE::code_point & other ) const
{
	return _unicode == other._unicode;
}

bool XE::code_point::operator<( const XE::code_point & other ) const
{
	return _unicode < other._unicode;
}

bool XE::code_point::operator<=( const XE::code_point & other ) const
{
	return _unicode <= other._unicode;
}

bool XE::code_point::operator>( const XE::code_point & other ) const
{
	return _unicode > other._unicode;
}

bool XE::code_point::operator>=( const XE::code_point & other ) const
{
	return _unicode >= other._unicode;
}

XE::code_point & XE::code_point::operator=( const XE::code_point & c )
{
	_unicode = c._unicode;
	return *this;
}

uint32_t XE::code_point::unicode() const
{
	return _unicode;
}


XE::code_point_arrow::code_point_arrow( XE::code_point c )
	: _data( c )
{
}

const XE::code_point * XE::code_point_arrow::operator->() const
{
	return &_data;
}


XE::code_point XE::ansi_encode::get_code_point( const XE::ansi_encode::storage_unit * iter )
{
	wchar_t value = 0;
	unsigned char tmp = static_cast< unsigned char >( *iter );

	if( tmp >= 0x80 && tmp <= 0xFF )
	{
		value = ( wchar_t( tmp ) << 8 ) | static_cast< unsigned char >( iter[1] );
	}

	return code_point( value );
}

XE::ansi_encode::size_type XE::ansi_encode::num_of_bytes( XE::ansi_encode::storage_unit value )
{
	if( static_cast< unsigned char >( value ) >= 0x80 && static_cast< unsigned char >( value ) <= 0xFF )
	{
		return 2;
	}

	return 1;
}


XE::code_point XE::wide_encode::get_code_point( const XE::wide_encode::storage_unit * iter )
{
	return code_point( *iter );
}

XE::wide_encode::size_type XE::wide_encode::num_of_bytes( XE::wide_encode::storage_unit value )
{
	return 1;
}


XE::code_point XE::utf8_encode::get_code_point( const XE::utf8_encode::storage_unit * iter )
{
	char32_t value = 0;
	unsigned char tmp = static_cast< unsigned char >( *iter );

	if( ( tmp & 0x80 ) == 0 )
	{
		value = tmp;
	}
	else if( ( tmp & 0xE0 ) == 0xC0 )
	{
		value = ( tmp & 0x1F ) << 6;

		tmp = iter[1];
		value |= ( tmp & 0x3F );
	}
	else if( ( tmp & 0xF0 ) == 0xE0 )
	{
		value = ( tmp & 0x0F ) << 12;

		tmp = iter[1];
		value |= ( tmp & 0x3F ) << 6;

		tmp = iter[2];
		value |= ( tmp & 0x3F );
	}
	else
	{
		value = ( tmp & 0x07 ) << 18;

		tmp = iter[1];
		value |= ( tmp & 0x3F ) << 12;

		tmp = iter[2];
		value |= ( tmp & 0x3F ) << 6;

		tmp = iter[3];
		value |= ( tmp & 0x3F );
	}

	return code_point( value );
}

XE::utf8_encode::size_type XE::utf8_encode::num_of_bytes( XE::utf8_encode::storage_unit value )
{
	unsigned char val = static_cast< unsigned char >( value );
	if( ( val & 0x80 ) == 0 )
	{
		return 1;
	}
	else if( ( val & 0xE0 ) == 0xC0 )
	{
		return 2;
	}
	else if( ( val & 0xF0 ) == 0xE0 )
	{
		return 3;
	}
	else if( ( val & 0xF8 ) == 0xF0 )
	{
		return 4;
	}

	return 1;
}


std::wstring XE::code_point_convert::ansi_2_wide( const std::string & str )
{
	std::wstring result;

#if _WIN32
	auto len = MultiByteToWideChar( CP_ACP, 0, str.c_str(), static_cast< int >( str.size() ), nullptr, 0 );
	if( len > 0 )
	{
		result.resize( len + 1 );

		if( MultiByteToWideChar( CP_ACP, 0, str.c_str(), static_cast< int >( str.size() ), ( wchar_t * )result.data(), len ) == 0 )
		{
			result.clear();
		}
	}
#else
	result.resize( mbstowcs( nullptr, str.c_str(), 0 ) );
	if( mbstowcs( ( wchar_t * )result.data(), str.c_str(), 0 ) == -1 )
	{
		result.clear();
	}
#endif

	return result;
}

std::string XE::code_point_convert::wide_2_ansi( const std::wstring & str )
{
	std::string result;

#if _WIN32
	auto len = WideCharToMultiByte( CP_ACP, 0, str.c_str(), static_cast< int >( str.size() ), nullptr, 0, nullptr, nullptr );
	if( len > 0 )
	{
		result.resize( len + 1 );

		if( WideCharToMultiByte( CP_ACP, 0, str.c_str(), static_cast< int >( str.size() ), ( char * )result.data(), len, nullptr, nullptr ) == 0 )
		{
			result.clear();
		}
	}
#else
	result.resize( wcstombs( nullptr, str.c_str(), 0 ) );
	if( wcstombs( ( char * )result.data(), str.c_str(), 0 ) == -1 )
	{
		result.clear();
	}
#endif

	return result;
}

std::string XE::code_point_convert::ansi_2_utf8( const std::string & str )
{
#if _WIN32
	return wide_2_utf8( ansi_2_wide( str ) );
#else
	std::string result;

	iconv_t cd = iconv_open( local_codeset.c_str(), "utf8" );
	if( cd != 0 )
	{
		char buf[1024];
		std::memset( buf, 0, 1024 );

		char ** pin = &( char * )str.c_str();
		size_t src_len = str.size();
		char ** pout = &buf;
		size_t dst_len = 1024;

		while( src_len > 0 )
		{
			if( iconv( cd, pin, &src_len, pout, &dst_len ) == -1 )
			{
				result.clear();
				break;
			}
			else
			{
				result.insert( result.end(), buf, buf + ( 1024 - dst_len ) );
				std::memset( buf, 0, 1024 );

				dst_len = 1024;
				pin = &( char * )( str.c_str() + ( str.size() - src_len ) );
				src_len = str.size() - src_len;
			}
		}
	}

	return result;
#endif
}

std::string XE::code_point_convert::utf8_2_ansi( const std::string & str )
{
	std::string result;

#if _WIN32
	auto len = MultiByteToWideChar( CP_UTF8, 0, str.c_str(), -1, nullptr, 0 );
	if( len > 0 )
	{
		std::wstring buf;

		buf.resize( len + 1 );

		if( MultiByteToWideChar( CP_UTF8, 0, str.c_str(), -1, ( wchar_t * )buf.data(), len ) > 0 )
		{
			result = wide_2_ansi( buf );
		}
	}
#else
	iconv_t cd = iconv_open( "utf8", local_codeset.c_str() );
	if( cd != 0 )
	{
		char buf[1024];
		std::memset( buf, 0, 1024 );

		char ** pin = &( char * )str.c_str();
		size_t src_len = str.size();
		char ** pout = &buf;
		size_t dst_len = 1024;

		while( src_len > 0 )
		{
			if( iconv( cd, pin, &src_len, pout, &dst_len ) == -1 )
			{
				result.clear();
				break;
			}
			else
			{
				result.insert( result.end(), buf, buf + ( 1024 - dst_len ) );
				std::memset( buf, 0, 1024 );

				dst_len = 1024;
				pin = &( char * )( str.c_str() + ( str.size() - src_len ) );
				src_len = str.size() - src_len;
			}
		}
	}
#endif

	return result;
}

std::string XE::code_point_convert::wide_2_utf8( const std::wstring & str )
{
	std::string result;

#if _WIN32
	auto len = WideCharToMultiByte( CP_UTF8, 0, str.c_str(), -1, nullptr, 0, nullptr, nullptr );
	if( len > 0 )
	{
		result.resize( len + 1 );

		if( WideCharToMultiByte( CP_UTF8, 0, str.c_str(), -1, ( char * )result.data(), len, nullptr, nullptr ) == 0 )
		{
			result.clear();
		}
	}
#else
	result = ansi_2_utf8( wide_2_ansi( str ) );
#endif

	return result;
}

std::wstring XE::code_point_convert::utf8_2_wide( const std::string & str )
{
	std::wstring result;

#if _WIN32
	auto len = MultiByteToWideChar( CP_UTF8, 0, str.c_str(), -1, nullptr, 0 );
	if( len > 0 )
	{
		result.resize( len + 1 );

		if( MultiByteToWideChar( CP_UTF8, 0, str.c_str(), static_cast< int >( str.size() ), ( wchar_t * )result.data(), len ) == 0 )
		{
			result.clear();
		}
	}
#else
	result = ansi_2_wide( utf8_2_ansi( str ) );
#endif

	return result;
}
