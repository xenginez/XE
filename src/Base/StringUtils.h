/*!
 * \file   StringUtils.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/01
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __STRINGUTILS_H__1EA13048_0A3D_4076_B97B_BC6DF4D9B40C
#define __STRINGUTILS_H__1EA13048_0A3D_4076_B97B_BC6DF4D9B40C

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API StringUtils
{
public:
	static std::string UTF16ToUTF8( const std::wstring & val );

	static std::wstring UTF8ToUTF16( const std::string & val );

	static std::string UTF16ToGBK( const std::wstring & val );

	static std::wstring GBKToUTF16( const std::string & val );

	static std::string UTF8ToGBK( const std::string & val );

	static std::string GBKToUTF8( const std::string & val );

	static XE::uint64 UTF8CharacterCount( const std::string & val );

	static std::vector<std::string> Split( const std::string & src, const std::string & sep );

public:
	static const std::string & Format( const std::string & fmt )
	{
		return fmt;
	}

	template< typename ... ARGS > static std::string Format( const std::string & fmt, ARGS && ... args )
	{
		std::string str = fmt;
		_Format( str, 1, std::move( args )... );
		return str;
	}

private:
	template< typename T > static void _Format( std::string & fmt, XE::uint64 index, T && val )
	{
		std::regex regex( ( "%" + XE::ToString( index ) ).c_str() );

		fmt = std::regex_replace( fmt, regex, XE::ToString( val ) );
	}

	template< typename T, typename ... ARGS > static void _Format( std::string & fmt, XE::uint64 index, T val, ARGS && ... args )
	{
		_Format( fmt, index, std::move( val ) );
		_Format( fmt, ++index, std::move( args )... );
	}

};

END_XE_NAMESPACE

#endif // __STRINGUTILS_H__1EA13048_0A3D_4076_B97B_BC6DF4D9B40C
