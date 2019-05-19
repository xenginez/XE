#include "IConfigService.h"

USING_XE

BEG_META(IConfigService)
END_META()

XE::IConfigService::IConfigService()
{

}

XE::IConfigService::~IConfigService()
{

}

bool IConfigService::GetBool( const String &key, bool def ) const
{
	String s = GetValue(key);
	
	return s == "" ? def : s == "true";
}

void IConfigService::SetBool( const String &key, bool val )
{
	SetValue(key, val ? "true" : "false");
}

int8 IConfigService::GetInt8( const String &key, int8 def ) const
{
	String s = GetValue(key);
	
	return s == "" ? def : std::stoi(s);
}

void IConfigService::SetInt8( const String &key, int8 val )
{
	SetValue(key, std::to_string(val));
}

int16 IConfigService::GetInt16( const String &key, int16 def ) const
{
	String s = GetValue(key);
	
	return s == "" ? def : std::stoi(s);
}

void IConfigService::SetInt16( const String &key, int16 val )
{
	SetValue(key, std::to_string(val));
}

int32 IConfigService::GetInt32( const String &key, int32 def ) const
{
	String s = GetValue(key);
	
	return s == "" ? def : std::stoi(s);
}

void IConfigService::SetInt32( const String &key, int32 val )
{
	SetValue(key, std::to_string(val));
}

int64 IConfigService::GetInt64( const String &key, int64 def ) const
{
	String s = GetValue(key);
	
	return s == "" ? def : std::stoll(s);
}

void IConfigService::SetInt64( const String &key, int64 val )
{
	SetValue(key, std::to_string(val));
}

uint8 IConfigService::GetUInt8( const String &key, uint8 def ) const
{
	String s = GetValue(key);
	
	return s == "" ? def : ( uint8 ) std::stoul(s);
}

void IConfigService::SetUInt8( const String &key, uint8 val )
{
	SetValue(key, std::to_string(val));
}

uint16 IConfigService::GetUInt16( const String &key, uint16 def ) const
{
	String s = GetValue(key);
	
	return s == "" ? def : ( uint16 ) std::stoul(s);
}

void IConfigService::SetUInt16( const String &key, uint16 val )
{
	SetValue(key, std::to_string(val));
}

uint32 IConfigService::GetUInt32( const String &key, uint32 def ) const
{
	String s = GetValue(key);
	
	return s == "" ? def : std::stoul(s);
}

void IConfigService::SetUInt32( const String &key, uint32 val )
{
	SetValue(key, std::to_string(val));
}

uint64 IConfigService::GetUInt64( const String &key, uint64 def ) const
{
	String s = GetValue(key);
	
	return s == "" ? def : std::stoull(s);
}

void IConfigService::SetUInt64( const String &key, uint64 val )
{
	SetValue(key, std::to_string(val));
}

float IConfigService::GetFloat( const String &key, float def ) const
{
	String s = GetValue(key);
	
	return s == "" ? def : std::stof(s);
}

void IConfigService::SetFloat( const String &key, float val )
{
	SetValue(key, std::to_string(val));
}

double IConfigService::GetDouble( const String &key, double def ) const
{
	String s = GetValue(key);
	
	return s == "" ? def : std::stod(s);
}

void IConfigService::SetDouble( const String &key, double val )
{
	SetValue(key, std::to_string(val));
}

String IConfigService::GetString( const String &key, const String &def ) const
{
	String s = GetValue(key);
	
	return s == "" ? def : s;
}

void IConfigService::SetString( const String &key, const String &val ) const
{
	SetValue(key, val);
}
