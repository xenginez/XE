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

class BASE_API String
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

	String& operator += ( bool val );

	String& operator += ( int8  val );

	String& operator += ( int16  val );

	String& operator += ( int32  val );

	String& operator += ( int64  val );

	String& operator += ( uint8  val );

	String& operator += ( uint16 val );

	String& operator += ( uint32 val );

	String& operator += ( uint64 val );

	String& operator += ( float  val );

	String& operator += ( double val );

	String& operator += ( const char * val );

	String& operator += ( const String& val );

	String& operator += ( const std::string& val );

	String operator + ( bool  val ) const;

	String operator + ( int8  val ) const;

	String operator + ( int16  val ) const;

	String operator + ( int32  val ) const;

	String operator + ( int64  val ) const;

	String operator + ( uint8  val ) const;

	String operator + ( uint16 val ) const;

	String operator + ( uint32 val ) const;

	String operator + ( uint64 val ) const;

	String operator + ( float  val ) const;

	String operator + ( double val ) const;

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

	const std::string& ToStdString() const;

	String& FromStdString( const std::string& val );

public:
	void Clear();

public:
	XE::uint64 Size() const;

	XE::uint64 Find( const String& val )const;

	bool Contains( const String& val ) const;

	String SubString( XE::uint64 offset = 0, XE::uint64 count = npos ) const;

private:
	const std::string * _String;
};

END_XE_NAMESAPCE

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
			return ( _Left.ToCString() == _Right.ToCString() );
		}
	};

	template<> struct hash<XE::String>
	{
		typedef XE::String argument_type;
		typedef XE::uint64 result_type;

		XE::uint64 operator()( const XE::String& _Keyval ) const noexcept
		{
			return (XE::uint64)_Keyval.ToCString();
		}
	};

}

struct BASE_API StringHashCompare
{
	static XE::uint64 hash( const XE::String& a )
	{
		return (XE::uint64)a.ToCString();
	}
	static bool equal( const XE::String& a, const XE::String& b )
	{
		return a == b;
	}
};

BASE_API XE::String operator + ( bool  val1, const XE::String& val2 );
BASE_API XE::String operator + ( XE::int8  val1, const XE::String& val2 );
BASE_API XE::String operator + ( XE::int16  val1, const XE::String& val2 );
BASE_API XE::String operator + ( XE::int32  val1, const XE::String& val2 );
BASE_API XE::String operator + ( XE::int64  val1, const XE::String& val2 );
BASE_API XE::String operator + ( XE::uint8  val1, const XE::String& val2 );
BASE_API XE::String operator + ( XE::uint16 val1, const XE::String& val2 );
BASE_API XE::String operator + ( XE::uint32 val1, const XE::String& val2 );
BASE_API XE::String operator + ( XE::uint64 val1, const XE::String& val2 );
BASE_API XE::String operator + ( float  val1, const XE::String& val2 );
BASE_API XE::String operator + ( double val1, const XE::String& val2 );
BASE_API XE::String operator + ( const char * val1, const XE::String& val2 );
BASE_API XE::String operator + ( const std::string& val1, const XE::String& val2 );

#endif // __STRING_H__56398C43_23FE_4F92_B5DF_985FB11D36BD
