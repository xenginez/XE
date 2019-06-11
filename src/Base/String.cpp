#include "String.h"
#include "Singleton.hpp"

#include <tbb/concurrent_hash_map.h>

USING_XE

class StringPool : public Singleton<StringPool>
{
	friend Singleton<StringPool>;

public:
	typedef tbb::concurrent_hash_map<std::string, XE::uint64> hash_map;

private:
	StringPool()
	{
		Strings.insert( std::make_pair( "", 1 ) );
	}

	~StringPool()
	{
	}

public:
	static const std::string * Register( const std::string& val )
	{
		hash_map::accessor it;

		if ( This()->Strings.find( it, val ) )
		{
			it->second++;
			return &it->first;
		}

		This()->Strings.insert( it, std::make_pair( val, 1 ) );
		return &it->first;
	}

	static void Unregister( const std::string * val )
	{
		hash_map::accessor it;

		if ( This()->Strings.find( it, *val ) )
		{
			it->second--;

			if ( it->second == 0 )
			{
				This()->Strings.erase( it );
			}
		}
	}

private:
	hash_map Strings;
};

String::String()
	:_String(StringPool::Register(""))
{

}

String::String( const char * val )
	: _String( StringPool::Register( val ) )
{

}

String::String( const String& val )
	: _String( StringPool::Register( val.ToStdString() ) )
{

}

String::String( const std::string& val )
	: _String( StringPool::Register( val ) )
{

}

String::~String()
{
	if ( _String )
	{
		StringPool::Unregister( _String );
	}
}

String& String::operator+=( const std::string& val )
{
	*this = ToStdString() + val;

	return *this;
}

String& String::operator=( const String& val )
{
	if ( _String )
	{
		StringPool::Unregister( _String );
	}

	_String = StringPool::Register( val.ToStdString() );

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
	return (*this += (val ? "true" : "false"));
}

String String::operator+( const std::string& val ) const
{
	return ToStdString() + val;
}

String String::operator+( const String& val ) const
{
	return *_String + val.ToStdString();
}

String String::operator+( const char * val ) const
{
	return ToStdString() + val;
}

String String::operator+( XE::float64 val ) const
{
	return *this + std::to_string( val );
}

String String::operator+( XE::float32 val ) const
{
	return *this + std::to_string( val );
}

String String::operator+( XE::uint64 val ) const
{
	return *this + std::to_string( val );
}

String String::operator+( XE::uint32 val ) const
{
	return *this + std::to_string( val );
}

String String::operator+( XE::uint16 val ) const
{
	return *this + std::to_string( val );
}

String String::operator+( XE::uint8 val ) const
{
	return *this + std::to_string( val );
}

String String::operator+( XE::int64 val ) const
{
	return *this + std::to_string( val );
}

String String::operator+( XE::int32 val ) const
{
	return *this + std::to_string( val );
}

String String::operator+( XE::int16 val ) const
{
	return *this + std::to_string( val );
}

String String::operator+( XE::int8 val ) const
{
	return *this + std::to_string( val );
}

String String::operator+( bool val ) const
{
	return (*this + (val ? "true" : "false"));
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
	return _String >= val._String;
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
	return _String <= val._String;
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
	return _String > val._String;
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
	return _String < val._String;
}

bool String::operator<( const std::string& val ) const
{
	return *this < String( val );
}

char String::operator[]( XE::uint64 val ) const
{
	return _String->at( val );
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
	if ( *_String != "" )
	{
		StringPool::Unregister( _String );
	}

	_String = StringPool::Register( "" );
}

XE::uint64 String::Size() const
{
	return _String->size();
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
	return String() + val1 + val2;
}

String operator+( XE::int8 val1, const String& val2 )
{
	return String() + val1 + val2;
}

String operator+( XE::int16 val1, const String& val2 )
{
	return String() + val1 + val2;
}

String operator+( XE::int32 val1, const String& val2 )
{
	return String() + val1 + val2;
}

String operator+( XE::int64 val1, const String& val2 )
{
	return String() + val1 + val2;
}

String operator+( XE::uint8 val1, const String& val2 )
{
	return String() + val1 + val2;
}

String operator+( XE::uint16 val1, const String& val2 )
{
	return String() + val1 + val2;
}

String operator+( XE::uint32 val1, const String& val2 )
{
	return String() + val1 + val2;
}

String operator+( XE::uint64 val1, const String& val2 )
{
	return String() + val1 + val2;
}

String operator+( XE::float32 val1, const String& val2 )
{
	return String() + val1 + val2;
}

String operator+( XE::float64 val1, const String& val2 )
{
	return String() + val1 + val2;
}

String operator+( const char * val1, const String& val2 )
{
	return String( val1 ) + val2;
}

String operator+( const std::string& val1, const String& val2 )
{
	return String( val1 ) + val2;
}
