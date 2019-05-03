#include "IConfigService.h"

USING_XE

BEGIN_META( IConfigService )
END_META()

XE::IConfigService::IConfigService()
{

}

XE::IConfigService::~IConfigService()
{

}

bool IConfigService::GetBool( const std::string& key ) const
{
	return GetValue( key ) == "true";
}

void IConfigService::SetBool( const std::string& key, bool val )
{
	SetValue( key, val ? "true" : "false" );
}

int8 IConfigService::GetInt8( const std::string& key ) const
{
	return std::stoi( GetValue( key ) );
}

void IConfigService::SetInt8( const std::string& key, int8 val )
{
	SetValue( key, std::to_string( val ) );
}

int16 IConfigService::GetInt16( const std::string& key ) const
{
	return std::stoi( GetValue( key ) );
}

void IConfigService::SetInt16( const std::string& key, int16 val )
{
	SetValue( key, std::to_string( val ) );
}

int32 IConfigService::GetInt32( const std::string& key ) const
{
	return std::stoi( GetValue( key ) );
}

void IConfigService::SetInt32( const std::string& key, int32 val )
{
	SetValue( key, std::to_string( val ) );
}

int64 IConfigService::GetInt64( const std::string& key ) const
{
	return std::stoll( GetValue( key ) );
}

void IConfigService::SetInt64( const std::string& key, int64 val )
{
	SetValue( key, std::to_string( val ) );
}

uint8 IConfigService::GetUInt8( const std::string& key ) const
{
	return (uint8)std::stoul( GetValue( key ) );
}

void IConfigService::SetUInt8( const std::string& key, uint8 val )
{
	SetValue( key, std::to_string( val ) );
}

uint16 IConfigService::GetUInt16( const std::string& key ) const
{
	return (uint16)std::stoul( GetValue( key ) );
}

void IConfigService::SetUInt16( const std::string& key, uint16 val )
{
	SetValue( key, std::to_string( val ) );
}

uint32 IConfigService::GetUInt32( const std::string& key ) const
{
	return std::stoul( GetValue( key ) );
}

void IConfigService::SetUInt32( const std::string& key, uint32 val )
{
	SetValue( key, std::to_string( val ) );
}

uint64 IConfigService::GetUInt64( const std::string& key ) const
{
	return std::stoull( GetValue( key ) );
}

void IConfigService::SetUInt64( const std::string& key, uint64 val )
{
	SetValue( key, std::to_string( val ) );
}

float IConfigService::GetFloat( const std::string& key ) const
{
	return std::stof( GetValue( key ) );
}

void IConfigService::SetFloat( const std::string& key, float val )
{
	SetValue( key, std::to_string( val ) );
}

double IConfigService::GetDouble( const std::string& key ) const
{
	return std::stod( GetValue( key ) );
}

void IConfigService::SetDouble( const std::string& key, double val )
{
	SetValue( key, std::to_string( val ) );
}

std::string IConfigService::GetString( const std::string& key ) const
{
	return GetValue( key );
}

void IConfigService::SetString( const std::string& key, const std::string& val ) const
{
	SetValue( key, val );
}
