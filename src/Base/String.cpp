#include "String.h"
#include "Singleton.hpp"
#include "StringUtils.h"

XE::String::String()
{

}

XE::String::String( const char * val )
	: _View( std::make_shared< std::string >( val ) )
{

}

XE::String::String( const String & val )
	: _View( val._View )
{

}

XE::String::String( std::string && val )
	: _View( std::make_shared< std::string >( std::forward< std::string >( val ) ) )
{

}

XE::String::String( const std::string & val )
	: _View( std::make_shared< std::string >( val ) )
{

}

XE::String::~String()
{

}

XE::String & XE::String::operator=( const XE::String & val )
{
	_View = val._View;

	return *this;
}

XE::String XE::String::operator+( const std::string & val ) const
{
	return ToStdString() + val;
}

XE::String XE::String::operator+( const XE::String & val ) const
{
	return ToStdString() + val.ToStdString();
}

XE::String XE::String::operator+( const char * val ) const
{
	return ToStdString() + val;
}

XE::String XE::String::operator+( XE::float64 val ) const
{
	return ToStdString() + XE::ToString( val );
}

XE::String XE::String::operator+( XE::float32 val ) const
{
	return ToStdString() + XE::ToString( val );
}

XE::String XE::String::operator+( XE::uint64 val ) const
{
	return ToStdString() + XE::ToString( val );
}

XE::String XE::String::operator+( XE::uint32 val ) const
{
	return ToStdString() + XE::ToString( val );
}

XE::String XE::String::operator+( XE::uint16 val ) const
{
	return ToStdString() + XE::ToString( val );
}

XE::String XE::String::operator+( XE::uint8 val ) const
{
	return ToStdString() + XE::ToString( val );
}

XE::String XE::String::operator+( XE::int64 val ) const
{
	return ToStdString() + XE::ToString( val );
}

XE::String XE::String::operator+( XE::int32 val ) const
{
	return ToStdString() + XE::ToString( val );
}

XE::String XE::String::operator+( XE::int16 val ) const
{
	return ToStdString() + XE::ToString( val );
}

XE::String XE::String::operator+( XE::int8 val ) const
{
	return ToStdString() + XE::ToString( val );
}

XE::String XE::String::operator+( bool val ) const
{
	return ToStdString() + XE::ToString( val );
}

bool XE::String::operator!=( const char * val ) const
{
	return *this != String( val );
}

bool XE::String::operator!=( const XE::String & val ) const
{
	return *_View != *val._View;
}

bool XE::String::operator!=( const std::string & val ) const
{
	return *this != String( val );
}

bool XE::String::operator==( const char * val ) const
{
	return *this == String( val );
}

bool XE::String::operator==( const XE::String & val ) const
{
	return *_View == *val._View;
}

bool XE::String::operator==( const std::string & val ) const
{
	return *this == String( val );
}

bool XE::String::operator>=( const char * val ) const
{
	return *this >= String( val );
}

bool XE::String::operator>=( const XE::String & val ) const
{
	return *_View >= *val._View;
}

bool XE::String::operator>=( const std::string & val ) const
{
	return *this >= String( val );
}

bool XE::String::operator<=( const char * val ) const
{
	return *this <= String( val );
}

bool XE::String::operator<=( const XE::String & val ) const
{
	return *_View <= *val._View;
}

bool XE::String::operator<=( const std::string & val ) const
{
	return *this <= String( val );
}

bool XE::String::operator>( const char * val ) const
{
	return *this > String( val );
}

bool XE::String::operator>( const XE::String & val ) const
{
	return *_View > *val._View;
}

bool XE::String::operator>( const std::string & val ) const
{
	return *this > String( val );
}

bool XE::String::operator<( const char * val ) const
{
	return *this < String( val );
}

bool XE::String::operator<( const XE::String & val ) const
{
	return *_View < *val._View;
}

bool XE::String::operator<( const std::string & val ) const
{
	return *this < String( val );
}

char XE::String::operator[]( XE::uint64 val ) const
{
	return _View->at( val );
}

XE::String::operator const char * () const
{
	return _View->c_str();
}

XE::String::operator std::string_view() const
{
	return std::string_view( *_View );
}

XE::String::operator const std::string & () const
{
	return *_View;
}

const char * XE::String::ToCString() const
{
	return _View->c_str();
}

std::string XE::String::ToStdString() const
{
	return *_View;
}

void XE::String::Clear()
{
	_View = nullptr;
}

bool XE::String::Empty() const
{
	return _View == nullptr;
}

XE::uint64 XE::String::Size() const
{
	return _View->size();
}

XE::uint64 XE::String::Count() const
{
	return StringUtils::UTF8CharacterCount( ToStdString() );
}

XE::uint64 XE::String::Find( const XE::String & val ) const
{
	return _View->find( *val._View );
}

bool XE::String::Contains( const XE::String & val ) const
{
	return _View->find( *val._View ) != npos;
}

XE::String XE::String::SubString( XE::uint64 offset /*= 0*/, XE::uint64 count /*= npos */ ) const
{
	XE::String str( _View->substr( offset, count ) );

	return str;
}


XE::String operator+( bool val1, const XE::String & val2 )
{
	return XE::ToString( val1 ) + val2.ToStdString();
}

XE::String operator+( XE::int8 val1, const XE::String & val2 )
{
	return XE::ToString( val1 ) + val2.ToStdString();
}

XE::String operator+( XE::int16 val1, const XE::String & val2 )
{
	return XE::ToString( val1 ) + val2.ToStdString();
}

XE::String operator+( XE::int32 val1, const XE::String & val2 )
{
	return XE::ToString( val1 ) + val2.ToStdString();
}

XE::String operator+( XE::int64 val1, const XE::String & val2 )
{
	return XE::ToString( val1 ) + val2.ToStdString();
}

XE::String operator+( XE::uint8 val1, const XE::String & val2 )
{
	return XE::ToString( val1 ) + val2.ToStdString();
}

XE::String operator+( XE::uint16 val1, const XE::String & val2 )
{
	return XE::ToString( val1 ) + val2.ToStdString();
}

XE::String operator+( XE::uint32 val1, const XE::String & val2 )
{
	return XE::ToString( val1 ) + val2.ToStdString();
}

XE::String operator+( XE::uint64 val1, const XE::String & val2 )
{
	return XE::ToString( val1 ) + val2.ToStdString();
}

XE::String operator+( XE::float32 val1, const XE::String & val2 )
{
	return XE::ToString( val1 ) + val2.ToStdString();
}

XE::String operator+( XE::float64 val1, const XE::String & val2 )
{
	return XE::ToString( val1 ) + val2.ToStdString();
}

XE::String operator+( const char * val1, const XE::String & val2 )
{
	return XE::String( val1 + val2.ToStdString() );
}

XE::String operator+( const std::string & val1, const XE::String & val2 )
{
	return XE::String( val1 + val2.ToStdString() );
}
