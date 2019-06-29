#include "String.h"
#include "Singleton.hpp"
#include "StringUtils.h"

#include <tbb/concurrent_unordered_set.h>

USING_XE

class ConstStringPool : public Singleton<ConstStringPool>
{
public:
	ConstStringPool()
	{
		_Strings.insert( "" );
		_Strings.insert( "1" );
		_Strings.insert( "2" );
		_Strings.insert( "3" );
		_Strings.insert( "4" );
		_Strings.insert( "5" );
		_Strings.insert( "6" );
		_Strings.insert( "7" );
		_Strings.insert( "8" );
		_Strings.insert( "9" );
		_Strings.insert( "0" );
	}

	~ConstStringPool()
	{
	}

public:
	static const std::string * Register( const std::string& val )
	{
		tbb::concurrent_unordered_set<std::string>::const_iterator it = This()->_Strings.find( val );

		if( it != This()->_Strings.end() )
		{
			return &( *it );
		}

		return &( *This()->_Strings.insert( val ).first );
	}

private:
	tbb::concurrent_unordered_set<std::string> _Strings;
};

String::String()
	:_String( ConstStringPool::Register( "" ) )
{

}

String::String( const char * val )
	: _String( ConstStringPool::Register( val ) )
{

}

String::String( const String& val )
	: _String( val._String )
{

}

String::String( const std::string& val )
	: _String( ConstStringPool::Register( val ) )
{

}

String::~String()
{

}

String& String::operator+=( const std::string& val )
{
	*this = ToStdString() + val;

	return *this;
}

String& String::operator=( const String& val )
{
	_String = val._String;

	return *this;
}

String& String::operator+=( const char * val )
{
	*this = ToStdString() + val;

	return *this;
}

String& String::operator+=( const String& val )
{
	*this = ( *_String ) + val.ToStdString();

	return *this;
}

String& String::operator+=( XE::float64 val )
{
	return *this += std::to_string( val );
}

String& String::operator+=( XE::float32 val )
{
	return *this += std::to_string( val );
}

String& String::operator+=( XE::uint64 val )
{
	return *this += std::to_string( val );
}

String& String::operator+=( XE::uint32 val )
{
	return *this += std::to_string( val );
}

String& String::operator+=( XE::uint16 val )
{
	return *this += std::to_string( val );
}

String& String::operator+=( XE::uint8 val )
{
	return *this += std::to_string( val );
}

String& String::operator+=( XE::int64 val )
{
	return *this += std::to_string( val );
}

String& String::operator+=( XE::int32 val )
{
	return *this += std::to_string( val );
}

String& String::operator+=( XE::int16 val )
{
	return *this += std::to_string( val );
}

String& String::operator+=( XE::int8 val )
{
	return *this += std::to_string( val );
}

String& String::operator+=( bool val )
{
	return *this += std::to_string( val );
}

String String::operator+( const std::string& val ) const
{
	return ToStdString() + val;
}

String String::operator+( const String& val ) const
{
	return ToStdString() + val.ToStdString();
}

String String::operator+( const char * val ) const
{
	return ToStdString() + val;
}

String String::operator+( XE::float64 val ) const
{
	return ToStdString() + std::to_string( val );
}

String String::operator+( XE::float32 val ) const
{
	return ToStdString() + std::to_string( val );
}

String String::operator+( XE::uint64 val ) const
{
	return ToStdString() + std::to_string( val );
}

String String::operator+( XE::uint32 val ) const
{
	return ToStdString() + std::to_string( val );
}

String String::operator+( XE::uint16 val ) const
{
	return ToStdString() + std::to_string( val );
}

String String::operator+( XE::uint8 val ) const
{
	return ToStdString() + std::to_string( val );
}

String String::operator+( XE::int64 val ) const
{
	return ToStdString() + std::to_string( val );
}

String String::operator+( XE::int32 val ) const
{
	return ToStdString() + std::to_string( val );
}

String String::operator+( XE::int16 val ) const
{
	return ToStdString() + std::to_string( val );
}

String String::operator+( XE::int8 val ) const
{
	return ToStdString() + std::to_string( val );
}

String String::operator+( bool val ) const
{
	return ToStdString() + std::to_string( val );
}

bool String::operator!=( const char * val ) const
{
	return *this != String( val );
}

bool String::operator!=( const String& val ) const
{
	return _String != val._String;
}

bool String::operator!=( const std::string& val ) const
{
	return *this != String( val );
}

bool String::operator==( const char * val ) const
{
	return *this == String( val );
}

bool String::operator==( const String& val ) const
{
	return _String == val._String;
}

bool String::operator==( const std::string& val ) const
{
	return *this == String( val );
}

bool String::operator>=( const char * val ) const
{
	return *this >= String( val );
}

bool String::operator>=( const String& val ) const
{
	return ( *_String ) >= ( *val._String );
}

bool String::operator>=( const std::string& val ) const
{
	return *this >= String( val );
}

bool String::operator<=( const char * val ) const
{
	return *this <= String( val );
}

bool String::operator<=( const String& val ) const
{
	return ( *_String ) <= ( *val._String );
}

bool String::operator<=( const std::string& val ) const
{
	return *this <= String( val );
}

bool String::operator>( const char * val ) const
{
	return *this > String( val );
}

bool String::operator>( const String& val ) const
{
	return ( *_String ) > ( *val._String );
}

bool String::operator>( const std::string& val ) const
{
	return *this > String( val );
}

bool String::operator<( const char * val ) const
{
	return *this < String( val );
}

bool String::operator<( const String& val ) const
{
	return ( *_String ) < ( *val._String );
}

bool String::operator<( const std::string& val ) const
{
	return *this < String( val );
}

char String::operator[]( XE::uint64 val ) const
{
	return ( *_String )[val];
}

String::operator const char *( ) const
{
	return ToCString();
}

String::operator const std::string&( ) const
{
	return ToStdString();
}

const char * String::ToCString() const
{
	return _String->c_str();
}

String& String::FromCString( const char * val )
{
	return *this += val;
}

const std::string& String::ToStdString() const
{
	return *_String;
}

String& String::FromStdString( const std::string& val )
{
	return *this += val;
}

void String::Clear()
{
	_String = ConstStringPool::Register( "" );
}

bool XE::String::Empty() const
{
	return _String->empty();
}

XE::uint64 String::Size() const
{
	return _String->size();
}

XE::uint64 XE::String::Count() const
{
	return StringUtils::UTF8CharacterCount( ToStdString() );
}

XE::uint64 String::Find( const String& val ) const
{
	return _String->find( *val._String );
}

bool String::Contains( const String& val ) const
{
	return _String->find( *val._String ) != npos;
}

String String::SubString( XE::uint64 offset /*= 0*/, XE::uint64 count /*= npos */ ) const
{
	return _String->substr( offset, count );
}


String operator+( bool val1, const String& val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

String operator+( XE::int8 val1, const String& val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

String operator+( XE::int16 val1, const String& val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

String operator+( XE::int32 val1, const String& val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

String operator+( XE::int64 val1, const String& val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

String operator+( XE::uint8 val1, const String& val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

String operator+( XE::uint16 val1, const String& val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

String operator+( XE::uint32 val1, const String& val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

String operator+( XE::uint64 val1, const String& val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

String operator+( XE::float32 val1, const String& val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

String operator+( XE::float64 val1, const String& val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

String operator+( const char * val1, const String& val2 )
{
	return String( val1 ) + val2;
}

String operator+( const std::string& val1, const String& val2 )
{
	return String( val1 ) + val2;
}
