#include "BASE64.h"

USING_XE

BEG_META( BASE64 )
END_META()

const char BASE64::_base64_encode_table[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

const char BASE64::_base64_decode_table[256] =
{
	-2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -1, -2, -2, -1, -2, -2,
	-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
	-1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 62, -2, -2, -2, 63,
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -2, -2, -2, -2, -2, -2,
	-2,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -2, -2, -2, -2, -2,
	-2, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -2, -2, -2, -2, -2,
	-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
	-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
	-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
	-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
	-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
	-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
	-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
	-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
};

std::string BASE64::Encode( const uint8 * src, XE::uint64 size )
{
	std::string ret;

	while ( size > 2 )
	{
		ret += _base64_encode_table[src[0] >> 2];
		ret += _base64_encode_table[( ( src[0] & 0x03 ) << 4 ) + ( src[1] >> 4 )];
		ret += _base64_encode_table[( ( src[1] & 0x0f ) << 2 ) + ( src[2] >> 6 )];
		ret += _base64_encode_table[src[2] & 0x3f];

		src += 3;
		size -= 3;
	}

	if ( size > 0 )
	{
		ret+= _base64_encode_table[src[0] >> 2];
		if ( size % 3 == 1 )
		{
			ret += _base64_encode_table[( src[0] & 0x03 ) << 4];
			ret += "==";
		}
		else if ( size % 3 == 2 )
		{
			ret += _base64_encode_table[( ( src[0] & 0x03 ) << 4 ) + ( src[1] >> 4 )];
			ret += _base64_encode_table[( src[1] & 0x0f ) << 2];
			ret += '=';
		}
	}

	return ret;
}

XE::uint64 XE::BASE64::Encode( const uint8 * src, XE::uint64 size, uint8 * out )
{
	XE::uint64 ret = 0;

	while ( size > 2 )
	{
		out[ret++] = _base64_encode_table[src[0] >> 2];
		out[ret++] = _base64_encode_table[( ( src[0] & 0x03 ) << 4 ) + ( src[1] >> 4 )];
		out[ret++] = _base64_encode_table[( ( src[1] & 0x0f ) << 2 ) + ( src[2] >> 6 )];
		out[ret++] = _base64_encode_table[src[2] & 0x3f];

		src += 3;
		size -= 3;
	}

	if ( size > 0 )
	{
		out[ret++] = _base64_encode_table[src[0] >> 2];
		if ( size % 3 == 1 )
		{
			out[ret++] = _base64_encode_table[( src[0] & 0x03 ) << 4];
			out[ret++] = '=';
			out[ret++] = '=';
		}
		else if ( size % 3 == 2 )
		{
			out[ret++] = _base64_encode_table[( ( src[0] & 0x03 ) << 4 ) + ( src[1] >> 4 )];
			out[ret++] = _base64_encode_table[( src[1] & 0x0f ) << 2];
			out[ret++] = '=';
		}
	}

	return ret;
}

XE::uint64 BASE64::Decode( const std::string& str, char * out )
{
	XE::uint64 size = str.size();
	const uint8 * src = (const uint8 *)str.c_str();

	int32 bin = 0, i = 0, pos = 0;

	XE::uint64 ret = 0;

	int32 * buf = (int *)out;
	char ch;

	while ( ( ch = *src++ ) != '\0' && size-- > 0 )
	{
		if ( ch == '=' )
		{
			if ( *src != '=' && ( i % 4 ) == 1 )
			{
				return 0;
			}

			continue;
		}

		ch = _base64_decode_table[ch];

		if ( ch < 0 )
		{
			continue;
		}

		switch ( i % 4 )
		{
		case 0:
			bin = ch << 2;
			break;
		case 1:
			bin |= ch >> 4;
			buf[ret] = bin; ret += 4;
			bin = ( ch & 0x0f ) << 4;
			break;
		case 2:
			bin |= ch >> 2;
			buf[ret] = bin; ret += 4;
			bin = ( ch & 0x03 ) << 6;
			break;
		case 3:
			bin |= ch;
			buf[ret] = bin; ret += 4;
			break;
		}

		i++;
	}

	return ret;
}

XE::uint64 XE::BASE64::Decode( const uint8* src, XE::uint64 size, char * out )
{
	int32 bin = 0, i = 0, pos = 0;

	XE::uint64 ret = 0;

	int32 * buf = (int *)out;
	char ch;

	while ( ( ch = *src++ ) != '\0' && size-- > 0 )
	{
		if ( ch == '=' )
		{
			if ( *src != '=' && ( i % 4 ) == 1 )
			{
				return 0;
			}

			continue;
		}

		ch = _base64_decode_table[ch];

		if ( ch < 0 )
		{
			continue;
		}

		switch ( i % 4 )
		{
		case 0:
			bin = ch << 2;
			break;
		case 1:
			bin |= ch >> 4;
			buf[ret] = bin; ret += 4;
			bin = ( ch & 0x0f ) << 4;
			break;
		case 2:
			bin |= ch >> 2;
			buf[ret] = bin; ret += 4;
			bin = ( ch & 0x03 ) << 6;
			break;
		case 3:
			bin |= ch;
			buf[ret] = bin; ret += 4;
			break;
		}

		i++;
	}

	return ret;
}
