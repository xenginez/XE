#include "IConfigService.h"

USING_XE

BEG_META( IConfigService )
END_META()

XE::IConfigService::IConfigService()
{

}

XE::IConfigService::~IConfigService()
{

}

bool IConfigService::GetBool( const String & key, bool def ) const
{
	String s = GetValue( key );

	return s == "" ? def : s == "true";
}

void IConfigService::SetBool( const String & key, bool val )
{
	SetValue( key, val ? "true" : "false" );
}

XE::int8 IConfigService::GetInt8( const String & key, XE::int8 def ) const
{
	String s = GetValue( key );

	return s == "" ? def : std::stoi( s );
}

void IConfigService::SetInt8( const String & key, XE::int8 val )
{
	SetValue( key, std::to_string( val ) );
}

XE::int16 IConfigService::GetInt16( const String & key, XE::int16 def ) const
{
	String s = GetValue( key );

	return s == "" ? def : std::stoi( s );
}

void IConfigService::SetInt16( const String & key, XE::int16 val )
{
	SetValue( key, std::to_string( val ) );
}

XE::int32 IConfigService::GetInt32( const String & key, XE::int32 def ) const
{
	String s = GetValue( key );

	return s == "" ? def : std::stoi( s );
}

void IConfigService::SetInt32( const String & key, XE::int32 val )
{
	SetValue( key, std::to_string( val ) );
}

XE::int64 IConfigService::GetInt64( const String & key, XE::int64 def ) const
{
	String s = GetValue( key );

	return s == "" ? def : std::stoll( s );
}

void IConfigService::SetInt64( const String & key, XE::int64 val )
{
	SetValue( key, std::to_string( val ) );
}

XE::uint8 IConfigService::GetUInt8( const String & key, XE::uint8 def ) const
{
	String s = GetValue( key );

	return s == "" ? def : ( XE::uint8 ) std::stoul( s );
}

void IConfigService::SetUInt8( const String & key, XE::uint8 val )
{
	SetValue( key, std::to_string( val ) );
}

XE::uint16 IConfigService::GetUInt16( const String & key, XE::uint16 def ) const
{
	String s = GetValue( key );

	return s == "" ? def : ( XE::uint16 ) std::stoul( s );
}

void IConfigService::SetUInt16( const String & key, XE::uint16 val )
{
	SetValue( key, std::to_string( val ) );
}

XE::uint32 IConfigService::GetUInt32( const String & key, XE::uint32 def ) const
{
	String s = GetValue( key );

	return s == "" ? def : std::stoul( s );
}

void IConfigService::SetUInt32( const String & key, XE::uint32 val )
{
	SetValue( key, std::to_string( val ) );
}

XE::uint64 IConfigService::GetUInt64( const String & key, XE::uint64 def ) const
{
	String s = GetValue( key );

	return s == "" ? def : std::stoull( s );
}

void IConfigService::SetUInt64( const String & key, XE::uint64 val )
{
	SetValue( key, std::to_string( val ) );
}

XE::float32 IConfigService::GetFloat32( const String & key, XE::float32 def ) const
{
	String s = GetValue( key );

	return s == "" ? def : std::stof( s );
}

void IConfigService::SetFloat32( const String & key, XE::float32 val )
{
	SetValue( key, std::to_string( val ) );
}

XE::float64 IConfigService::GetFloat64( const String & key, XE::float64 def ) const
{
	String s = GetValue( key );

	return s == "" ? def : std::stod( s );
}

void IConfigService::SetFloat64( const String & key, XE::float64 val )
{
	SetValue( key, std::to_string( val ) );
}

String IConfigService::GetString( const String & key, const String & def ) const
{
	String s = GetValue( key );

	return s == "" ? def : s;
}

void IConfigService::SetString( const String & key, const String & val )
{
	SetValue( key, val );
}
