/*!
 * \file   String.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __STRING_H__56398C43_23FE_4F92_B5DF_985FB11D36BD
#define __STRING_H__56398C43_23FE_4F92_B5DF_985FB11D36BD

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API String
{
public:
	static const XE::uint64 npos = std::string::npos;

public:
	String();

	String( const char * val );

	String( const String& val );

	String( const std::string& val );

	~String();

public:
	String& operator = ( const String& val );

	String operator + ( bool  val ) const;

	String operator + ( XE::int8  val ) const;

	String operator + ( XE::int16  val ) const;

	String operator + ( XE::int32  val ) const;

	String operator + ( XE::int64  val ) const;

	String operator + ( XE::uint8  val ) const;

	String operator + ( XE::uint16 val ) const;

	String operator + ( XE::uint32 val ) const;

	String operator + ( XE::uint64 val ) const;

	String operator + ( XE::float32  val ) const;

	String operator + ( XE::float64 val ) const;

	String operator + ( const char * val ) const;

	String operator + ( const String& val ) const;

	String operator + ( const std::string& val ) const;

	bool operator < ( const char * val ) const;

	bool operator < ( const String& val ) const;

	bool operator < ( const std::string& val ) const;

	bool operator > ( const char * val ) const;

	bool operator > ( const String& val ) const;

	bool operator > ( const std::string& val ) const;

	bool operator <= ( const char * val ) const;

	bool operator <= ( const String& val ) const;

	bool operator <= ( const std::string& val ) const;

	bool operator >= ( const char * val ) const;

	bool operator >= ( const String& val ) const;

	bool operator >= ( const std::string& val ) const;

	bool operator == ( const char * val ) const;

	bool operator == ( const String& val ) const;

	bool operator == ( const std::string& val ) const;

	bool operator != ( const char * val ) const;

	bool operator != ( const String& val ) const;

	bool operator != ( const std::string& val ) const;

	char operator[]( XE::uint64 val ) const;

	operator const char *( ) const;

	operator const std::string&( ) const;

public:
	const char * ToCString() const;

	String& FromCString( const char * val );

	std::string ToStdString() const;

	String& FromStdString( const std::string& val );

public:
	void Clear();

public:
	bool Empty() const;

	XE::uint64 Size() const;

	XE::uint64 Count() const;

public:
	XE::uint64 Find( const String& val )const;

	bool Contains( const String& val ) const;

	String SubString( XE::uint64 offset = 0, XE::uint64 count = npos ) const;

private:
	std::string_view _View;
};

END_XE_NAMESPACE

namespace std
{
	inline std::string to_string( const XE::String& _Val )
	{
		return _Val.ToStdString();
	}

	template<> struct equal_to<XE::String>
	{
		typedef XE::String first_argument_type;
		typedef XE::String second_argument_type;
		typedef bool result_type;

		bool operator()( const XE::String& _Left, const XE::String& _Right ) const
		{
			return ( _Left.ToStdString() == _Right.ToStdString() );
		}
	};

	template<> struct hash<XE::String>
	{
		typedef XE::String argument_type;
		typedef XE::uint64 result_type;

		XE::uint64 operator()( const XE::String& _Keyval ) const noexcept
		{
			return std::hash<std::string>()( _Keyval.ToStdString() );
		}
	};

}

struct StringHashCompare
{
	static XE::uint64 hash( const XE::String& a )
	{
		return std::hash<XE::String>()( a );
	}
	static bool equal( const XE::String& a, const XE::String& b )
	{
		return std::equal_to<XE::String>()( a, b );
	}
};

XE_API XE::String operator + ( bool  val1, const XE::String& val2 );
XE_API XE::String operator + ( XE::int8  val1, const XE::String& val2 );
XE_API XE::String operator + ( XE::int16  val1, const XE::String& val2 );
XE_API XE::String operator + ( XE::int32  val1, const XE::String& val2 );
XE_API XE::String operator + ( XE::int64  val1, const XE::String& val2 );
XE_API XE::String operator + ( XE::uint8  val1, const XE::String& val2 );
XE_API XE::String operator + ( XE::uint16 val1, const XE::String& val2 );
XE_API XE::String operator + ( XE::uint32 val1, const XE::String& val2 );
XE_API XE::String operator + ( XE::uint64 val1, const XE::String& val2 );
XE_API XE::String operator + ( XE::float32  val1, const XE::String& val2 );
XE_API XE::String operator + ( XE::float64 val1, const XE::String& val2 );
XE_API XE::String operator + ( const char * val1, const XE::String& val2 );
XE_API XE::String operator + ( const std::string& val1, const XE::String& val2 );

#endif // __STRING_H__56398C43_23FE_4F92_B5DF_985FB11D36BD
