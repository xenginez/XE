#include "IFramework.h"

XE::IFrameworkPtr XE::IFramework::_CurrentFramework = nullptr;

USING_XE

BEG_META( IFramework )
END_META()

IFramework::IFramework()
{
	XE_ASSERT( _CurrentFramework == nullptr && "framework is not unique!" );

	_CurrentFramework = this;
}

IFramework::~IFramework()
{
	_CurrentFramework = nullptr;
}

XE::IFrameworkPtr XE::IFramework::GetCurrentFramework()
{
	return _CurrentFramework;
}

bool IFramework::GetBool( const String & key, bool def )
{
	String s = GetValue( key );

	return s == "" ? def : s == "true";
}

void IFramework::SetBool( const String & key, bool val )
{
	SetValue( key, val ? "true" : "false" );
}

XE::int8 IFramework::GetInt8( const String & key, XE::int8 def )
{
	String s = GetValue( key );

	return s == "" ? def : std::stoi( s );
}

void IFramework::SetInt8( const String & key, XE::int8 val )
{
	SetValue( key, std::to_string( val ) );
}

XE::int16 IFramework::GetInt16( const String & key, XE::int16 def )
{
	String s = GetValue( key );

	return s == "" ? def : std::stoi( s );
}

void IFramework::SetInt16( const String & key, XE::int16 val )
{
	SetValue( key, std::to_string( val ) );
}

XE::int32 IFramework::GetInt32( const String & key, XE::int32 def )
{
	String s = GetValue( key );

	return s == "" ? def : std::stoi( s );
}

void IFramework::SetInt32( const String & key, XE::int32 val )
{
	SetValue( key, std::to_string( val ) );
}

XE::int64 IFramework::GetInt64( const String & key, XE::int64 def )
{
	String s = GetValue( key );

	return s == "" ? def : std::stoll( s );
}

void IFramework::SetInt64( const String & key, XE::int64 val )
{
	SetValue( key, std::to_string( val ) );
}

XE::uint8 IFramework::GetUInt8( const String & key, XE::uint8 def )
{
	String s = GetValue( key );

	return s == "" ? def : ( XE::uint8 ) std::stoul( s );
}

void IFramework::SetUInt8( const String & key, XE::uint8 val )
{
	SetValue( key, std::to_string( val ) );
}

XE::uint16 IFramework::GetUInt16( const String & key, XE::uint16 def )
{
	String s = GetValue( key );

	return s == "" ? def : ( XE::uint16 ) std::stoul( s );
}

void IFramework::SetUInt16( const String & key, XE::uint16 val )
{
	SetValue( key, std::to_string( val ) );
}

XE::uint32 IFramework::GetUInt32( const String & key, XE::uint32 def )
{
	String s = GetValue( key );

	return s == "" ? def : std::stoul( s );
}

void IFramework::SetUInt32( const String & key, XE::uint32 val )
{
	SetValue( key, std::to_string( val ) );
}

XE::uint64 IFramework::GetUInt64( const String & key, XE::uint64 def )
{
	String s = GetValue( key );

	return s == "" ? def : std::stoull( s );
}

void IFramework::SetUInt64( const String & key, XE::uint64 val )
{
	SetValue( key, std::to_string( val ) );
}

XE::float32 IFramework::GetFloat32( const String & key, XE::float32 def )
{
	String s = GetValue( key );

	return s == "" ? def : std::stof( s );
}

void IFramework::SetFloat32( const String & key, XE::float32 val )
{
	SetValue( key, std::to_string( val ) );
}

XE::float64 IFramework::GetFloat64( const String & key, XE::float64 def )
{
	String s = GetValue( key );

	return s == "" ? def : std::stod( s );
}

void IFramework::SetFloat64( const String & key, XE::float64 val )
{
	SetValue( key, std::to_string( val ) );
}

String IFramework::GetString( const String & key, const String & def )
{
	String s = GetValue( key );

	return s == "" ? def : s;
}

void IFramework::SetString( const String & key, const String & val )
{
	SetValue( key, val );
}
