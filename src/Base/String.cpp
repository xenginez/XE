#include "String.h"
#include "Singleton.hpp"
#include "StringUtils.h"

#include <tbb/concurrent_unordered_set.h>



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
	const std::string & Register( const std::string & val )
	{
		tbb::concurrent_unordered_set<std::string>::const_iterator it = Instance()->_Strings.find( val );

		if( it != _Strings.end() )
		{
			return ( *it );
		}

		return ( *( _Strings.insert( val ).first ) );
	}

private:
	tbb::concurrent_unordered_set<std::string> _Strings;
};

XE::String::String()
	:_View( ConstStringPool::Instance()->Register( "" ) )
{

}

XE::String::String( const char * val )
	: _View( ConstStringPool::Instance()->Register( val ) )
{

}

XE::String::String( const String & val )
	: _View( val._View )
{

}

XE::String::String( const std::string & val )
	: _View( ConstStringPool::Instance()->Register( val ) )
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
	return ToStdString() + std::to_string( val );
}

XE::String XE::String::operator+( XE::float32 val ) const
{
	return ToStdString() + std::to_string( val );
}

XE::String XE::String::operator+( XE::uint64 val ) const
{
	return ToStdString() + std::to_string( val );
}

XE::String XE::String::operator+( XE::uint32 val ) const
{
	return ToStdString() + std::to_string( val );
}

XE::String XE::String::operator+( XE::uint16 val ) const
{
	return ToStdString() + std::to_string( val );
}

XE::String XE::String::operator+( XE::uint8 val ) const
{
	return ToStdString() + std::to_string( val );
}

XE::String XE::String::operator+( XE::int64 val ) const
{
	return ToStdString() + std::to_string( val );
}

XE::String XE::String::operator+( XE::int32 val ) const
{
	return ToStdString() + std::to_string( val );
}

XE::String XE::String::operator+( XE::int16 val ) const
{
	return ToStdString() + std::to_string( val );
}

XE::String XE::String::operator+( XE::int8 val ) const
{
	return ToStdString() + std::to_string( val );
}

XE::String XE::String::operator+( bool val ) const
{
	return ToStdString() + std::to_string( val );
}

bool XE::String::operator!=( const char * val ) const
{
	return *this != String( val );
}

bool XE::String::operator!=( const XE::String & val ) const
{
	return _View != val._View;
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
	return _View == val._View;
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
	return _View >= val._View;
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
	return _View <= val._View;
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
	return _View > val._View;
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
	return _View < val._View;
}

bool XE::String::operator<( const std::string & val ) const
{
	return *this < String( val );
}

char XE::String::operator[]( XE::uint64 val ) const
{
	return _View[val];
}

XE::String::operator const char * () const
{
	return _View.data();
}

XE::String::operator std::string ( ) const
{
	return ConstStringPool::Instance()->Register( _View.data() );
}

XE::String::operator const std::string & () const
{
	return ConstStringPool::Instance()->Register( _View.data() );
}

XE::String::operator const std::string_view & () const
{
	return _View;
}

const char * XE::String::ToCString() const
{
	return _View.data();
}

XE::String & XE::String::FromCString( const char * val )
{
	_View = ConstStringPool::Instance()->Register( val );

	return *this;
}

std::string XE::String::ToStdString() const
{
	return _View.data();
}

XE::String & XE::String::FromStdString( const std::string & val )
{
	_View = ConstStringPool::Instance()->Register( val );
	return *this;
}

void XE::String::Clear()
{
	_View = nullptr;
}

bool XE::String::Empty() const
{
	return _View.empty();
}

XE::uint64 XE::String::Size() const
{
	return _View.size();
}

XE::uint64 XE::String::Count() const
{
	return StringUtils::UTF8CharacterCount( ToStdString() );
}

XE::uint64 XE::String::Find( const XE::String & val ) const
{
	return _View.find( val._View );
}

bool XE::String::Contains( const XE::String & val ) const
{
	return _View.find( val._View ) != npos;
}

XE::String XE::String::SubString( XE::uint64 offset /*= 0*/, XE::uint64 count /*= npos */ ) const
{
	XE::String str;

	str._View = _View.substr( offset, count );

	return str;
}


XE::String operator+( bool val1, const XE::String & val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

XE::String operator+( XE::int8 val1, const XE::String & val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

XE::String operator+( XE::int16 val1, const XE::String & val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

XE::String operator+( XE::int32 val1, const XE::String & val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

XE::String operator+( XE::int64 val1, const XE::String & val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

XE::String operator+( XE::uint8 val1, const XE::String & val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

XE::String operator+( XE::uint16 val1, const XE::String & val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

XE::String operator+( XE::uint32 val1, const XE::String & val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

XE::String operator+( XE::uint64 val1, const XE::String & val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

XE::String operator+( XE::float32 val1, const XE::String & val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

XE::String operator+( XE::float64 val1, const XE::String & val2 )
{
	return std::to_string( val1 ) + val2.ToStdString();
}

XE::String operator+( const char * val1, const XE::String & val2 )
{
	return XE::String( val1 ) + val2;
}

XE::String operator+( const std::string & val1, const XE::String & val2 )
{
	return XE::String( val1 ) + val2;
}
