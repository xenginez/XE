#include "String.h"
#include "Singleton.hpp"
#include "StringUtils.h"

#include <tbb/concurrent_unordered_set.h>

USING_XE

class ConstStringPool : public XE::Singleton<ConstStringPool>
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
	static const std::string & Register( const std::string & val )
	{
		tbb::concurrent_unordered_set<std::string>::const_iterator it = Instance()->_Strings.find( val );

		if( it != Instance()->_Strings.end() )
		{
			return ( *it );
		}

		return ( *Instance()->_Strings.insert( val ).first );
	}

private:
	tbb::concurrent_unordered_set<std::string> _Strings;
};

String::String()
	:_View( ConstStringPool::Register( "" ) )
{

}

String::String( const char * val )
	: _View( ConstStringPool::Register( val ) )
{

}

String::String( const String & val )
	: _View( val._View )
{

}

String::String( const std::string & val )
	: _View( ConstStringPool::Register( val ) )
{

}

String::~String()
{

}

String & String::operator=( const String & val )
{
	_View = val._View;

	return *this;
}

String String::operator+( const std::string & val ) const
{
	return ToStdString() + val;
}

String String::operator+( const String & val ) const
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

bool String::operator!=( const String & val ) const
{
	return _View != val._View;
}

bool String::operator!=( const std::string & val ) const
{
	return *this != String( val );
}

bool String::operator==( const char * val ) const
{
	return *this == String( val );
}

bool String::operator==( const String & val ) const
{
	return _View == val._View;
}

bool String::operator==( const std::string & val ) const
{
	return *this == String( val );
}

bool String::operator>=( const char * val ) const
{
	return *this >= String( val );
}

bool String::operator>=( const String & val ) const
{
	return _View >= val._View;
}

bool String::operator>=( const std::string & val ) const
{
	return *this >= String( val );
}

bool String::operator<=( const char * val ) const
{
	return *this <= String( val );
}

bool String::operator<=( const String & val ) const
{
	return _View <= val._View;
}

bool String::operator<=( const std::string & val ) const
{
	return *this <= String( val );
}

bool String::operator>( const char * val ) const
{
	return *this > String( val );
}

bool String::operator>( const String & val ) const
{
	return _View > val._View;
}

bool String::operator>( const std::string & val ) const
{
	return *this > String( val );
}

bool String::operator<( const char * val ) const
{
	return *this < String( val );
}

bool String::operator<( const String & val ) const
{
	return _View < val._View;
}

bool String::operator<( const std::string & val ) const
{
	return *this < String( val );
}

char String::operator[]( XE::uint64 val ) const
{
	return _View[val];
}

String::operator const char * ( ) const
{
	return ToCString();
}

String::operator const std::string & ( ) const
{
	return ToStdString();
}

const char * String::ToCString() const
{
	return _View.data();
}

String & String::FromCString( const char * val )
{
	_View = ConstStringPool::Register( val );

	return *this;
}

std::string String::ToStdString() const
{
	return _View.data();
}

String & String::FromStdString( const std::string & val )
{
	_View = ConstStringPool::Register( val );
	return *this;
}

void String::Clear()
{
	_View = nullptr;
}

bool XE::String::Empty() const
{
	return _View.empty();
}

XE::uint64 String::Size() const
{
	return _View.size();
}

XE::uint64 XE::String::Count() const
{
	return StringUtils::UTF8CharacterCount( ToStdString() );
}

XE::uint64 String::Find( const String & val ) const
{
	return _View.find( val._View );
}

bool String::Contains( const String & val ) const
{
	return _View.find( val._View ) != npos;
}

String String::SubString( XE::uint64 offset /*= 0*/, XE::uint64 count /*= npos */ ) const
{
	String str;

	str._View = _View.substr( offset, count );

	return str;
}


String operator+( bool val1, const String & val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

String operator+( XE::int8 val1, const String & val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

String operator+( XE::int16 val1, const String & val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

String operator+( XE::int32 val1, const String & val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

String operator+( XE::int64 val1, const String & val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

String operator+( XE::uint8 val1, const String & val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

String operator+( XE::uint16 val1, const String & val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

String operator+( XE::uint32 val1, const String & val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

String operator+( XE::uint64 val1, const String & val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

String operator+( XE::float32 val1, const String & val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

String operator+( XE::float64 val1, const String & val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

String operator+( const char * val1, const String & val2 )
{
	return String( val1 ) + val2;
}

String operator+( const std::string & val1, const String & val2 )
{
	return String( val1 ) + val2;
}
