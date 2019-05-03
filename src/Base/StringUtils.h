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

class BASE_API StringUtils
{
public:
	static std::vector<std::string> Split( const std::string& src, const std::string& sep );

public:
	static std::string Format( const std::string& fmt )
	{
		return fmt;
	}

	template< typename ... ARGS > static std::string Format( const std::string& fmt, ARGS ... args )
	{
		std::string str = fmt;
		_Format( str, 0, args... );
		return str;
	}

private:
	template< typename T > static void _Format( std::string& fmt, XE::uint64 index, T val )
	{
		std::regex regex( "{%" + std::to_string( index ) + "}" );

		fmt = std::regex_replace( fmt, regex, std::to_string( val ) );
	}

	template< typename T, typename ... ARGS > static void _Format( std::string& fmt, XE::uint64 index, T val, ARGS ... args )
	{
		_Format( fmt, index, val );
		_Format( fmt, ++index, args... );
	}

};

END_XE_NAMESAPCE

#endif // __STRINGUTILS_H__1EA13048_0A3D_4076_B97B_BC6DF4D9B40C
