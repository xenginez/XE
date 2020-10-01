/*!
 * \file	MD5.h
 *
 * \author	ZhengYuanQing
 * \date	2019/12/15
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef MD5_H__EF0EE087_0F95_41D9_956F_532BA1F954FA
#define MD5_H__EF0EE087_0F95_41D9_956F_532BA1F954FA

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API MD5
{
public:
	MD5();

	MD5( const MD5 & val );

	MD5( XE::MemoryView val );

	MD5( const std::string & val );

public:
	MD5 & operator =( const MD5 & val );

	MD5 & operator =( XE::MemoryView val );

	MD5 & operator =( const std::string & val );

public:
	bool operator <( const MD5 & val ) const;

	bool operator <=( const MD5 & val ) const;

	bool operator >( const MD5 & val ) const;

	bool operator >=( const MD5 & val ) const;

	bool operator ==( const MD5 & val ) const;

	bool operator !=( const MD5 & val ) const;

public:
	std::string To16String() const;

	std::string To32String() const;

public:
	static MD5 From32String( const std::string & val );

private:
	void Hash( XE::MemoryView val );

private:
	char _Hash[33];
};
DECL_META_CLASS( XE_API, MD5 );

END_XE_NAMESPACE

namespace std
{
	inline std::string to_string( const XE::MD5 & _Val )
	{
		return _Val.To32String();
	}

	template<> struct equal_to<XE::MD5>
	{
		typedef XE::MD5 first_argument_type;
		typedef XE::MD5 second_argument_type;
		typedef bool result_type;

		bool operator()( const XE::MD5 & _Left, const XE::MD5 & _Right ) const
		{
			return ( _Left == _Right );
		}
	};

	template<> struct hash<XE::MD5>
	{
		typedef XE::MD5 argument_type;
		typedef XE::uint64 result_type;

		XE::uint64 operator()( const XE::MD5 & _Keyval ) const noexcept
		{
			return std::hash<std::string>()( _Keyval.To32String() );
		}
	};

}

struct MD5HashCompare
{
	static XE::uint64 hash( const XE::MD5 & a )
	{
		return std::hash<XE::MD5>()( a );
	}
	static bool equal( const XE::MD5 & a, const XE::MD5 & b )
	{
		return std::equal_to<XE::MD5>()( a, b );
	}
};


#endif // MD5_H__EF0EE087_0F95_41D9_956F_532BA1F954FA
