#include "IFramework.h"

#include <rapidjson/document.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/ostreamwrapper.h>

XE::IFrameworkPtr XE::IFramework::_CurrentFramework = nullptr;

BEG_META( XE::IFramework )
END_META()

XE::IFramework::IFramework()
{
	XE_ASSERT( _CurrentFramework == nullptr && "framework is not unique!" );

	_CurrentFramework = this;
}

XE::IFramework::~IFramework()
{
	_CurrentFramework = nullptr;
}

XE::IFrameworkPtr XE::IFramework::GetCurrentFramework()
{
	return _CurrentFramework;
}

bool XE::IFramework::GetBool( const String & key, bool def )
{
	String s = GetValue( key );

	return s.empty() ? def : s == "true";
}

void XE::IFramework::SetBool( const String & key, bool val )
{
	SetValue( key, val ? "true" : "false" );
}

XE::int8 XE::IFramework::GetInt8( const String & key, XE::int8 def )
{
	String s = GetValue( key );

	return s.empty() ? def : std::stoi( s.c_str() );
}

void XE::IFramework::SetInt8( const String & key, XE::int8 val )
{
	SetValue( key, XE::ToString( val ) );
}

XE::int16 XE::IFramework::GetInt16( const String & key, XE::int16 def )
{
	String s = GetValue( key );

	return s.empty() ? def : std::stoi( s.c_str() );
}

void XE::IFramework::SetInt16( const String & key, XE::int16 val )
{
	SetValue( key, XE::ToString( val ) );
}

XE::int32 XE::IFramework::GetInt32( const String & key, XE::int32 def )
{
	String s = GetValue( key );

	return s.empty() ? def : std::stoi( s.c_str() );
}

void XE::IFramework::SetInt32( const String & key, XE::int32 val )
{
	SetValue( key, XE::ToString( val ) );
}

XE::int64 XE::IFramework::GetInt64( const String & key, XE::int64 def )
{
	String s = GetValue( key );

	return s.empty() ? def : std::stoll( s.c_str() );
}

void XE::IFramework::SetInt64( const String & key, XE::int64 val )
{
	SetValue( key, XE::ToString( val ) );
}

XE::uint8 XE::IFramework::GetUInt8( const String & key, XE::uint8 def )
{
	String s = GetValue( key );

	return s.empty() ? def : ( XE::uint8 ) std::stoul( s.c_str() );
}

void XE::IFramework::SetUInt8( const String & key, XE::uint8 val )
{
	SetValue( key, XE::ToString( val ) );
}

XE::uint16 XE::IFramework::GetUInt16( const String & key, XE::uint16 def )
{
	String s = GetValue( key );

	return s.empty() ? def : ( XE::uint16 ) std::stoul( s.c_str() );
}

void XE::IFramework::SetUInt16( const String & key, XE::uint16 val )
{
	SetValue( key, XE::ToString( val ) );
}

XE::uint32 XE::IFramework::GetUInt32( const String & key, XE::uint32 def )
{
	String s = GetValue( key );

	return s.empty() ? def : std::stoul( s.c_str() );
}

void XE::IFramework::SetUInt32( const String & key, XE::uint32 val )
{
	SetValue( key, XE::ToString( val ) );
}

XE::uint64 XE::IFramework::GetUInt64( const String & key, XE::uint64 def )
{
	String s = GetValue( key );

	return s.empty() ? def : std::stoull( s.c_str() );
}

void XE::IFramework::SetUInt64( const String & key, XE::uint64 val )
{
	SetValue( key, XE::ToString( val ) );
}

XE::float32 XE::IFramework::GetFloat32( const String & key, XE::float32 def )
{
	String s = GetValue( key );

	return s.empty() ? def : std::stof( s.c_str() );
}

void XE::IFramework::SetFloat32( const String & key, XE::float32 val )
{
	SetValue( key, XE::ToString( val ) );
}

XE::float64 XE::IFramework::GetFloat64( const String & key, XE::float64 def )
{
	String s = GetValue( key );

	return s.empty() ? def : std::stod( s.c_str() );
}

void XE::IFramework::SetFloat64( const String & key, XE::float64 val )
{
	SetValue( key, XE::ToString( val ) );
}

XE::String XE::IFramework::GetString( const String & key, const String & def )
{
	String s = GetValue( key );

	return s.empty() ? def : s;
}

void XE::IFramework::SetString( const String & key, const String & val )
{
	SetValue( key, val );
}

void XE::IFramework::SetStringArray( const String & key, const Array< String > & val )
{
	rapidjson::Document doc;

	rapidjson::Value & strs = doc.SetArray();

	for( size_t i = 0; i < val.size(); i++ )
	{
		strs.PushBack( rapidjson::StringRef( val[i].c_str() ), doc.GetAllocator() );
	}

	std::stringstream str;

	rapidjson::OStreamWrapper wrapper( str );
	rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer( wrapper );
	doc.Accept( writer );

	SetValue( key, str.str() );
}

XE::Array< XE::String > XE::IFramework::GetStringArray( const String & key, const Array< String > & def /*= Array< String >() */ )
{
	XE::Array< XE::String > res;

	rapidjson::Document doc;
	doc.Parse( GetValue( key ).c_str() );

	auto strs = doc.GetArray();

	for( size_t i = 0; i < strs.Size(); i++ )
	{
		res.push_back( strs[i].GetString() );
	}

	return res;
}
